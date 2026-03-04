#include "type_weather_modifier_editor_dialog.h"

#include "services/pokegold/data/game_data.h"

#include <wx/wx.h>

ui::internal::TypeWeatherModifierEditorDialog::TypeWeatherModifierEditorDialog(wxWindow *parent, std::optional<pokegold::WeatherTypeModifier> defaultValue)
    : TypeWeatherModifierEditorDialogBase(parent)
{
    if (defaultValue.has_value())
    {
        if ((*defaultValue).Weather == pokegold::BattleWeather::Rain)
            m_weatherComboBox->Select(0);
        else if ((*defaultValue).Weather == pokegold::BattleWeather::Sandstorm)
            m_weatherComboBox->Select(1);
        else if ((*defaultValue).Weather == pokegold::BattleWeather::Sun)
            m_weatherComboBox->Select(2);

        if ((*defaultValue).TypeEffectiveness == pokegold::TypeEffectiveness::MoreEffective)
            m_effectivenessComboBox->Select(0);
        else if ((*defaultValue).TypeEffectiveness == pokegold::TypeEffectiveness::NotVeryEffective)
            m_effectivenessComboBox->Select(1);

        SetTitle(wxT("수정..."));
    }
    else
    {
        m_weatherComboBox->Select(0);
        m_effectivenessComboBox->Select(0);

        SetTitle(wxT("추가..."));
    }
}

void ui::internal::TypeWeatherModifierEditorDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    pokegold::WeatherTypeModifier result;

    if (m_weatherComboBox->GetSelection() == 0)
        result.Weather = pokegold::BattleWeather::Rain;
    else if (m_weatherComboBox->GetSelection() == 1)
        result.Weather = pokegold::BattleWeather::Sandstorm;
    else if (m_weatherComboBox->GetSelection() == 2)
        result.Weather = pokegold::BattleWeather::Sun;

    if (m_effectivenessComboBox->GetSelection() == 1)
        result.TypeEffectiveness = pokegold::TypeEffectiveness::NotVeryEffective;
    else if (m_effectivenessComboBox->GetSelection() == 0)
        result.TypeEffectiveness = pokegold::TypeEffectiveness::MoreEffective;

    Result = result;

    EndModal(wxID_OK);
}

void ui::internal::TypeWeatherModifierEditorDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    Result.reset();

    EndModal(wxID_CANCEL);
}

std::optional<pokegold::WeatherTypeModifier> ui::ShowTypeWeatherModifierEditorDialog(wxWindow *parent, std::optional<pokegold::WeatherTypeModifier> defaultValue)
{
    internal::TypeWeatherModifierEditorDialog dialog(parent, defaultValue);
    dialog.ShowModal();
    return dialog.Result;
}
