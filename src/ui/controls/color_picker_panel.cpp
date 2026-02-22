#include "color_picker_panel.h"

#include "ui/bindings.h"
#include "ui/utils.h"

#include <wx/colour.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/dcclient.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/types.h>
#include <wx/wx.h>

#include <memory>

namespace
{
    wxColour HSVtoRGB(float h, float s, float v)
    {
        float c = v * s;
        float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
        float m = v - c;

        float r, g, b;
        if (h < 60)
            r = c, g = x, b = 0;
        else if (h < 120)
            r = x, g = c, b = 0;
        else if (h < 180)
            r = 0, g = c, b = x;
        else if (h < 240)
            r = 0, g = x, b = c;
        else if (h < 300)
            r = x, g = 0, b = c;
        else
            r = c, g = 0, b = x;

        return wxColour((r + m) * 255, (g + m) * 255, (b + m) * 255);
    }

    void RGBtoHSV(const wxColour &rgb, float &h, float &s, float &v)
    {
        float r = rgb.Red() / 255.0f;
        float g = rgb.Green() / 255.0f;
        float b = rgb.Blue() / 255.0f;

        float max = std::max(r, std::max(g, b));
        float min = std::min(r, std::min(g, b));

        float delta = max - min;

        // value
        v = max;

        // saturation
        if (max == 0.0f)
        {
            s = 0.0f;
            h = 0.0f;
            return;
        }
        else
        {
            s = delta / max;
        }

        // hue
        if (delta == 0.0f)
            h = 0.0f;
        else if (max == r)
            h = 60.0f * fmod(((g - b) / delta), 6.0f);
        else if (max == g)
            h = 60.0f * (((b - r) / delta) + 2.0f);
        else
            h = 60.0f * (((r - g) / delta) + 4.0f);

        if (h < 0.0f)
            h += 360.0f;
    }
}

// popup panel

ui::internal::ColorPickerPopupPanel::ColorPickerPopupPanel(wxWindow *parent, wxColour defaultColor)
    : ColorPickerPopupPanelBase(parent)
{
    BindSliderValue(this, m_redSlider, m_red);
    BindSpinCtrlValue(this, m_redSpinCtrl, m_red);

    BindSliderValue(this, m_greenSlider, m_green);
    BindSpinCtrlValue(this, m_greenSpinCtrl, m_green);

    BindSliderValue(this, m_blueSlider, m_blue);
    BindSpinCtrlValue(this, m_blueSpinCtrl, m_blue);

    m_pickerPanel->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    m_brightnessPreviewPanel->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    m_previewPanel->SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    m_red.Subscribe(this, [this] { OnRgbUpdated(); });
    m_green.Subscribe(this, [this] { OnRgbUpdated(); });
    m_blue.Subscribe(this, [this] { OnRgbUpdated(); });

    m_red.Update(defaultColor.Red());
    m_green.Update(defaultColor.Green());
    m_blue.Update(defaultColor.Blue());
    OnRgbUpdated();
}

void ui::internal::ColorPickerPopupPanel::OnPickerMouseEvent(wxMouseEvent &event)
{
    if (event.LeftIsDown() || (event.GetEventType() == wxEVT_MOTION && event.LeftIsDown()))
    {
        m_pickerPoint.x = std::max(0, std::min(238, event.GetX()));
        m_pickerPoint.y = std::max(0, std::min(158, event.GetY()));

        const auto size = m_pickerPanel->GetClientSize();
        m_hue = std::max(0.0f, std::min(360.0f, (float)m_pickerPoint.x / (size.x - 1) * 360.0f));
        m_sat = std::max(0.0f, std::min(1.0f, 1.0f - (float)m_pickerPoint.y / (size.y - 1)));

        OnHsvUpdated();
    }
}

void ui::internal::ColorPickerPopupPanel::OnPickerPaint(wxPaintEvent &ev)
{
    wxAutoBufferedPaintDC dc(m_pickerPanel);
    std::unique_ptr<wxGraphicsContext> gc((wxGraphicsContext::Create(dc)));

    const auto size = m_pickerPanel->GetClientSize();
    if (!m_pickerBitmap.IsOk() || m_pickerBitmap.GetWidth() != size.x || m_pickerBitmap.GetHeight() != size.y)
    {
        int width = size.x;
        int height = size.y;

        wxImage img(width, height);

        unsigned char *data = img.GetData();
        for (int y = 0; y < height; y++)
        {
            float ny = (float)y / (height - 1);

            for (int x = 0; x < width; x++)
            {
                float nx = (float)x / (width - 1);

                float hue = nx * 360.0f;
                float sat = 1.0f - ny;
                float val = 1.0f;

                wxColour col = HSVtoRGB(hue, sat, val);

                int index = (y * width + x) * 3;
                data[index + 0] = col.Red();
                data[index + 1] = col.Green();
                data[index + 2] = col.Blue();
            }
        }

        m_pickerBitmap = wxBitmap(img);
    }

    dc.DrawBitmap(m_pickerBitmap, 0, 0);

    gc->SetPen(wxPen(*wxBLACK, 2));
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->DrawEllipse(m_pickerPoint.x - 4, m_pickerPoint.y - 4, 8, 8);
}

