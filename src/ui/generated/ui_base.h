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
namespace ui{ class ImageEditorPanel; }
namespace ui{ class LabeledSeparator; }
namespace ui{ class MapEditorTreeCtrl; }

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/simplebook.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/checklst.h>
#include <wx/scrolwin.h>
#include <wx/radiobox.h>
#include <wx/notebook.h>
#include <wx/dialog.h>
#include <wx/statbmp.h>
#include <wx/html/htmlwin.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>

///////////////////////////////////////////////////////////////////////////

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
			wxID_DB,
			wxID_EMULATOR,
			wxID_DEBUG_LABEL,
			wxID_TEST_PLAY_SAVE,
			wxID_TRAINER_CARD_IMAGE,
		};

		wxMenuBar* m_mainMenuBar;
		wxMenuItem* m_fileSaveMenuItem;
		wxMenuItem* m_fileExportToIpsMenuItem;
		wxMenuItem* m_fileExportToXdeltaMenuItem;
		wxMenuItem* m_gameTestPlayMenuItem;
		wxMenuItem* m_gameDbMenuItem;
		wxMenuItem* m_gameSettingsEmulatorMenuItem;
		wxMenuItem* m_gameSettingsShowDebugLabelMenuItem;
		wxMenuItem* m_gameSettingsSaveMenuItem;
		wxMenuItem* m_gameSettingsTrainerCardImageMenuItem;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_saveToolbarItem;
		wxToolBarToolBase* m_dbToolbarItem;
		wxToolBarToolBase* m_testPlayToolbarItem;
		wxStatusBar* m_statusBar;
		wxSplitterWindow* m_mainSplitter;
		wxPanel* m_mapGroupPanel;
		ui::MapEditorTreeCtrl* m_mapGroupTreeCtrl;
		wxPanel* m_mapEditorPanel;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuItemSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,640 ), long style = wxCAPTION|wxCLOSE_BOX|wxICONIZE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainFrameBase();

		void m_mainSplitterOnIdle( wxIdleEvent& )
		{
			m_mainSplitter->SetSashPosition( 180 );
			m_mainSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrameBase::m_mainSplitterOnIdle ), NULL, this );
		}

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
			wxID_IMPORT = 6000,
			wxID_POKEMON_TMHMS_CHECK_ALL,
			wxID_POKEMON_TMHMS_CLEAR,
			wxID_CHECK_ALL,
		};

		ui::ColoredListBox* m_pokemonList;
		wxSimplebook* m_pokemonContainer;
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
		wxSimplebook* m_pokemonImageContainer;
		ui::ImageEditorPanel* m_pokemonFrontImage;
		ui::ImageEditorPanel* m_pokemonBackImage;
		ui::ImageEditorPanel* m_pokemonShinyFrontImage;
		ui::ImageEditorPanel* m_pokemonShinyBackImage;
		ui::ColorPickerPanel* m_pokemonColor_1;
		ui::ColorPickerPanel* m_pokemonColor_2;
		ui::ColorPickerPanel* m_pokemonShinyColor_1;
		ui::ColorPickerPanel* m_pokemonShinyColor_2;
		ui::ImageEditorPanel* m_pokemonFootprintImage;
		ui::ImageEditorPanel* m_pokemonSmallPicture;
		wxComboBox* m_pokemonSmallPictureColorComboBox;
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
		ui::ColoredListCtrl* m_pokemonMovesList;
		wxButton* m_pokemonMovesImport;
		wxButton* m_pokemonMovesAdd;
		wxButton* m_pokemonMovesModify;
		wxButton* m_pokemonMovesRemove;
		wxButton* m_pokemonMovesClear;
		ui::ColoredListCtrl* m_pokemonEggMovesList;
		wxButton* m_pokemonEggMovesAdd;
		wxButton* m_pokemonEggMovesModify;
		wxButton* m_pokemonEggMovesRemove;
		wxButton* m_pokemonEggMovesClear;
		wxGridSizer* m_pokemonTMHMsSizer;
		ui::ColoredCheckListBox* m_pokemonHmTmList1;
		ui::ColoredCheckListBox* m_pokemonHmTmList2;
		ui::ColoredCheckListBox* m_pokemonHmTmList3;
		ui::ColoredCheckListBox* m_pokemonHmTmList4;
		ui::ColoredCheckListBox* m_pokemonHmTmList5;
		ui::ColoredCheckListBox* m_pokemonHmTmList6;
		ui::ColoredCheckListBox* m_pokemonHmTmList7;
		ui::ColoredCheckListBox* m_pokemonHmTmList8;
		wxTextCtrl* m_pokemonEggNameText;
		ui::ImageEditorPanel* m_pokemonEggImage;
		ui::ColorPickerPanel* m_pokemonEggColor_1;
		ui::ColorPickerPanel* m_pokemonEggColor_2;
		ui::ColorPickerPanel* m_pokemonEggShinyColor_1;
		ui::ColorPickerPanel* m_pokemonEggShinyColor_2;
		ui::ImageEditorPanel* m_pokemonEggSmallPicture;
		wxComboBox* m_pokemonEggSmallPictureColorComboBox;
		wxComboBox* m_unownPokemonComboBox;
		wxPanel* m_unownInnerPanel;
		ui::ColoredListBox* m_unownList;
		wxPanel* m_unownContainer;
		ui::ImageEditorPanel* m_unownFrontImage;
		ui::ImageEditorPanel* m_unownBackImage;
		ui::ImageEditorPanel* m_unownShinyFrontImage;
		ui::ImageEditorPanel* m_unownShinyBackImage;
		ui::ColorPickerPanel* m_unownColor_1;
		ui::ColorPickerPanel* m_unownColor_2;
		ui::ColorPickerPanel* m_unownShinyColor_1;
		ui::ColorPickerPanel* m_unownShinyColor_2;
		ui::ColoredListBox* m_itemList;
		wxScrolledWindow* m_itemContainer;
		wxComboBox* m_itemPrimaryGroupComboBox;
		wxTextCtrl* m_itemPrimaryNameText;
		wxSpinCtrlDouble* m_itemPrimaryPriceSpinCtrl;
		wxStaticText* m_itemPrimaryDescriptionLabel;
		wxTextCtrl* m_itemPrimaryDescriptionText;
		wxComboBox* m_itemFieldMenuComboBox;
		wxComboBox* m_itemBattleMenuComboBox;
		wxComboBox* m_itemEtcEffectComboBox;
		wxComboBox* m_itemEtcRegisterComboBox;
		wxSpinCtrlDouble* m_itemEtcValueSpinCtrl;
		ui::ColoredListBox* m_moveList;
		wxScrolledWindow* m_moveContainer;
		wxTextCtrl* m_movePrimaryNumberText;
		wxTextCtrl* m_movePrimaryNameText;
		wxComboBox* m_movePrimaryTypeComboBox;
		wxSpinCtrlDouble* m_movePrimaryPowerSpinCtrl;
		wxSpinCtrlDouble* m_movePrimaryAccuracySpinCtrl;
		wxStaticText* m_movePrimaryAccuracyPercentageLabel;
		wxSpinCtrlDouble* m_movePrimaryPPSpinCtrl;
		wxStaticText* m_movePrimaryDescriptionLabel;
		wxTextCtrl* m_movePrimaryDescriptionText;
		wxComboBox* m_moveEffectTypeComboBox;
		wxSpinCtrlDouble* m_moveEffectValueSpinCtrl;
		ui::ColoredListBox* m_tmhmList;
		wxScrolledWindow* m_tmhmContainer;
		wxComboBox* m_tmhmMoveComboBox;
		wxButton* tmhmPokemonClearButton;
		ui::ColoredCheckListBox* m_tmhmPokemonList;
		ui::ColoredListBox* m_trainerGroupList;
		wxScrolledWindow* m_trainerGroupContainer;
		wxTextCtrl* m_trainerGroupNameText;
		wxSimplebook* m_trainerGroupImageContainer;
		ui::ImageEditorPanel* m_trainerGroupImage;
		ui::ColorPickerPanel* m_trainerGroupColor_1;
		ui::ColorPickerPanel* m_trainerGroupColor_2;
		wxStaticText* m_trainerGroupImageWarningLabel;
		wxPanel* m_trainerGroupBackImagePanel;
		ui::ImageEditorPanel* m_trainerGroupBackImage_1;
		ui::ImageEditorPanel* m_trainerGroupBackImage_2;
		ui::ColorPickerPanel* m_trainerGroupBackColor_1;
		ui::ColorPickerPanel* m_trainerGroupBackColor_2;
		ui::ColoredListBox* m_typeList;
		wxScrolledWindow* m_typeContainer;
		wxTextCtrl* m_typeNameText;
		ui::ColoredListCtrl* m_typeMatchupList;
		wxButton* m_typeMatchupsAddButton;
		wxButton* m_typeMatchupsEditButton;
		wxButton* m_typeMatchupsRemoveButton;
		wxButton* m_typeMatchupsClearButton;
		wxRadioBox* m_typeWeatherModifierRainRadioBox;
		wxRadioBox* m_typeWeatherModifierSunRadioBox;
		wxRadioBox* m_typeWeatherModifierSandstormRadioBox;

		// Virtual event handlers, override them in your derived class
		virtual void OnPokemonEvolutionsButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPokemonMovesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPokemonEggMovesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPokemonTMHMsButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTMHMsButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeMatchupsButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeWeatherModifierRadioBox( wxCommandEvent& event ) { event.Skip(); }


	public:

		DatabasePanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 760,2500 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~DatabasePanelBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DatabaseDialogBase
