///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
namespace ui{ class ColorPickerPanel; }
namespace ui{ class ColoredCheckListBox; }
namespace ui{ class ColoredListBox; }
namespace ui{ class ColoredListCtrl; }
namespace ui{ class DatabasePanel; }

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
#include <wx/listbox.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/spinctrl.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/checklst.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/statbmp.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/slider.h>

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
			wxID_DEBUG_LABEL,
			wxID_TEST_PLAY_SAVE,
		};

		wxMenuBar* m_mainMenuBar;
		wxMenuItem* m_fileSaveMenuItem;
		wxMenuItem* m_fileExportToIpsMenuItem;
		wxMenuItem* m_fileExportToXdeltaMenuItem;
		wxMenuItem* m_gameTestPlayMenuItem;
		wxMenuItem* m_gameTestPlaySetEmulatorMenuItem;
		wxMenuItem* m_gameTestPlayShowDebugLabelMenuItem;
		wxMenuItem* m_gameTestPlaySaveMenuItem;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_saveToolbarItem;
		wxToolBarToolBase* m_testPlayToolbarItem;
		wxStatusBar* m_statusBar;
		ui::DatabasePanel* m_mainPanel;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuItemSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 740,560 ), long style = wxCAPTION|wxCLOSE_BOX|wxICONIZE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DatabasePanelBase
///////////////////////////////////////////////////////////////////////////////
class DatabasePanelBase : public wxPanel
{
	private:

	protected:
		enum
		{
			wxID_POKEMON_EVOLUTION_ADD = 6000,
			wxID_POKEMON_EVOLUTION_MODIFY,
			wxID_POKEMON_EVOLUTION_REMOVE,
			wxID_POKEMON_EVOLUTION_CLEAR,
			wxID_POKEMON_LEARN_MOVES_IMPORT,
			wxID_POKEMON_LEARN_MOVES_ADD,
			wxID_POKEMON_LEARN_MOVES_MODIFY,
			wxID_POKEMON_LEARN_MOVES_REMOVE,
			wxID_POKEMON_LEARN_MOVES_CLEAR,
			wxID_POKEMON_TMHMS_CHECK_ALL,
			wxID_POKEMON_TMHMS_CLEAR,
		};

		ui::ColoredListBox* m_pokemonList;
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
		ui::ColorPickerPanel* m_panel24;
		wxTextCtrl* m_pokemonDexSpeciesNameText;
		wxSpinCtrlDouble* m_pokemonDexHeightValue;
		wxSpinCtrlDouble* m_pokemonDexWeightValue;
		wxStaticText* m_pokemonDexDescriptionLabel;
		wxTextCtrl* m_pokemonDexDescriptionText;
		ui::ColoredListCtrl* m_pokemonEvolutionsList;
		wxButton* m_pokemonEvolutionAdd;
		wxButton* m_pokemonEvolutionModify;
		wxButton* m_pokemonEvolutionRemove;
		wxButton* m_pokemonEvolutionClear;
		ui::ColoredListCtrl* m_pokemonLearnMovesList;
		wxButton* m_pokemonLearnMovesImport;
		wxButton* m_pokemonLearnMovesAdd;
		wxButton* m_pokemonLearnMovesModify;
		wxButton* m_pokemonLearnMovesRemove;
		wxButton* m_pokemonLearnMovesClear;
		wxGridSizer* m_pokemonTMHMsSizer;
		ui::ColoredCheckListBox* m_pokemonHmTmList1;
		ui::ColoredCheckListBox* m_pokemonHmTmList2;
		ui::ColoredCheckListBox* m_pokemonHmTmList3;
		ui::ColoredCheckListBox* m_pokemonHmTmList4;
		ui::ColoredCheckListBox* m_pokemonHmTmList5;
		ui::ColoredCheckListBox* m_pokemonHmTmList6;
		ui::ColoredCheckListBox* m_pokemonHmTmList7;
		ui::ColoredCheckListBox* m_pokemonHmTmList8;

		// Virtual event handlers, override them in your derived class
		virtual void OnPokemonSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPokemonEvolutionsButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPokemonLearnMovesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPokemonTMHMsButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		DatabasePanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 760,1800 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~DatabasePanelBase();

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
		wxTextCtrl* m_thirdPartyNoticesText;

	public:

		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GS 에디터 정보..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,540 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE );

		~AboutDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class EvolutionEditorDialogBase
///////////////////////////////////////////////////////////////////////////////
class EvolutionEditorDialogBase : public wxDialog
{
	private:

	protected:
		wxComboBox* m_pokemon;
		wxRadioButton* m_levelUpRadio;
		wxPanel* m_levelUpPanel;
		wxRadioButton* m_levelUpCommonRadio;
		wxSpinCtrlDouble* m_level;
		wxComboBox* m_levelTypeComboBox;
		wxRadioButton* m_happinessRadio;
		wxComboBox* m_happinessTypeComboBox;
		wxRadioButton* m_useItemRadio;
		wxPanel* m_useItemPanel;
		wxComboBox* m_useItems;
		wxRadioButton* m_tradeRadio;
		wxPanel* m_tradePanel;
		wxCheckBox* m_tradeGaveItemCheckBox;
		wxComboBox* m_tradeItems;

		// Virtual event handlers, override them in your derived class
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		EvolutionEditorDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 440,400 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU );

		~EvolutionEditorDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ProgressDialogBase
///////////////////////////////////////////////////////////////////////////////
class ProgressDialogBase : public wxDialog
{
	private:

	protected:
		wxGauge* m_progressGauge;
		wxStaticText* m_messageLabel;
		wxButton* m_cancelButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		ProgressDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,180 ), long style = wxCAPTION );

		~ProgressDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class BadDataDialogBase
///////////////////////////////////////////////////////////////////////////////
class BadDataDialogBase : public wxDialog
{
	private:

	protected:
		ui::ColoredListCtrl* m_badDataList;

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
/// Class ColorPickerPopupPanelBase
///////////////////////////////////////////////////////////////////////////////
class ColorPickerPopupPanelBase : public wxPanel
{
	private:

	protected:
		wxPanel* m_pickerPanel;
		wxPanel* m_previewPanel;
		wxSlider* m_brightnessSlider;
		wxPanel* m_brightnessPreviewPanel;
		wxSlider* m_redSlider;
		wxSpinCtrlDouble* m_redSpinCtrl;
		wxSlider* m_greenSlider;
		wxSpinCtrlDouble* m_greenSpinCtrl;
		wxSlider* m_blueSlider;
		wxSpinCtrlDouble* m_blueSpinCtrl;

		// Virtual event handlers, override them in your derived class
		virtual void OnPickerMouseEvent( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPickerPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnPreviewPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnBrightnessSlider( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBrightnessPreviewPaint( wxPaintEvent& event ) { event.Skip(); }


	public:

		ColorPickerPopupPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 290,328 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~ColorPickerPopupPanelBase();

};

