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
#include <wx/html/htmlwin.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/spinctrl.h>
#include <wx/checklst.h>
#include <wx/wrapsizer.h>
#include <wx/scrolwin.h>

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

		wxMenu* m_fileMenu;
		wxMenuItem* m_fileSaveMenuItem;
		wxMenuItem* m_fileExportToIpsMenuItem;
		wxMenuItem* m_fileExportToXdeltaMenuItem;
		wxMenu* m_gameMenu;
		wxMenuItem* m_gameTestPlayMenuItem;
		wxMenuItem* m_gameSetEmulatorMenuItem;
		wxMenu* m_helpMenu;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_saveToolbarItem;
		wxToolBarToolBase* m_testPlayToolbarItem;
		wxStatusBar* m_statusBar;
		gui::controls::DatabasePanel* m_mainPanel;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 740,560 ), long style = wxCAPTION|wxCLOSE_BOX|wxICONIZE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialogBase
///////////////////////////////////////////////////////////////////////////////
class AboutDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_authorText;
		wxStaticText* m_versionText;
		wxHtmlWindow* m_versionHtml;
		wxTextCtrl* m_openSourceLicensesText;

	public:

		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GS 에디터 정보..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 616,538 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE );

		~AboutDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class BadDataDialogBase
///////////////////////////////////////////////////////////////////////////////
class BadDataDialogBase : public wxDialog
{
	private:

	protected:
		wxListCtrl* m_badDataList;

		// Virtual event handlers, override them in your derived class
		virtual void OnDialogShow( wxShowEvent& event ) { event.Skip(); }
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }
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
		wxListBox* m_pokemonList;
		wxScrolledWindow* m_pokemonContainer;
		wxTextCtrl* m_pokemonNoText;
		wxTextCtrl* m_pokemonNameText;
		wxComboBox* m_pokemonGenderRateComboBox;
		wxComboBox* m_pokemonGrowthRateComboBox;
		wxComboBox* m_pokemonType1ComboBox;
		wxComboBox* m_pokemonType2ComboBox;
		wxComboBox* m_pokemonItem1ComboBox;
		wxComboBox* m_pokemonItem2ComboBox;
		wxComboBox* m_pokemonEggGroup1ComboBox;
		wxComboBox* m_pokemonEggGroup2ComboBox;
		wxSpinCtrlDouble* m_pokemonStatsHpValue;
		wxSpinCtrlDouble* m_pokemonStatsAtkValue;
		wxSpinCtrlDouble* m_pokemonStatsDefValue;
		wxSpinCtrlDouble* m_pokemonStatsSpAtkValue;
		wxSpinCtrlDouble* m_pokemonStatsSpDefValue;
		wxSpinCtrlDouble* m_pokemonStatsSpdValue;
		wxSpinCtrlDouble* m_pokemonStatsExpValue;
		wxSpinCtrlDouble* m_pokemonStatsCatchRateValue;
		wxStaticText* m_pokemonCatchRatePercentage;
		wxTextCtrl* m_pokemonDexSpeciesNameText;
		wxSpinCtrlDouble* m_pokemonDexHeightValue;
		wxSpinCtrlDouble* m_pokemonDexWeightValue;
		wxStaticText* m_pokemonDexDescriptionLabel;
		wxTextCtrl* m_pokemonDexDescriptionText;
		wxListCtrl* m_pokemonEvolutionsList;
		wxListCtrl* m_pokemonLearnMovesList;
		wxCheckListBox* m_pokemonHmTmList1;
		wxCheckListBox* m_pokemonHmTmList2;
		wxCheckListBox* m_pokemonHmTmList3;
		wxCheckListBox* m_pokemonHmTmList4;
		wxCheckListBox* m_pokemonHmTmList5;
		wxCheckListBox* m_pokemonHmTmList6;
		wxCheckListBox* m_pokemonHmTmList7;
		wxCheckListBox* m_pokemonHmTmList8;

		// Virtual event handlers, override them in your derived class
		virtual void OnPokemonSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		DatabasePanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 740,1500 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~DatabasePanelBase();

};

