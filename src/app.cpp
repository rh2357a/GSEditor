#include "app.h"
#include "gui/main_frame.h"

bool App::OnInit()
{
	wxInitAllImageHandlers();

	m_mainFrame = new gs::gui::MainFrame(nullptr);
	m_mainFrame->Show();

	return true;
}

wxIMPLEMENT_APP(App);
