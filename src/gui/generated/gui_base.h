///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
namespace gui{ namespace controls{ class DatabasePanel; } }

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
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame
{
	private:

	protected:
		enum
		{
			wxID_IPS = 6000,
			wxID_XDELTA,
			wxID_TEST_PLAY,
			wxID_EMULATOR,
		};

		wxMenuBar* m_menuBar;
		wxMenu* m_fileMenu;
		wxMenuItem* m_fileSaveMenuItem;
		wxMenuItem* m_fileExportToIpsMenuItem;
		wxMenuItem* m_fileExportToXdeltaMenuItem;
		wxMenu* m_gameMenu;
		wxMenuItem* m_gameTestPlayMenuItem;
		wxMenuItem* m_gameSetEmulatorMenuItem;
		wxMenu* m_helpMenu;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_openToolbarItem;
		wxToolBarToolBase* m_saveToolbarItem;
		wxToolBarToolBase* m_testPlayToolbarItem;
		wxToolBarToolBase* m_exitToolbarItem;
		wxStatusBar* m_statusBar;
		gui::controls::DatabasePanel* m_mainPanel;

		// Virtual event handlers, override them in your derived class
		virtual void OnMenuSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 720,560 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxICONIZE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

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

///////////////////////////////////////////////////////////////////////////////
/// Class BadDataDialogBase
///////////////////////////////////////////////////////////////////////////////
class BadDataDialogBase : public wxDialog
{
	private:

	protected:
		wxPanel* m_TopPanel;
		wxStaticText* m_messageLabel;
		wxListCtrl* m_badDataList;
		wxPanel* m_bottomPanel;
		wxButton* m_YesButton;
		wxButton* m_NoButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnDialogShow( wxShowEvent& event ) { event.Skip(); }
		virtual void OnYesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNoButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		BadDataDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("데이터 손상 알림"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 560,440 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~BadDataDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DatabasePanelBase
///////////////////////////////////////////////////////////////////////////////
class DatabasePanelBase : public wxPanel
{
	private:

	protected:
		wxNotebook* m_mainTabs;
		wxPanel* m_pokemonPanel;
		wxListBox* m_pokemonList;
		wxScrolledWindow* m_pokemonContainer;

		// Virtual event handlers, override them in your derived class
		virtual void OnPokemonSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		DatabasePanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 753,554 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~DatabasePanelBase();

};

