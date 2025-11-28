///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menuBar;
		wxMenu* m_fileMenu;
		wxMenu* m_helpMenu;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_tool10;
		wxToolBarToolBase* m_tool9;
		wxStatusBar* m_statusBar;

		// Virtual event handlers, override them in your derived class
		virtual void OnMenuSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 653,455 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxICONIZE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialogBase
///////////////////////////////////////////////////////////////////////////////
class AboutDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticBitmap* m_appIconBitmap;
		wxStaticText* m_authorText;
		wxStaticText* m_versionText;
		wxStaticText* m_separatorText;
		wxStaticLine* m_appInfoLine;
		wxHtmlWindow* m_versionHtml;

	public:

		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GS 에디터 정보..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 552,538 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE );

		~AboutDialogBase();

};

