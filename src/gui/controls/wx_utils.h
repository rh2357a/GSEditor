#ifndef _GUI_CONTROLS_WX_UTILS_H_
#define _GUI_CONTROLS_WX_UTILS_H_

#include "gui.h"

#include <vector>
#include <initializer_list>

namespace gui::controls {

class ListCtrlColumn
{
public:
    wxString title;
    double width;
};

void AutoColumnsWidth(wxListCtrl *ctrl);
void FixedHeaderWidth(wxListCtrl *ctrl, const std::vector<ListCtrlColumn> columns);
void NestedScrolling(const std::initializer_list<wxWindow *> &ctrls);
void Select(wxWindow *ctrl, int selection);
void SetValue(wxSpinCtrlDouble *ctrl, double value);

} // namespace gui::controls

#endif
