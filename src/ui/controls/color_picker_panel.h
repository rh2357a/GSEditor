#pragma once

#include "base/functional/guard.h"
#include "base/functional/state.h"
#include "ui/ui.h"
#include "ui/utils.h"

#include <wx/button.h>
#include <wx/colour.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/panel.h>
#include <wx/wx.h>

namespace ui
{
    namespace internal
    {
        class ColorPickerPopupPanel : public ColorPickerPopupPanelBase
        {
        private:
            base::MutableState<int> m_red = 0;
            base::MutableState<int> m_green = 0;
            base::MutableState<int> m_blue = 0;

            base::MutableState<wxColour> m_colorState;

            base::Guard m_eventGuard;

            wxBitmap m_pickerBitmap, m_brightnessBitmap;
            wxPoint m_pickerPoint{0, 0};
            float m_hue = 0, m_sat = 0, m_val = 0;

        public:
            ColorPickerPopupPanel(wxWindow *parent, wxColour defaultColor);

        public:
            base::State<wxColour> &GetColorState() { return m_colorState; }

        private:
            void OnHsvUpdated();
            void OnRgbUpdated();

            void OnPickerMouseEvent(wxMouseEvent &event) override;
            void OnPickerPaint(wxPaintEvent &event) override;
            void OnBrightnessSlider(wxCommandEvent &event) override;
            void OnBrightnessPreviewPaint(wxPaintEvent &event) override;
            void OnPreviewPaint(wxPaintEvent &event) override;
        };
    }

    class ColorPickerPanel : public wxPanel
    {
    private:
        base::MutableState<wxColour> m_color;

        bool m_mouseDown = false;

    public:
        ColorPickerPanel(wxWindow *parent,
                         wxWindowID winid = wxID_ANY,
                         const wxPoint &pos = wxDefaultPosition,
                         const wxSize &size = wxDefaultSize,
                         long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                         const wxString &name = wxASCII_STR(wxPanelNameStr))
            : wxPanel(parent, winid, pos, size, style, name)
        {
            SetBackgroundStyle(wxBG_STYLE_PAINT);
            SetColor({255, 255, 255});

            Bind(wxEVT_PAINT, [&](wxPaintEvent &ev) { OnPaint(ev); });

            Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &ev) {
                m_mouseDown = true;
            });

            Bind(wxEVT_LEFT_UP, [this](wxMouseEvent &ev) {
                if (m_mouseDown)
                {
                    OnClick(ev);
                    m_mouseDown = false;
                }
            });

            FixBorderThemeBug(this);
        }

    public:
        wxColour GetColor() const { return *m_color; }
        void SetColor(wxColour color);

        base::State<wxColour> &GetColorState() { return m_color; }

    private:
        void OnPaint(wxPaintEvent &ev);
        void OnClick(wxMouseEvent &ev);
    };
}
