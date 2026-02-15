#include "main_frame.h"

#include "base/files/patch.h"
#include "base/log.h"
#include "base/resources.h"
#include "ui/dialogs/about_dialog.h"
#include "ui/dialogs/bad_data_dialog.h"
#include "ui/dialogs/file_dialogs.h"
#include "ui/dialogs/message_box.h"
#include "ui/dialogs/progress_dialog.h"

#include <wx/persist/toplevel.h>

#include <filesystem>
#include <format>
#include <string>

namespace
{
    const std::vector<std::string> k_executableFileFilter = {"exe 파일|*.exe"};
    const std::vector<std::string> k_romFileFilter = {"gbc 파일|*.gbc", "bin 파일|*.bin"};
}

ui::MainFrame::MainFrame() : MainFrameBase(nullptr)
{
    wxPersistentRegisterAndRestore(this);

    auto appIconBitmap = embed::GetAppIconBitmap();
    wxIcon appIcon;
    appIcon.CopyFromBitmap(appIconBitmap);
    SetIcon(appIcon);

    auto title = wxString::Format(wxT("GS 에디터 v%s"), APP_VERSION_STR);
    SetTitle(title);

    m_pokegold.Rom().Opened().Subscribe(this, [this] { RomOpenedControlHandler(); });
    m_pokegold.Rom().FilePath().Subscribe(this, [this] { StatusBarTextHandler(); });
    m_pokegold.Rom().DataChanged().Subscribe(this, [this] { StatusBarTextHandler(); });
    m_configs.GetEmulatorPathState().Subscribe(this, [this] { EmulatorMenuHelpHandler(); });
}

void ui::MainFrame::RomOpenedControlHandler()
{
    bool isOpened = *m_pokegold.Rom().Opened();

    m_fileSaveMenuItem->Enable(isOpened);
    m_mainMenuBar->EnableTop(/* 게임 메뉴 */ 1, isOpened);

    m_saveToolbarItem->Enable(isOpened);
    m_testPlayToolbarItem->Enable(isOpened);
    m_toolBar->Realize();

    m_mainPanel->Enable(isOpened);
}

void ui::MainFrame::StatusBarTextHandler()
{
    auto romPath = *m_pokegold.Rom().FilePath();
    auto isDataChanged = *m_pokegold.Rom().DataChanged();

    if (romPath != base::GetNullPath())
    {
        auto state = isDataChanged ? "[변경됨] " : "";
        auto path = std::format("{}{}", state, romPath.string());
        m_statusBar->SetStatusText(wxString::FromUTF8(path));
    }
    else
    {
        m_statusBar->SetStatusText(wxT("-"));
    }
}

void ui::MainFrame::EmulatorMenuHelpHandler()
{
    auto path = *m_configs.GetEmulatorPathState();
    if (path == base::GetNullPath())
    {
        wxString help = wxT("테스트 플레이 에뮬레이터를 등록합니다.");
        m_settingsSetEmulatorMenuItem->SetHelp(help);
    }
    else
    {
        std::string realPath = path.string();
        wxString help = wxString::Format(wxT("테스트 플레이 에뮬레이터를 등록합니다. (등록: '%s')"), wxString::FromUTF8(realPath));
        m_settingsSetEmulatorMenuItem->SetHelp(help);
    }
}

void ui::MainFrame::OnClose(wxCloseEvent &event)
{
    if (*m_pokegold.Rom().DataChanged())
    {
        auto selected = ShowYesNoCancelDialog(this, "알림", "변경 사항을 롬 파일에 저장하시겠습니까?");
        if (selected == MessageBoxResult::Yes)
        {
            base::Log(TAG, "close app (save: yes)");
            // TODO: 롬 저장 수행 후, `Close()` 직접 호출 ...
            event.Veto();
        }
        else if (selected == MessageBoxResult::No)
        {
            base::Log(TAG, "close app (save: no)");
            event.Skip();
        }
        else
        {
            base::Log(TAG, "close app (save: cancel)");
            event.Veto();
        }

        return;
    }

    base::Log(TAG, "close app");
    event.Skip();
}

