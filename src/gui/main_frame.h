#ifndef _GUI_MAIN_FRAME_H_
#define _GUI_MAIN_FRAME_H_

#include "core/resources.h"
#include "utils/strings.h"

#include "generated/gui_base.h"

#include <wx/mstream.h>
#include <wx/wx.h>

namespace gs::gui {

class MainFrame : public MainFrameBase
{
public:
	MainFrame(wxWindow *parent) : MainFrameBase(parent)
	{
		// 비트맵은 embedded를 써야함

		// html 은 커스텀 컨트롤 기능을 써야함
		// class: 'wxHtmlWindow'
		// include: '#include <wx/html/htmlwin.h>'
		const auto &html = gs::utils::strings::to_string(gs::core::res::app_version_html);
		m_htmlView->SetPage(html);

		// 툴바 항목 비활성화는 직접 코드로 변경 필요, 그 후 `Realize` 호출 필요
		m_tool9->Enable(false);
		m_tool10->Enable(false);
		m_toolBar3->Realize();
	}
};

} // namespace gs::gui

#endif
