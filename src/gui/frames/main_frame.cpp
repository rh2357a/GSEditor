#include "main_frame.h"

#include "resources.h"
#include "core.h"
#include "utils.h"
#include "embed.h"
#include "pokegold.h"

#include <wx/wx.h>

#include <string>
#include <format>
#include <filesystem>

gui::frames::MainFrame::MainFrame(wxWindow *parent) : MainFrameBase(parent)
{
    const auto &bmp = embed::app_ico_to_wx_bitmap();
    wxIcon icon;
    icon.CopyFromBitmap(bmp);
    SetIcon(icon);

    const auto title = std::format("GS 에디터 v{}", APP_VERSION_STR);
    SetTitle(wxString::FromUTF8(title));

    m_subscriptions.subscribe(pokegold::event::rom_changed, [this] {
        m_mainPanel->Enable(pokegold::romfile::is_opened);

        m_fileSaveMenuItem->Enable(pokegold::romfile::is_opened);
        m_gameExportToIpsMenuItem->Enable(pokegold::romfile::is_opened);
        m_gameExportToXdeltaMenuItem->Enable(pokegold::romfile::is_opened);
        m_gameTestPlayMenuItem->Enable(pokegold::romfile::is_opened);

        m_saveToolbarItem->Enable(pokegold::romfile::is_opened);
        m_testPlayToolbarItem->Enable(pokegold::romfile::is_opened);
        m_toolBar->Realize();
    });

    m_subscriptions.subscribe(pokegold::event::rom_data_changed, [this] {
        if (pokegold::romfile::is_opened)
        {
            const auto state = pokegold::romfile::is_changed ? "[변경됨] " : "";
            const auto path = std::format("{}{}", state, pokegold::romfile::path.string());
            m_statusBar->SetStatusText(wxString::FromUTF8(path));
        }
        else
        {
            m_statusBar->SetStatusText(wxT("-"));
        }
    });

    m_subscriptions.subscribe(core::app_settings::emulator_path_changed, [this](const std::filesystem::path &path) {
        std::string realPath = path.string() == "" ? "없음" : path.string();
        wxString help = wxString::Format(wxT("테스트 플레이를 위한 에뮬레이터를 등록합니다. (등록: '%s')"), wxString::FromUTF8(realPath));
        m_settingsSetEmulatorMenuItem->SetHelp(help);
    });

    // 앱의 초기 상태를 알림
    pokegold::event::rom_data_changed();
    pokegold::event::rom_changed();
    core::app_settings::emulator_path_changed(core::app_settings::get_emulator_path());
}

void SaveInternal()
{
    const auto outputRomPath = pokegold::build();
    const auto romPath = pokegold::romfile::path;
    std::filesystem::copy_file(outputRomPath, romPath, std::filesystem::copy_options::overwrite_existing);
    pokegold::config::write();

    pokegold::romfile::is_changed = false;
    pokegold::event::rom_data_changed();
}