void ui::MainFrame::OnMenuSelected(wxCommandEvent &event)
{
    const int id = event.GetId();

    if (id == wxID_EXIT)
    {
        base::Log(TAG, "menu selected (menu: exit app)");
        Close();
        return;
    }

    if (id == wxID_OPEN)
    {
        base::Log(TAG, "menu selected (menu: open)");

        auto openRomResult = ShowOpenFileDialog(this, "열기...", k_romFileFilter);
        if (!openRomResult.has_value())
            return;

        auto &state = m_pokegold.Rom().OpenProgressState();
        auto result = ShowProgressDialog(this, "열기...", state, [this, &openRomResult] {
            std::filesystem::path filePath = *openRomResult;
            return m_pokegold.Rom().Open(filePath);
        });

        auto badDataList = m_pokegold.Data().BadDataList();
        if (result && !badDataList.empty())
            ShowBadDataDialog(this, badDataList);

        return;
    }

    if (id == wxID_ABOUT)
    {
        base::Log(TAG, "menu selected (menu: about this app)");
        ShowAboutDialog(this);
        return;
    }

    if (id == wxID_TEST_PLAY)
    {
        base::Log(TAG, "menu selected (menu: test play)");

        auto emulatorPath = m_configs.GetEmulatorPath();
        if (!emulatorPath)
        {
            auto result = ShowYesNoDialog(this, "경고", "등록된 에뮬레이터가 없습니다.\n찾아보겠습니까?");
            if (result == MessageBoxResult::No)
                return;

            auto openResult = ShowOpenFileDialog(this, "에뮬레이터 등록...", k_executableFileFilter);
            if (!openResult.has_value())
                return;

            auto newPath = *openResult;
            m_configs.SetEmulatorPath(newPath);

            emulatorPath = m_configs.GetEmulatorPath();
        }

        base::Log(TAG, "  - path: \"{}\"", (*emulatorPath).string());

        // TODO: sidecar 실행 추가...

        return;
    }

    if (id == wxID_EMULATOR)
    {
        base::Log(TAG, "menu selected (menu: set emulator)");

        auto openResult = ShowOpenFileDialog(this, "에뮬레이터 등록...", k_executableFileFilter);
        if (openResult.has_value())
        {
            base::Log(TAG, "emulator selected (path=\"{}\")", (*openResult).string());
            m_configs.SetEmulatorPath(*openResult);
        }

        return;
    }

    if (id == wxID_IPS)
    {
        base::Log(TAG, "menu selected (menu: create ips)");

        auto openBaseRomResult = ShowOpenFileDialog(this, "원본 롬 열기...", k_romFileFilter);
        if (!openBaseRomResult.has_value())
            return;

        auto savePatchResult = ShowSaveFileDialog(this, "패치 파일 저장...", {"ips 패치 파일|*.ips"});
        if (!savePatchResult.has_value())
            return;

        auto &state = m_pokegold.Rom().BuildProgressState();
        auto result = ShowProgressDialog(this, "저장...", state, [this] {
            return m_pokegold.Rom().Build();
        });

        if (result.has_value())
        {
            base::CreateIpsPatch(*savePatchResult, *openBaseRomResult, *result);
            ShowAlertDialog(this, "완료", "패치 파일이 생성되었습니다!");
        }

        return;
    }

    if (id == wxID_XDELTA)
    {
        base::Log(TAG, "menu selected (menu: create xdelta)");

        auto openBaseRomResult = ShowOpenFileDialog(this, "원본 롬 열기...", k_romFileFilter);
        if (!openBaseRomResult.has_value())
            return;

        auto savePatchResult = ShowSaveFileDialog(this, "패치 파일 저장...", {"xdelta 패치 파일|*.xdelta"});
        if (!savePatchResult.has_value())
            return;

        auto &state = m_pokegold.Rom().BuildProgressState();
        auto result = ShowProgressDialog(this, "저장...", state, [this] {
            return m_pokegold.Rom().Build();
        });

        if (result.has_value())
        {
            base::CreateDeltaPatch(*savePatchResult, *openBaseRomResult, *result);
            ShowAlertDialog(this, "완료", "패치 파일이 생성되었습니다!");
        }

        return;
    }
}
        return;
    }
}
