#pragma once

#include "base/functional/event.h"
#include "base/types/types.h"
#include "services/pokegold/data/bitmap.h"
#include "services/pokegold/data/color.h"
#include "services/pokegold/data/game_data.h"
#include "ui/ui.h"
#include "ui/utils.h"

#include <wx/bitmap.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/wx.h>

#include <array>
#include <span>

namespace ui
{
    enum ImageEditorPopupMenu : int
    {
        Import,
        WritePng,
        WriteBinary,
    };

    class ImageEditorPanel : public wxPanel
    {
    private:
        inline static const auto TAG = "ui::ImageEditorPanel";

        wxMenu m_menu;

        pokegold::BitmapBuilder m_bitmapBuilder;
        wxBitmap m_cacheBitmap = wxNullBitmap;

        bool m_mouseDown = false;

        base::Event<> m_importRequested;

    public:
        ImageEditorPanel(wxWindow *parent,
                         wxWindowID winid = wxID_ANY,
                         const wxPoint &pos = wxDefaultPosition,
                         const wxSize &size = wxDefaultSize,
                         long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                         const wxString &name = wxASCII_STR(wxPanelNameStr))
            : wxPanel(parent, winid, pos, size, style, name)
        {
            SetBackgroundStyle(wxBG_STYLE_PAINT);

            MenuInitialize();

            Bind(wxEVT_PAINT, &ImageEditorPanel::OnPaint, this);

            Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &ev) {
                m_mouseDown = true;
            });

            Bind(wxEVT_LEFT_UP, [this](wxMouseEvent &ev) {
                if (m_mouseDown)
                {
                    PopupMenu(&m_menu);
                    m_mouseDown = false;
                }
            });

            Bind(wxEVT_MENU, &ImageEditorPanel::OnImportFromPng, this, ImageEditorPopupMenu::Import);
            Bind(wxEVT_MENU, &ImageEditorPanel::OnWritePng, this, ImageEditorPopupMenu::WritePng);
            Bind(wxEVT_MENU, &ImageEditorPanel::OnWriteBinary, this, ImageEditorPopupMenu::WriteBinary);

            FixBorderThemeBug(this);
        }

    private:
        void MenuInitialize();

        void OnPaint(wxPaintEvent &ev);
        void OnImportFromPng(wxCommandEvent &ev);
        void OnWritePng(wxCommandEvent &ev);
        void OnWriteBinary(wxCommandEvent &ev);

    public:
        auto &ImportRequested() { return m_importRequested; }

        void Clear();
        void Set2bppData(pokegold::ImageDimensions size, std::span<const u8> data, std::span<pokegold::Color> colors);
        void Set1bppData(pokegold::ImageDimensions size, std::span<const u8> data, std::span<pokegold::Color> colors);
    };
}