void gui::frames::MainFrame::OnMenuSelected(wxCommandEvent &event)
{
    const auto id = event.GetId();

    if (id == wxID_EXIT)
    {
        Close();
        return;
    }

    if (id == wxID_ABOUT)
    {
        dialogs::AboutDialog dialog(this);
        dialog.ShowModal();
        return;
    }

    if (id == wxID_OPEN)
    {
        if (pokegold::romfile::is_opened && pokegold::romfile::is_changed)
        {
            wxBell();

            const auto result = gui::dialogs::ShowConfirm(this, "경고", "이미 다른 롬 파일이 열려있습니다!\n계속하겠습니까?");
            if (result == wxNO)
                return;
        }

        wxFileDialog openDlg(this, wxT("롬 열기..."), "", "", wxT("GBC 파일|*.gbc|BIN 바일|*.bin"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openDlg.ShowModal() == wxID_CANCEL)
            return;

        pokegold::close();

        const auto result = pokegold::open(openDlg.GetPath().utf8_string());
        if (!result.empty())
        {
            dialogs::BadDataDialog dialog(this, result);
            dialog.ShowModal();
        }
        return;
    }

    if (id == wxID_SAVE)
    {
        SaveInternal();
        return;
    }

    if (id == wxID_TEST_PLAY)
    {
        const auto outputPath = pokegold::build();

        // sav 복사
        if (std::filesystem::exists(pokegold::romfile::save_path))
        {
            const auto saveBytes = utils::files::read_bytes_from_file(pokegold::romfile::save_path);
            const auto savePath = pokegold::romfile::workspace_path / "target.sav";
            utils::files::write_bytes_to_file(savePath, saveBytes);
        }

        auto emulator_path = core::app_settings::get_emulator_path();
        if (!std::filesystem::exists(emulator_path))
        {
            wxBell();

            const auto result = gui::dialogs::ShowConfirm(this, "경고", "등록된 에뮬레이터가 없습니다!\n찾아보겠습니까?");
            if (result == wxNO)
                return;

            wxFileDialog dialog(this, wxT("에뮬레이터 찾기..."), "", "", wxT("exe 파일|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if (dialog.ShowModal() == wxID_CANCEL)
                return;

            core::app_settings::set_emulator_path(dialog.GetPath().utf8_string());
            emulator_path = core::app_settings::get_emulator_path();
            if (!std::filesystem::exists(emulator_path))
                return;
        }

        utils::run_process(emulator_path, outputPath.string(), pokegold::romfile::workspace_path.string());
        return;
    }

    if (id == wxID_EMULATOR)
    {
        wxFileDialog dialog(this, wxT("에뮬레이터 찾기..."), "", "", wxT("exe 파일|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (dialog.ShowModal() == wxID_CANCEL)
            return;

        core::app_settings::set_emulator_path(dialog.GetPath().utf8_string());
        return;
    }

    // TODO: 원본 롬을 열어 비교하여 생성해야함..
    if (id == wxID_IPS)
    {
        wxFileDialog dialog(this, wxT("IPS 패치 생성..."), "", "", wxT("IPS 파일|*.ips"), wxFD_SAVE);
        if (dialog.ShowModal() == wxID_CANCEL)
            return;

        const auto inputBytes = utils::files::read_bytes_from_file(pokegold::romfile::path);
        const auto outputBytes = utils::files::read_bytes_from_file(pokegold::build());
        const auto ipsBytes = utils::patch::create_ips_patch(inputBytes, outputBytes);
        const auto patchPath = dialog.GetPath().utf8_string();
        utils::files::write_bytes_to_file(patchPath, ipsBytes);
        return;
    }

    // TODO: 원본 롬을 열어 비교하여 생성해야함..
    if (id == wxID_XDELTA)
    {
        wxFileDialog dialog(this, wxT("xdelta 패치 생성..."), "", "", wxT("xdelta 파일|*.xdelta"), wxFD_SAVE);
        if (dialog.ShowModal() == wxID_CANCEL)
            return;

        const auto inputBytes = utils::files::read_bytes_from_file(pokegold::romfile::path);
        const auto outputBytes = utils::files::read_bytes_from_file(pokegold::build());
        const auto patchBytes = utils::patch::create_xdelta_patch(inputBytes, outputBytes);
        const auto patchPath = dialog.GetPath().ToStdString();
        utils::files::write_bytes_to_file(patchPath, patchBytes);
        return;
    }
}

void gui::frames::MainFrame::OnClose(wxCloseEvent &event)
{
    if (pokegold::romfile::is_changed)
    {
        wxBell();

        const auto selected = gui::dialogs::ShowYesNoCancel(this, "알림", "변경 사항을 롬 파일에 저장하시겠습니까?");
        if (selected == wxYES)
        {
            debug_log("main", "close app (save: yes)");
            SaveInternal();
            event.Skip();
        }
        else if (selected == wxNO)
        {
            debug_log("main", "close app (save: no)");
            event.Skip();
        }
        else
        {
            debug_log("main", "close app (save: cancel)");
            event.Veto();
        }

        core::app_settings::write();
        return;
    }

    debug_log("main", "close app");
    event.Skip();
    core::app_settings::write();
}
