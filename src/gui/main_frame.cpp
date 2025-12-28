#include "main_frame.h"

#include "utils.h"
#include "embed.h"
#include "pokegold.h"
#include "gui/about_dialog.h"

#include <wx/wx.h>

gui::MainFrame::MainFrame(wxWindow *parent) : MainFrameBase(parent)
{
    const auto &bmp = embed::app_ico_to_wx_bitmap();
    wxIcon icon;
    icon.CopyFromBitmap(bmp);
    SetIcon(icon);

    // 툴바 항목 비활성화는 직접 코드로 변경 필요, 그 후 `Realize` 호출 필요
    // m_tool9->Enable(false);
    // m_tool10->Enable(false);
    // m_toolBar->Realize();
}

void gui::MainFrame::OnMenuSelected(wxCommandEvent &event)
{
    const auto id = event.GetId();

    if (id == wxID_EXIT)
    {
        wxExit();
        return;
    }

    if (id == wxID_ABOUT)
    {
        AboutDialog dialog(this);
        dialog.ShowModal();
        return;
    }

    if (id == wxID_OPEN)
    {
        wxFileDialog openDlg(this, wxT("롬 열기..."), "", "", wxT("GBC 파일|*.gbc"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openDlg.ShowModal() == wxID_CANCEL)
            return;

        // TEST 1: pokegold
        pokegold::open(openDlg.GetPath().ToStdString());
        pokegold::build();

        return;
    }

    if (id == wxID_SAVE)
    {
        wxFileDialog openDlg(this, wxT("롬 열기..."), "", "", wxT("GBC 파일|*.gbc"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openDlg.ShowModal() == wxID_CANCEL)
            return;

        // TEST 2: lzcomp
        pokegold::open(openDlg.GetPath().ToStdString());

        auto a = pokegold::data::pokemons[2].front_image;
        utils::files::write_bytes_to_file("a.bin", a);

        auto b = a.decompressed();
        utils::files::write_bytes_to_file("b.bin", b);

        auto c = b.compressed();
        utils::files::write_bytes_to_file("c.bin", c);

        auto d = c.decompressed();
        utils::files::write_bytes_to_file("d.bin", d);

        return;
    }
}