void ui::internal::ColorPickerPopupPanel::OnBrightnessSlider(wxCommandEvent &event)
{
    m_val = m_brightnessSlider->GetValue() / 100.0;
    OnHsvUpdated();
}

void ui::internal::ColorPickerPopupPanel::OnBrightnessPreviewPaint(wxPaintEvent &ev)
{
    wxAutoBufferedPaintDC dc(m_brightnessPreviewPanel);

    const auto size = m_brightnessPreviewPanel->GetClientSize();
    {
        int width = size.x;
        int height = size.y;

        wxImage img(width, height);

        unsigned char *data = img.GetData();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float value = (float)x / (width - 1);

                wxColour col = HSVtoRGB(m_hue, m_sat, value);

                int index = (y * width + x) * 3;
                data[index + 0] = col.Red();
                data[index + 1] = col.Green();
                data[index + 2] = col.Blue();
            }
        }

        m_brightnessBitmap = wxBitmap(img);
    }

    dc.DrawBitmap(m_brightnessBitmap, 0, 0);
}

void ui::internal::ColorPickerPopupPanel::OnPreviewPaint(wxPaintEvent &event)
{
    wxAutoBufferedPaintDC dc(m_previewPanel);
    std::unique_ptr<wxGraphicsContext> gc((wxGraphicsContext::Create(dc)));
    const auto size = m_previewPanel->GetClientSize();
    gc->SetBrush({wxColour(*m_red, *m_green, *m_blue)});
    gc->DrawRectangle(0, 0, size.x, size.y);
}

void ui::internal::ColorPickerPopupPanel::OnHsvUpdated()
{
    if (!m_eventGuard.IsGuarded())
    {
        m_eventGuard([this] {
            const auto rgb = HSVtoRGB(m_hue, m_sat, m_val);
            m_colorState.Update(rgb);

            m_red.Update(int(rgb.Red()));
            m_green.Update(int(rgb.Green()));
            m_blue.Update(int(rgb.Blue()));

            m_pickerPanel->Refresh();
            m_brightnessPreviewPanel->Refresh();
            m_previewPanel->Refresh();
        });
    }
}

void ui::internal::ColorPickerPopupPanel::OnRgbUpdated()
{
    if (!m_eventGuard.IsGuarded())
    {
        m_eventGuard([this] {
            const wxColour newColor = wxColour(*m_red, *m_green, *m_blue);
            m_colorState.Update(newColor);

            RGBtoHSV(newColor, m_hue, m_sat, m_val);

            const auto size = m_pickerPanel->GetClientSize();
            m_pickerPoint.x = m_hue / 360.0f * size.x;
            m_pickerPoint.y = (1.0f - m_sat) * size.y;

            m_brightnessSlider->SetValue(int(m_val * 100));

            m_pickerPanel->Refresh();
            m_brightnessPreviewPanel->Refresh();
            m_previewPanel->Refresh();
        });
    }
}

// button

void ui::ColorPickerPanel::SetColor(wxColour color)
{
    m_color = color;
    Refresh();
}

void ui::ColorPickerPanel::OnPaint(wxPaintEvent &ev)
{
    wxAutoBufferedPaintDC dc(this);
    std::unique_ptr<wxGraphicsContext> gc((wxGraphicsContext::Create(dc)));
    const auto size = GetClientSize();
    gc->SetBrush({m_color});
    gc->DrawRectangle(0, 0, size.x, size.y);
}

void ui::ColorPickerPanel::OnClick(wxMouseEvent &ev)
{
    // NOTE: 팝업 생성 중에는 컨트롤의 paint 상태가 좋지않음. 그리기는 일시정지
    Freeze();
    internal::ColorPickerPopupPanel *panel = new internal::ColorPickerPopupPanel(this, m_color);
    ShowDropdownPopup(this, panel);
    Thaw();

    panel->GetColorState().Subscribe(panel, [this](const wxColour &newColor) {
        SetColor(newColor);
    });

    ev.Skip();
}
