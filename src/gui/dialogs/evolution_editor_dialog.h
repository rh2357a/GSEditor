#ifndef _GUI_DIALOGS_EVOLUTION_EDITOR_DIALOG_H_
#define _GUI_DIALOGS_EVOLUTION_EDITOR_DIALOG_H_

#include "core.h"
#include "gui.h"
#include "pokegold.h"
#include "utils.h"

#include <optional>

namespace gui::dialogs {

class EvolutionEditorDialog : public EvolutionEditorDialogBase
{
private:
    core::event_guard m_eventGuard;

private:
    core::state<int> m_evolveType = 0;
    core::state<int> m_levelUpType = 0;
    core::state<bool> m_tradeGaveItem = false;

    std::optional<pokegold::data::evolution_method> m_result;

public:
    EvolutionEditorDialog(wxWindow *parent, std::optional<pokegold::data::evolution_method> defaultValue);

private:
    void OnConfirmButtonClick(wxCommandEvent &event) override;
    void OnCancelButtonClick(wxCommandEvent &event) override;

public:
    std::optional<pokegold::data::evolution_method> GetResult() { return m_result; }
};

} // namespace gui::dialogs

namespace gui::dialogs {

/// @brief 진화 편집기 창 열기
/// @param parent 상위 윈도우 인스턴스
/// @param defaultValue
/// @return 값이 없음으로 취소를 확인하기
std::optional<pokegold::data::evolution_method> ShowEvolutionDialog(wxWindow *parent, std::optional<pokegold::data::evolution_method> defaultValue = std::nullopt);

} // namespace gui::dialogs

#endif
