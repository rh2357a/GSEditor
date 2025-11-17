#ifndef _APP_H_
#define _APP_H_

#include "gui/main_frame.h"
#include <wx/wx.h>

class App : public wxApp
{
private:
	gs::gui::MainFrame *m_mainFrame = nullptr;

public:
	virtual bool OnInit();
};

#endif