///////////////////////////////////////////////////////////////////////////////
class DatabaseDialogBase : public wxDialog
{
	private:

	protected:

		// Virtual event handlers, override them in your derived class
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		DatabaseDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("데이터베이스"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 760,600 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~DatabaseDialogBase();

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

		// Virtual event handlers, override them in your derived class
		virtual void OnOkButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GS 에디터 정보"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 624,540 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE );

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
/// Class MoveEditorDialogBase
///////////////////////////////////////////////////////////////////////////////
class MoveEditorDialogBase : public wxDialog
{
	private:

	protected:
		wxFlexGridSizer* m_contentGrid;
		wxStaticText* m_levelLabel;
		wxSpinCtrlDouble* m_levelSpinCtrl;
		wxComboBox* m_movesComboBox;

		// Virtual event handlers, override them in your derived class
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		MoveEditorDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 240,162 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU );

		~MoveEditorDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TypeMatchupEditorDialogBase
///////////////////////////////////////////////////////////////////////////////
class TypeMatchupEditorDialogBase : public wxDialog
{
	private:

	protected:
		wxComboBox* m_typeComboBox;
		wxComboBox* m_effectivenessComboBox;
		wxCheckBox* m_foresightCheckBox;

		// Virtual event handlers, override them in your derived class
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		TypeMatchupEditorDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("{title}"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 285,186 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU );

		~TypeMatchupEditorDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ImportMoveDialogBase
///////////////////////////////////////////////////////////////////////////////
class ImportMoveDialogBase : public wxDialog
{
	private:

	protected:
		ui::ColoredListBox* m_pokemonListBox;
		ui::ColoredListCtrl* m_movesListCtrl;
		wxButton* m_ignoreButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnIgnoreButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		ImportMoveDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("가져오기..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,400 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~ImportMoveDialogBase();

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
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		BadDataDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("데이터 손상 알림"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 560,440 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~BadDataDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SearchDialogBase
///////////////////////////////////////////////////////////////////////////////
class SearchDialogBase : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_keywordText;
		ui::ColoredListCtrl* m_list;
		wxButton* m_confirmButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnKeywordTextChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConfirmButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		SearchDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("찾기..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,400 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~SearchDialogBase();

};

