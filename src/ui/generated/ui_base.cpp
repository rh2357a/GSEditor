///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui/ui.h"

#include "ui_base.h"

#include "icon_about.png.h"
#include "icon_exit.png.h"
#include "icon_folder.png.h"
#include "icon_play.png.h"
#include "icon_save.png.h"

///////////////////////////////////////////////////////////////////////////

ColorPickerPopupPanelBase::ColorPickerPopupPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* topPickerSizer;
	topPickerSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pickerPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 240,160 ), wxBORDER_STATIC|wxTAB_TRAVERSAL );
	m_pickerPanel->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_pickerPanel->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	topPickerSizer->Add( m_pickerPanel, 0, wxALL, 0 );


	topPickerSizer->Add( 4, 0, 0, 0, 0 );

	m_previewPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 40,160 ), wxBORDER_STATIC|wxTAB_TRAVERSAL );
	m_previewPanel->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_previewPanel->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	topPickerSizer->Add( m_previewPanel, 0, wxALL, 0 );


	panelSizer->Add( topPickerSizer, 0, wxALL|wxEXPAND, 4 );

	m_brightnessSlider = new wxSlider( this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	panelSizer->Add( m_brightnessSlider, 0, wxEXPAND, 5 );

	m_brightnessPreviewPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxTAB_TRAVERSAL );
	m_brightnessPreviewPanel->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_brightnessPreviewPanel->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	panelSizer->Add( m_brightnessPreviewPanel, 1, wxEXPAND|wxLEFT|wxRIGHT, 12 );

	wxStaticLine* separator_0;
	separator_0 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	panelSizer->Add( separator_0, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* redSizer;
	redSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* redLabel;
	redLabel = new wxStaticText( this, wxID_ANY, wxT("R"), wxDefaultPosition, wxSize( 10,-1 ), 0 );
	redLabel->Wrap( -1 );
	redSizer->Add( redLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_redSlider = new wxSlider( this, wxID_ANY, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_BOTH|wxSL_HORIZONTAL );
	redSizer->Add( m_redSlider, 1, wxALIGN_CENTER_VERTICAL, 8 );

	m_redSpinCtrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 56,-1 ), wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_redSpinCtrl->SetDigits( 0 );
	redSizer->Add( m_redSpinCtrl, 0, wxALL, 5 );


	panelSizer->Add( redSizer, 0, wxEXPAND, 0 );

	wxBoxSizer* greenSizer;
	greenSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* greenLabel;
	greenLabel = new wxStaticText( this, wxID_ANY, wxT("G"), wxDefaultPosition, wxSize( 10,-1 ), 0 );
	greenLabel->Wrap( -1 );
	greenSizer->Add( greenLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_greenSlider = new wxSlider( this, wxID_ANY, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_BOTH|wxSL_HORIZONTAL );
	greenSizer->Add( m_greenSlider, 1, wxALIGN_CENTER_VERTICAL, 8 );

	m_greenSpinCtrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 56,-1 ), wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_greenSpinCtrl->SetDigits( 0 );
	greenSizer->Add( m_greenSpinCtrl, 0, wxALL, 5 );


	panelSizer->Add( greenSizer, 0, wxEXPAND, 5 );

	wxBoxSizer* blueSizer;
	blueSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* blueLabel;
	blueLabel = new wxStaticText( this, wxID_ANY, wxT("B"), wxDefaultPosition, wxSize( 10,-1 ), 0 );
	blueLabel->Wrap( -1 );
	blueSizer->Add( blueLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_blueSlider = new wxSlider( this, wxID_ANY, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_BOTH|wxSL_HORIZONTAL );
	blueSizer->Add( m_blueSlider, 1, wxALIGN_CENTER_VERTICAL, 8 );

	m_blueSpinCtrl = new wxSpinCtrlDouble( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 56,-1 ), wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_blueSpinCtrl->SetDigits( 0 );
	blueSizer->Add( m_blueSpinCtrl, 0, wxALL, 5 );


	panelSizer->Add( blueSizer, 0, wxEXPAND, 5 );


	this->SetSizer( panelSizer );
	this->Layout();

	// Connect Events
	m_pickerPanel->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_MIDDLE_UP, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_AUX1_DOWN, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_AUX1_UP, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_AUX2_DOWN, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_AUX1_UP, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_MOTION, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_AUX1_DCLICK, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_AUX2_DCLICK, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( ColorPickerPopupPanelBase::OnPickerMouseEvent ), NULL, this );
	m_pickerPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( ColorPickerPopupPanelBase::OnPickerPaint ), NULL, this );
	m_previewPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( ColorPickerPopupPanelBase::OnPreviewPaint ), NULL, this );
	m_brightnessSlider->Connect( wxEVT_SLIDER, wxCommandEventHandler( ColorPickerPopupPanelBase::OnBrightnessSlider ), NULL, this );
	m_brightnessPreviewPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( ColorPickerPopupPanelBase::OnBrightnessPreviewPaint ), NULL, this );
}

ColorPickerPopupPanelBase::~ColorPickerPopupPanelBase()
{
}

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 740,600 ), wxDefaultSize );

	m_mainMenuBar = new wxMenuBar( 0 );
	wxMenu* fileMenu;
	fileMenu = new wxMenu();
	wxMenuItem* fileOpenMenuItem;
	fileOpenMenuItem = new wxMenuItem( fileMenu, wxID_OPEN, wxString( wxT("열기(&O)...") ) + wxT('\t') + wxT("Ctrl+O"), wxT("롬 파일을 엽니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	fileOpenMenuItem->SetBitmaps( icon_folder_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	fileOpenMenuItem->SetBitmap( icon_folder_png_to_wx_bitmap() );
	#endif
	fileMenu->Append( fileOpenMenuItem );

	m_fileSaveMenuItem = new wxMenuItem( fileMenu, wxID_SAVE, wxString( wxT("저장(&S)") ) + wxT('\t') + wxT("Ctrl+S"), wxT("열린 롬 파일을 저장합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileSaveMenuItem->SetBitmaps( icon_save_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileSaveMenuItem->SetBitmap( icon_save_png_to_wx_bitmap() );
	#endif
	fileMenu->Append( m_fileSaveMenuItem );

	fileMenu->AppendSeparator();

	m_fileExportToIpsMenuItem = new wxMenuItem( fileMenu, wxID_IPS, wxString( wxT("ips 패치 생성...") ) , wxT("ips 형식의 패치 파일을 생성합니다."), wxITEM_NORMAL );
	fileMenu->Append( m_fileExportToIpsMenuItem );

	m_fileExportToXdeltaMenuItem = new wxMenuItem( fileMenu, wxID_XDELTA, wxString( wxT("xdelta 패치 생성...") ) , wxT("xdelta 형식의 패치 파일을 생성합니다."), wxITEM_NORMAL );
	fileMenu->Append( m_fileExportToXdeltaMenuItem );

	fileMenu->AppendSeparator();

	wxMenuItem* fileExitMenuItem;
	fileExitMenuItem = new wxMenuItem( fileMenu, wxID_EXIT, wxString( wxT("닫기(&X)") ) + wxT('\t') + wxT("Alt+F4"), wxT("프로그램을 종료합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	fileExitMenuItem->SetBitmaps( icon_exit_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	fileExitMenuItem->SetBitmap( icon_exit_png_to_wx_bitmap() );
	#endif
	fileMenu->Append( fileExitMenuItem );

	m_mainMenuBar->Append( fileMenu, wxT("파일(&F)") );

	wxMenu* gameMenu;
	gameMenu = new wxMenu();
	m_gameTestPlayMenuItem = new wxMenuItem( gameMenu, wxID_TEST_PLAY, wxString( wxT("테스트 플레이(&P)") ) + wxT('\t') + wxT("F5"), wxT("롬을 빌드하여 테스트합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_gameTestPlayMenuItem->SetBitmaps( icon_play_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_gameTestPlayMenuItem->SetBitmap( icon_play_png_to_wx_bitmap() );
	#endif
	gameMenu->Append( m_gameTestPlayMenuItem );

	wxMenu* gameSettingsSubMenu;
	gameSettingsSubMenu = new wxMenu();
	wxMenuItem* gameSettingsSubMenuItem = new wxMenuItem( gameMenu, wxID_ANY, wxT("설정"), wxEmptyString, wxITEM_NORMAL, gameSettingsSubMenu );
	#if (defined( __WXMSW__ ) || defined( __WXGTK__ ) || defined( __WXOSX__ ))
	gameSettingsSubMenuItem->SetBitmap( wxNullBitmap );
	#endif

	m_gameSettingsEmulatorMenuItem = new wxMenuItem( gameSettingsSubMenu, wxID_EMULATOR, wxString( wxT("에뮬레이터 설정(&E)...") ) , wxEmptyString, wxITEM_NORMAL );
	gameSettingsSubMenu->Append( m_gameSettingsEmulatorMenuItem );

	gameSettingsSubMenu->AppendSeparator();

	m_gameSettingsShowDebugLabelMenuItem = new wxMenuItem( gameSettingsSubMenu, wxID_DEBUG_LABEL, wxString( wxT("디버그 라벨(&D)") ) , wxT("디버거에서 롬 파일에 기록된 라벨을 표시합니다."), wxITEM_CHECK );
	gameSettingsSubMenu->Append( m_gameSettingsShowDebugLabelMenuItem );

	m_gameSettingsSaveMenuItem = new wxMenuItem( gameSettingsSubMenu, wxID_TEST_PLAY_SAVE, wxString( wxT("테스트 플레이 세이브(&S)") ) , wxT("테스트 플레이 도중 세이브 시, 세이브 파일에 기록이 가능하도록 합니다. (권장: 켜기)"), wxITEM_CHECK );
	gameSettingsSubMenu->Append( m_gameSettingsSaveMenuItem );

	gameSettingsSubMenu->AppendSeparator();

	m_gameSettingsTrainerCardImageMenuItem = new wxMenuItem( gameSettingsSubMenu, wxID_TRAINER_CARD_IMAGE, wxString( wxT("플레이어 이미지를 트레이너 카드에 적용") ) , wxT("트레이너 이미지를 트레이너 카드에 적용합니다. (권장: 켜기)"), wxITEM_CHECK );
	gameSettingsSubMenu->Append( m_gameSettingsTrainerCardImageMenuItem );

	gameMenu->Append( gameSettingsSubMenuItem );

	m_mainMenuBar->Append( gameMenu, wxT("게임(&G)") );

	wxMenu* helpMenu;
	helpMenu = new wxMenu();
	wxMenuItem* helpAboutMenuItem;
	helpAboutMenuItem = new wxMenuItem( helpMenu, wxID_ABOUT, wxString( wxT("GS 에디터 정보(&A)...") ) , wxT("프로그램의 정보를 봅니다."), wxITEM_NORMAL );
	helpMenu->Append( helpAboutMenuItem );

	m_mainMenuBar->Append( helpMenu, wxT("도움말(&H)") );

	this->SetMenuBar( m_mainMenuBar );

	m_toolBar = this->CreateToolBar( wxTB_DEFAULT_STYLE|wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY );
	m_toolBar->SetToolSeparation( 25 );
	wxToolBarToolBase* openToolbarItem;
	openToolbarItem = m_toolBar->AddTool( wxID_OPEN, wxT("open"), icon_folder_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("롬 파일을 엽니다."), NULL );

	m_saveToolbarItem = m_toolBar->AddTool( wxID_SAVE, wxT("save"), icon_save_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("열린 롬 파일을 저장합니다."), NULL );

	m_toolBar->AddSeparator();

	m_testPlayToolbarItem = m_toolBar->AddTool( wxID_TEST_PLAY, wxT("save"), icon_play_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("롬을 빌드하여 테스트합니다."), NULL );

	m_toolBar->AddSeparator();

	wxToolBarToolBase* exitToolbarItem;
	exitToolbarItem = m_toolBar->AddTool( wxID_EXIT, wxT("exit"), icon_exit_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("프로그램을 종료합니다."), NULL );

	m_toolBar->Realize();

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	m_mainPanel = new ui::DatabasePanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	mainSizer->Add( m_mainPanel, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnClose ) );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, fileOpenMenuItem->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileSaveMenuItem->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExportToIpsMenuItem->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExportToXdeltaMenuItem->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, fileExitMenuItem->GetId());
	gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_gameTestPlayMenuItem->GetId());
	gameSettingsSubMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_gameSettingsEmulatorMenuItem->GetId());
	gameSettingsSubMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuItemSelected ), this, m_gameSettingsShowDebugLabelMenuItem->GetId());
	gameSettingsSubMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuItemSelected ), this, m_gameSettingsSaveMenuItem->GetId());
	gameSettingsSubMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuItemSelected ), this, m_gameSettingsTrainerCardImageMenuItem->GetId());
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, helpAboutMenuItem->GetId());
	this->Connect( openToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_saveToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_testPlayToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( exitToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
}

MainFrameBase::~MainFrameBase()
{
}

DatabasePanelBase::DatabasePanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer( wxVERTICAL );

	wxNotebook* mainTabs;
	mainTabs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* pokemonPanel;
	pokemonPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonPanelSizer;
	pokemonPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* pokemonInnerPanel;
	pokemonInnerPanel = new wxPanel( pokemonPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonInnerPanelSizer;
	pokemonInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonList = new ui::ColoredListBox( pokemonInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 128,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	pokemonInnerPanelSizer->Add( m_pokemonList, 0, wxALL|wxEXPAND, 2 );

	m_pokemonContainer = new wxSimplebook( pokemonInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC );
	wxScrolledWindow* pokemonPokemonType;
	pokemonPokemonType = new wxScrolledWindow( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL );
	pokemonPokemonType->SetScrollRate( 5, 16 );
	pokemonPokemonType->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* pokemonPokemonTypeSizer;
	pokemonPokemonTypeSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* pokemonStatsLabel;
	pokemonStatsLabel = new ui::LabeledSeparator( pokemonPokemonType, wxID_ANY, wxT("기본 정보 && 능력치"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsLabel->Wrap( -1 );
	pokemonPokemonTypeSizer->Add( pokemonStatsLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* pokemonStatsSizer;
	pokemonStatsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxFlexGridSizer* pokemonInfoGrid;
	pokemonInfoGrid = new wxFlexGridSizer( 7, 2, 0, 0 );
	pokemonInfoGrid->AddGrowableCol( 0 );
	pokemonInfoGrid->SetFlexibleDirection( wxBOTH );
	pokemonInfoGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonNoLabel;
	pokemonNoLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("번호："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonNoLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonNoLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonNoText = new wxTextCtrl( pokemonPokemonType, wxID_ANY, wxT("-"), wxDefaultPosition, wxSize( 240,-1 ), wxTE_READONLY );
	#ifdef __WXGTK__
	if ( !m_pokemonNoText->HasFlag( wxTE_MULTILINE ) )
	{
	m_pokemonNoText->SetMaxLength( 5 );
	}
	#else
	m_pokemonNoText->SetMaxLength( 5 );
	#endif
	m_pokemonNoText->SetMinSize( wxSize( 240,-1 ) );
	m_pokemonNoText->SetMaxSize( wxSize( 240,-1 ) );

	pokemonInfoGrid->Add( m_pokemonNoText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 4 );

	wxStaticText* pokemonNameLabel;
	pokemonNameLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("이름："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonNameLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonNameText = new wxTextCtrl( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_pokemonNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_pokemonNameText->SetMaxLength( 5 );
	}
	#else
	m_pokemonNameText->SetMaxLength( 5 );
	#endif
	m_pokemonNameText->SetMinSize( wxSize( 240,-1 ) );
	m_pokemonNameText->SetMaxSize( wxSize( 240,-1 ) );

	pokemonInfoGrid->Add( m_pokemonNameText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 4 );

	wxStaticText* pokemonGenderRateLabel;
	pokemonGenderRateLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("성비율："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonGenderRateLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonGenderRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonGenderRateComboBox = new wxComboBox( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonGenderRateComboBox->Append( wxT("00.0% (수컷)") );
	m_pokemonGenderRateComboBox->Append( wxT("12.5%") );
	m_pokemonGenderRateComboBox->Append( wxT("25.0%") );
	m_pokemonGenderRateComboBox->Append( wxT("37.5%") );
	m_pokemonGenderRateComboBox->Append( wxT("50% (중간)") );
	m_pokemonGenderRateComboBox->Append( wxT("62.5%") );
	m_pokemonGenderRateComboBox->Append( wxT("75.0%") );
	m_pokemonGenderRateComboBox->Append( wxT("87.5%") );
	m_pokemonGenderRateComboBox->Append( wxT("100% (암컷)") );
	m_pokemonGenderRateComboBox->Append( wxT("없음") );
	m_pokemonGenderRateComboBox->SetFont( wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_pokemonGenderRateComboBox->SetMinSize( wxSize( 240,-1 ) );
	m_pokemonGenderRateComboBox->SetMaxSize( wxSize( 240,-1 ) );

	pokemonInfoGrid->Add( m_pokemonGenderRateComboBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 4 );

	wxStaticText* pokemonGrowthRateLabel;
	pokemonGrowthRateLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("성장률："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonGrowthRateLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonGrowthRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonGrowthRateComboBox = new wxComboBox( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonGrowthRateComboBox->Append( wxT("중간 빠름 (125 ~ 1,000,000)") );
	m_pokemonGrowthRateComboBox->Append( wxT("약간 빠름 (313 ~ 849,970)") );
	m_pokemonGrowthRateComboBox->Append( wxT("약간 느림 (523 ~ 949,930)") );
	m_pokemonGrowthRateComboBox->Append( wxT("중간 느림 (135 ~ 1,059,860)") );
	m_pokemonGrowthRateComboBox->Append( wxT("빠름 (100 ~ 800,000)") );
	m_pokemonGrowthRateComboBox->Append( wxT("느림 (156 ~ 1,250,000)") );
	m_pokemonGrowthRateComboBox->SetFont( wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_pokemonGrowthRateComboBox->SetMinSize( wxSize( 240,-1 ) );
	m_pokemonGrowthRateComboBox->SetMaxSize( wxSize( 240,-1 ) );

	pokemonInfoGrid->Add( m_pokemonGrowthRateComboBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 4 );

	wxStaticText* pokemonTypeLabel;
	pokemonTypeLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("타입："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTypeLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonTypeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxPanel* pokemonTypePanel;
	pokemonTypePanel = new wxPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( 240,-1 ), wxTAB_TRAVERSAL );
	pokemonTypePanel->SetMinSize( wxSize( 240,-1 ) );
	pokemonTypePanel->SetMaxSize( wxSize( 240,-1 ) );

	wxBoxSizer* pokemonTypeSizer;
	pokemonTypeSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonType1ComboBox = new wxComboBox( pokemonTypePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 118,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonType1ComboBox->SetMinSize( wxSize( 118,-1 ) );
	m_pokemonType1ComboBox->SetMaxSize( wxSize( 118,-1 ) );

	pokemonTypeSizer->Add( m_pokemonType1ComboBox, 0, wxALL, 0 );


	pokemonTypeSizer->Add( 4, 0, 0, 0, 0 );

	m_pokemonType2ComboBox = new wxComboBox( pokemonTypePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 118,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonType2ComboBox->SetMinSize( wxSize( 118,-1 ) );
	m_pokemonType2ComboBox->SetMaxSize( wxSize( 118,-1 ) );

	pokemonTypeSizer->Add( m_pokemonType2ComboBox, 0, wxALL, 0 );


	pokemonTypePanel->SetSizer( pokemonTypeSizer );
	pokemonTypePanel->Layout();
	pokemonInfoGrid->Add( pokemonTypePanel, 0, wxALL, 4 );

	wxStaticText* pokemonItemsLabel;
	pokemonItemsLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("지닌물건："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonItemsLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonItemsLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxPanel* pokemonItemsPanel;
	pokemonItemsPanel = new wxPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( 240,-1 ), wxTAB_TRAVERSAL );
	pokemonItemsPanel->SetMinSize( wxSize( 240,-1 ) );
	pokemonItemsPanel->SetMaxSize( wxSize( 240,-1 ) );

	wxBoxSizer* pokemonItemsSizer;
	pokemonItemsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonItem1ComboBox = new wxComboBox( pokemonItemsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 118,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonItem1ComboBox->SetMinSize( wxSize( 118,-1 ) );
	m_pokemonItem1ComboBox->SetMaxSize( wxSize( 118,-1 ) );

	pokemonItemsSizer->Add( m_pokemonItem1ComboBox, 0, wxALL, 0 );


	pokemonItemsSizer->Add( 4, 0, 0, 0, 0 );

	m_pokemonItem2ComboBox = new wxComboBox( pokemonItemsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 118,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonItem2ComboBox->SetMinSize( wxSize( 118,-1 ) );
	m_pokemonItem2ComboBox->SetMaxSize( wxSize( 118,-1 ) );

	pokemonItemsSizer->Add( m_pokemonItem2ComboBox, 0, wxALL, 0 );


	pokemonItemsPanel->SetSizer( pokemonItemsSizer );
	pokemonItemsPanel->Layout();
	pokemonInfoGrid->Add( pokemonItemsPanel, 0, wxALL, 4 );

	wxStaticText* pokemonEggGroupLabel;
	pokemonEggGroupLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("알 그룹："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggGroupLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonEggGroupLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxPanel* pokemonEggGroupPanel;
	pokemonEggGroupPanel = new wxPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( 240,-1 ), wxTAB_TRAVERSAL );
	pokemonEggGroupPanel->SetMinSize( wxSize( 240,-1 ) );
	pokemonEggGroupPanel->SetMaxSize( wxSize( 240,-1 ) );

	wxBoxSizer* pokemonEggGroupSizer;
	pokemonEggGroupSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonEggGroup1ComboBox = new wxComboBox( pokemonEggGroupPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 118,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonEggGroup1ComboBox->Append( wxT("괴물") );
	m_pokemonEggGroup1ComboBox->Append( wxT("양서류") );
	m_pokemonEggGroup1ComboBox->Append( wxT("벌레") );
	m_pokemonEggGroup1ComboBox->Append( wxT("비행") );
	m_pokemonEggGroup1ComboBox->Append( wxT("땅") );
	m_pokemonEggGroup1ComboBox->Append( wxT("요정") );
	m_pokemonEggGroup1ComboBox->Append( wxT("식물") );
	m_pokemonEggGroup1ComboBox->Append( wxT("인간형") );
	m_pokemonEggGroup1ComboBox->Append( wxT("뱀") );
	m_pokemonEggGroup1ComboBox->Append( wxT("광물") );
	m_pokemonEggGroup1ComboBox->Append( wxT("불완전") );
	m_pokemonEggGroup1ComboBox->Append( wxT("물고기") );
	m_pokemonEggGroup1ComboBox->Append( wxT("메타몽") );
	m_pokemonEggGroup1ComboBox->Append( wxT("드래곤") );
	m_pokemonEggGroup1ComboBox->Append( wxT("불명") );
	m_pokemonEggGroup1ComboBox->SetMinSize( wxSize( 118,-1 ) );
	m_pokemonEggGroup1ComboBox->SetMaxSize( wxSize( 118,-1 ) );

	pokemonEggGroupSizer->Add( m_pokemonEggGroup1ComboBox, 0, wxALL, 0 );


	pokemonEggGroupSizer->Add( 4, 0, 0, 0, 0 );

	m_pokemonEggGroup2ComboBox = new wxComboBox( pokemonEggGroupPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 118,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonEggGroup2ComboBox->Append( wxT("괴물") );
	m_pokemonEggGroup2ComboBox->Append( wxT("양서류") );
	m_pokemonEggGroup2ComboBox->Append( wxT("벌레") );
	m_pokemonEggGroup2ComboBox->Append( wxT("비행") );
	m_pokemonEggGroup2ComboBox->Append( wxT("땅") );
	m_pokemonEggGroup2ComboBox->Append( wxT("요정") );
	m_pokemonEggGroup2ComboBox->Append( wxT("식물") );
	m_pokemonEggGroup2ComboBox->Append( wxT("인간형") );
	m_pokemonEggGroup2ComboBox->Append( wxT("뱀") );
	m_pokemonEggGroup2ComboBox->Append( wxT("광물") );
	m_pokemonEggGroup2ComboBox->Append( wxT("불완전") );
	m_pokemonEggGroup2ComboBox->Append( wxT("물고기") );
	m_pokemonEggGroup2ComboBox->Append( wxT("메타몽") );
	m_pokemonEggGroup2ComboBox->Append( wxT("드래곤") );
	m_pokemonEggGroup2ComboBox->Append( wxT("불명") );
	m_pokemonEggGroup2ComboBox->SetMinSize( wxSize( 118,-1 ) );
	m_pokemonEggGroup2ComboBox->SetMaxSize( wxSize( 118,-1 ) );

	pokemonEggGroupSizer->Add( m_pokemonEggGroup2ComboBox, 0, wxALL, 0 );


	pokemonEggGroupPanel->SetSizer( pokemonEggGroupSizer );
	pokemonEggGroupPanel->Layout();
	pokemonInfoGrid->Add( pokemonEggGroupPanel, 0, wxALL, 4 );


	pokemonStatsSizer->Add( pokemonInfoGrid, 0, 0, 5 );


	pokemonStatsSizer->Add( 8, 0, 0, wxEXPAND, 5 );

	wxFlexGridSizer* pokemonStatsGrid;
	pokemonStatsGrid = new wxFlexGridSizer( 8, 3, 0, 0 );
	pokemonStatsGrid->AddGrowableCol( 1 );
	pokemonStatsGrid->SetFlexibleDirection( wxBOTH );
	pokemonStatsGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonStatsHpLabel;
	pokemonStatsHpLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("HP："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsHpLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsHpLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsHpValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0.000000, 1 );
	m_pokemonStatsHpValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsHpValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsAtkLabel;
	pokemonStatsAtkLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("공격："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsAtkLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsAtkLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsAtkValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsAtkValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsAtkValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsDefLabel;
	pokemonStatsDefLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("방어："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsDefLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsDefLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsDefValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsDefValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsDefValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpAtkLabel;
	pokemonStatsSpAtkLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("특수공격："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpAtkLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpAtkLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpAtkValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpAtkValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpAtkValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpDefHpLabel;
	pokemonStatsSpDefHpLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("특수방어："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpDefHpLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpDefHpLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpDefValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpDefValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpDefValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpdLabel;
	pokemonStatsSpdLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("스피드："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpdLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpdLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpdValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpdValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpdValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsExpLabel;
	pokemonStatsExpLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("경험치："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsExpLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsExpLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsExpValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsExpValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsExpValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsCatchRateLabel;
	pokemonStatsCatchRateLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("포획률："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsCatchRateLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsCatchRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsCatchRateValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsCatchRateValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsCatchRateValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	m_pokemonCatchRatePercentage = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("(0.00%)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonCatchRatePercentage->Wrap( -1 );
	pokemonStatsGrid->Add( m_pokemonCatchRatePercentage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonStatsSizer->Add( pokemonStatsGrid, 0, 0, 5 );


	pokemonPokemonTypeSizer->Add( pokemonStatsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonPokemonTypeSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* pokemonImageLabel;
	pokemonImageLabel = new ui::LabeledSeparator( pokemonPokemonType, wxID_ANY, wxT("이미지 && 색상"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonImageLabel->Wrap( -1 );
	pokemonPokemonTypeSizer->Add( pokemonImageLabel, 0, wxALL|wxEXPAND, 5 );

	m_pokemonImageContainer = new wxSimplebook( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* pokemonImageCommonTypePanel;
	pokemonImageCommonTypePanel = new wxPanel( m_pokemonImageContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonImageCommonSizer;
	pokemonImageCommonSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* pokemonImageSizer;
	pokemonImageSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonImageDataLabel;
	pokemonImageDataLabel = new wxStaticText( pokemonImageCommonTypePanel, wxID_ANY, wxT("이미지："), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	pokemonImageDataLabel->Wrap( -1 );
	pokemonImageSizer->Add( pokemonImageDataLabel, 0, wxALL, 5 );

	m_pokemonFrontImage = new ui::ImageEditorPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonImageSizer->Add( m_pokemonFrontImage, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_pokemonBackImage = new ui::ImageEditorPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonImageSizer->Add( m_pokemonBackImage, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	wxStaticLine* pokemonImageSeparator;
	pokemonImageSeparator = new wxStaticLine( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	pokemonImageSizer->Add( pokemonImageSeparator, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxTOP, 5 );

	m_pokemonShinyFrontImage = new ui::ImageEditorPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonImageSizer->Add( m_pokemonShinyFrontImage, 1, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_pokemonShinyBackImage = new ui::ImageEditorPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonImageSizer->Add( m_pokemonShinyBackImage, 1, wxBOTTOM|wxLEFT|wxTOP, 5 );


	pokemonImageCommonSizer->Add( pokemonImageSizer, 0, wxLEFT|wxRIGHT|wxTOP, 5 );

	wxBoxSizer* pokemonColorSizer;
	pokemonColorSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonColorLabel;
	pokemonColorLabel = new wxStaticText( pokemonImageCommonTypePanel, wxID_ANY, wxT("색상："), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	pokemonColorLabel->Wrap( -1 );
	pokemonColorSizer->Add( pokemonColorLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonColor_1 = new ui::ColorPickerPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonColorSizer->Add( m_pokemonColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_pokemonColor_2 = new ui::ColorPickerPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonColorSizer->Add( m_pokemonColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	wxStaticLine* pokemonColorSeparator;
	pokemonColorSeparator = new wxStaticLine( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	pokemonColorSizer->Add( pokemonColorSeparator, 0, wxEXPAND|wxLEFT, 5 );

	m_pokemonShinyColor_1 = new ui::ColorPickerPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonColorSizer->Add( m_pokemonShinyColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_pokemonShinyColor_2 = new ui::ColorPickerPanel( pokemonImageCommonTypePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonColorSizer->Add( m_pokemonShinyColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );


	pokemonImageCommonSizer->Add( pokemonColorSizer, 0, wxLEFT|wxRIGHT, 5 );


	pokemonImageCommonTypePanel->SetSizer( pokemonImageCommonSizer );
	pokemonImageCommonTypePanel->Layout();
	pokemonImageCommonSizer->Fit( pokemonImageCommonTypePanel );
	m_pokemonImageContainer->AddPage( pokemonImageCommonTypePanel, wxEmptyString, true );
	wxPanel* pokemonImageUnownType;
	pokemonImageUnownType = new wxPanel( m_pokemonImageContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonImageUnownSizer;
	pokemonImageUnownSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonUnownWarnLabel;
	pokemonUnownWarnLabel = new wxStaticText( pokemonImageUnownType, wxID_ANY, wxT("'안농' 메뉴에서 편집해 주십시오."), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonUnownWarnLabel->Wrap( -1 );
	pokemonImageUnownSizer->Add( pokemonUnownWarnLabel, 0, wxALL, 48 );


	pokemonImageUnownType->SetSizer( pokemonImageUnownSizer );
	pokemonImageUnownType->Layout();
	pokemonImageUnownSizer->Fit( pokemonImageUnownType );
	m_pokemonImageContainer->AddPage( pokemonImageUnownType, wxEmptyString, false );

	pokemonPokemonTypeSizer->Add( m_pokemonImageContainer, 0, wxEXPAND, 5 );


	pokemonPokemonTypeSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* pokemonImage2Label;
	pokemonImage2Label = new ui::LabeledSeparator( pokemonPokemonType, wxID_ANY, wxT("발자국 && 스몰 스프라이트"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonImage2Label->Wrap( -1 );
	pokemonPokemonTypeSizer->Add( pokemonImage2Label, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* pokemonImage2Sizer;
	pokemonImage2Sizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonFootprintLabel;
	pokemonFootprintLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("발자국"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonFootprintLabel->Wrap( -1 );
	pokemonImage2Sizer->Add( pokemonFootprintLabel, 0, wxALL, 8 );

	m_pokemonFootprintImage = new ui::ImageEditorPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( 32,32 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonImage2Sizer->Add( m_pokemonFootprintImage, 0, wxBOTTOM|wxLEFT, 8 );


	pokemonImage2Sizer->Add( 0, 8, 0, 0, 5 );

	wxStaticText* pokemonSmallPictureLabel;
	pokemonSmallPictureLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("스몰 스프라이트 (색상은 맵에서만 적용됩니다)"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonSmallPictureLabel->Wrap( -1 );
	pokemonImage2Sizer->Add( pokemonSmallPictureLabel, 0, wxALL, 8 );

	wxFlexGridSizer* pokemonSmallPictureGrid;
	pokemonSmallPictureGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	pokemonSmallPictureGrid->SetFlexibleDirection( wxBOTH );
	pokemonSmallPictureGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonSmallPictureLabel2;
	pokemonSmallPictureLabel2 = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("이미지： "), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonSmallPictureLabel2->Wrap( -1 );
	pokemonSmallPictureGrid->Add( pokemonSmallPictureLabel2, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxLEFT, 8 );

	m_pokemonSmallPicture = new ui::ImageEditorPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( 56,32 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonSmallPictureGrid->Add( m_pokemonSmallPicture, 0, wxLEFT, 8 );

	wxStaticText* pokemonSmallPictureColorLabel;
	pokemonSmallPictureColorLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("색상： "), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonSmallPictureColorLabel->Wrap( -1 );
	pokemonSmallPictureGrid->Add( pokemonSmallPictureColorLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 8 );

	m_pokemonSmallPictureColorComboBox = new wxComboBox( pokemonPokemonType, wxID_ANY, wxT("파란색"), wxDefaultPosition, wxSize( 120,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonSmallPictureColorComboBox->Append( wxT("빨간색") );
	m_pokemonSmallPictureColorComboBox->Append( wxT("파란색") );
	m_pokemonSmallPictureColorComboBox->Append( wxT("초록색") );
	m_pokemonSmallPictureColorComboBox->Append( wxT("갈색") );
	m_pokemonSmallPictureColorComboBox->Append( wxT("자홍색") );
	m_pokemonSmallPictureColorComboBox->Append( wxT("회색") );
	m_pokemonSmallPictureColorComboBox->SetSelection( 1 );
	pokemonSmallPictureGrid->Add( m_pokemonSmallPictureColorComboBox, 0, wxALL, 8 );


	pokemonImage2Sizer->Add( pokemonSmallPictureGrid, 0, 0, 5 );


	pokemonImage2Sizer->Add( 0, 8, 0, 0, 0 );


	pokemonPokemonTypeSizer->Add( pokemonImage2Sizer, 1, wxEXPAND, 5 );

	ui::LabeledSeparator* pokemonDexLabel;
	pokemonDexLabel = new ui::LabeledSeparator( pokemonPokemonType, wxID_ANY, wxT("도감"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexLabel->Wrap( -1 );
	pokemonPokemonTypeSizer->Add( pokemonDexLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* pokemonDexSizer;
	pokemonDexSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* pokemonDexInfoGrid;
	pokemonDexInfoGrid = new wxFlexGridSizer( 3, 2, 0, 0 );
	pokemonDexInfoGrid->AddGrowableCol( 1 );
	pokemonDexInfoGrid->SetFlexibleDirection( wxBOTH );
	pokemonDexInfoGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonDexSpeciesNameLabel;
	pokemonDexSpeciesNameLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("분류명："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexSpeciesNameLabel->Wrap( -1 );
	pokemonDexInfoGrid->Add( pokemonDexSpeciesNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonDexSpeciesNameText = new wxTextCtrl( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_pokemonDexSpeciesNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_pokemonDexSpeciesNameText->SetMaxLength( 7 );
	}
	#else
	m_pokemonDexSpeciesNameText->SetMaxLength( 7 );
	#endif
	pokemonDexInfoGrid->Add( m_pokemonDexSpeciesNameText, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonDexHeightLabel;
	pokemonDexHeightLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("키："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexHeightLabel->Wrap( -1 );
	pokemonDexInfoGrid->Add( pokemonDexHeightLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonDexHeightValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 25.5, 0, 0.1 );
	m_pokemonDexHeightValue->SetDigits( 1 );
	pokemonDexInfoGrid->Add( m_pokemonDexHeightValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonDexWeightLabel;
	pokemonDexWeightLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("몸무게："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexWeightLabel->Wrap( -1 );
	pokemonDexInfoGrid->Add( pokemonDexWeightLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonDexWeightValue = new wxSpinCtrlDouble( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999.9, 0, 0.1 );
	m_pokemonDexWeightValue->SetDigits( 1 );
	pokemonDexInfoGrid->Add( m_pokemonDexWeightValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonDexSizer->Add( pokemonDexInfoGrid, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );

	m_pokemonDexDescriptionLabel = new wxStaticText( pokemonPokemonType, wxID_ANY, wxT("설명 (너비 %d/18)："), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonDexDescriptionLabel->Wrap( -1 );
	pokemonDexSizer->Add( m_pokemonDexDescriptionLabel, 0, wxALL, 5 );

	m_pokemonDexDescriptionText = new wxTextCtrl( pokemonPokemonType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,72 ), wxTE_MULTILINE|wxTE_NO_VSCROLL|wxBORDER_SIMPLE );
	m_pokemonDexDescriptionText->SetFont( wxFont( 14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_pokemonDexDescriptionText->SetMinSize( wxSize( 320,72 ) );
	m_pokemonDexDescriptionText->SetMaxSize( wxSize( 320,72 ) );

	pokemonDexSizer->Add( m_pokemonDexDescriptionText, 0, wxALL, 5 );


	pokemonPokemonTypeSizer->Add( pokemonDexSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonPokemonTypeSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* pokemonEvoLearnsLabel;
	pokemonEvoLearnsLabel = new ui::LabeledSeparator( pokemonPokemonType, wxID_ANY, wxT("진화 && 자력기"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvoLearnsLabel->Wrap( -1 );
	pokemonPokemonTypeSizer->Add( pokemonEvoLearnsLabel, 0, wxALL|wxEXPAND, 5 );


	pokemonPokemonTypeSizer->Add( 0, 8, 0, 0, 0 );

	wxPanel* pokemonEvolutionsPanel;
	pokemonEvolutionsPanel = new wxPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonEvolutionsSizer;
	pokemonEvolutionsSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonEvolutionsLabel;
	pokemonEvolutionsLabel = new wxStaticText( pokemonEvolutionsPanel, wxID_ANY, wxT("진화"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvolutionsLabel->Wrap( -1 );
	pokemonEvolutionsSizer->Add( pokemonEvolutionsLabel, 0, wxLEFT|wxTOP, 8 );

	m_pokemonEvolutionsList = new ui::ColoredListCtrl( pokemonEvolutionsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	m_pokemonEvolutionsList->SetMinSize( wxSize( 512,125 ) );

	pokemonEvolutionsSizer->Add( m_pokemonEvolutionsList, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 8 );

	wxBoxSizer* pokemonEvolutionsButtonsSizer;
	pokemonEvolutionsButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonEvolutionAdd = new wxButton( pokemonEvolutionsPanel, wxID_ADD, wxT("추가..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEvolutionAdd->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionAdd, 0, wxALL, 2 );

	m_pokemonEvolutionModify = new wxButton( pokemonEvolutionsPanel, wxID_EDIT, wxT("수정..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEvolutionModify->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionModify, 0, wxALL, 2 );

	m_pokemonEvolutionRemove = new wxButton( pokemonEvolutionsPanel, wxID_REMOVE, wxT("삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEvolutionRemove->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionRemove, 0, wxALL, 2 );

	m_pokemonEvolutionClear = new wxButton( pokemonEvolutionsPanel, wxID_CLEAR, wxT("전체 삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEvolutionClear->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_pokemonEvolutionClear->SetForegroundColour( wxColour( 255, 0, 0 ) );

	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionClear, 0, wxALL, 2 );


	pokemonEvolutionsSizer->Add( pokemonEvolutionsButtonsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonEvolutionsPanel->SetSizer( pokemonEvolutionsSizer );
	pokemonEvolutionsPanel->Layout();
	pokemonEvolutionsSizer->Fit( pokemonEvolutionsPanel );
	pokemonPokemonTypeSizer->Add( pokemonEvolutionsPanel, 0, wxEXPAND, 0 );

	wxPanel* pokemonMovesPanel;
	pokemonMovesPanel = new wxPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonMovesSizer;
	pokemonMovesSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonMovesLabel;
	pokemonMovesLabel = new wxStaticText( pokemonMovesPanel, wxID_ANY, wxT("자력기"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonMovesLabel->Wrap( -1 );
	pokemonMovesSizer->Add( pokemonMovesLabel, 0, wxLEFT|wxTOP, 8 );

	m_pokemonMovesList = new ui::ColoredListCtrl( pokemonMovesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	m_pokemonMovesList->SetMinSize( wxSize( 512,180 ) );

	pokemonMovesSizer->Add( m_pokemonMovesList, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 8 );

	wxBoxSizer* pokemonMovesButtonsSizer;
	pokemonMovesButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonMovesImport = new wxButton( pokemonMovesPanel, wxID_IMPORT, wxT("가져오기..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonMovesImport->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonMovesButtonsSizer->Add( m_pokemonMovesImport, 0, wxALL, 2 );

	wxStaticLine* pokemonMovesButtonsSeparator;
	pokemonMovesButtonsSeparator = new wxStaticLine( pokemonMovesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	pokemonMovesButtonsSizer->Add( pokemonMovesButtonsSeparator, 0, wxALL|wxEXPAND, 5 );

	m_pokemonMovesAdd = new wxButton( pokemonMovesPanel, wxID_ADD, wxT("추가..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonMovesAdd->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonMovesButtonsSizer->Add( m_pokemonMovesAdd, 0, wxALL, 2 );

	m_pokemonMovesModify = new wxButton( pokemonMovesPanel, wxID_EDIT, wxT("수정..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonMovesModify->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonMovesButtonsSizer->Add( m_pokemonMovesModify, 0, wxALL, 2 );

	m_pokemonMovesRemove = new wxButton( pokemonMovesPanel, wxID_REMOVE, wxT("삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonMovesRemove->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonMovesButtonsSizer->Add( m_pokemonMovesRemove, 0, wxALL, 2 );

	m_pokemonMovesClear = new wxButton( pokemonMovesPanel, wxID_CLEAR, wxT("전체 삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonMovesClear->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_pokemonMovesClear->SetForegroundColour( wxColour( 255, 0, 0 ) );

	pokemonMovesButtonsSizer->Add( m_pokemonMovesClear, 0, wxALL, 2 );


	pokemonMovesSizer->Add( pokemonMovesButtonsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonMovesPanel->SetSizer( pokemonMovesSizer );
	pokemonMovesPanel->Layout();
	pokemonMovesSizer->Fit( pokemonMovesPanel );
	pokemonPokemonTypeSizer->Add( pokemonMovesPanel, 0, wxEXPAND, 0 );

	wxPanel* pokemonEggMovesPanel;
	pokemonEggMovesPanel = new wxPanel( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonEggMovesSizer;
	pokemonEggMovesSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonEggMovesLabel;
	pokemonEggMovesLabel = new wxStaticText( pokemonEggMovesPanel, wxID_ANY, wxT("알 기술"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggMovesLabel->Wrap( -1 );
	pokemonEggMovesSizer->Add( pokemonEggMovesLabel, 0, wxLEFT|wxTOP, 8 );

	m_pokemonEggMovesList = new ui::ColoredListCtrl( pokemonEggMovesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	m_pokemonEggMovesList->SetMinSize( wxSize( 512,180 ) );

	pokemonEggMovesSizer->Add( m_pokemonEggMovesList, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 8 );

	wxBoxSizer* pokemonEggMovesButtonsSizer;
	pokemonEggMovesButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonEggMovesAdd = new wxButton( pokemonEggMovesPanel, wxID_ADD, wxT("추가..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEggMovesAdd->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonEggMovesButtonsSizer->Add( m_pokemonEggMovesAdd, 0, wxALL, 2 );

	m_pokemonEggMovesModify = new wxButton( pokemonEggMovesPanel, wxID_EDIT, wxT("수정..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEggMovesModify->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonEggMovesButtonsSizer->Add( m_pokemonEggMovesModify, 0, wxALL, 2 );

	m_pokemonEggMovesRemove = new wxButton( pokemonEggMovesPanel, wxID_REMOVE, wxT("삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEggMovesRemove->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonEggMovesButtonsSizer->Add( m_pokemonEggMovesRemove, 0, wxALL, 2 );

	m_pokemonEggMovesClear = new wxButton( pokemonEggMovesPanel, wxID_CLEAR, wxT("전체 삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEggMovesClear->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_pokemonEggMovesClear->SetForegroundColour( wxColour( 255, 0, 0 ) );

	pokemonEggMovesButtonsSizer->Add( m_pokemonEggMovesClear, 0, wxALL, 2 );


	pokemonEggMovesSizer->Add( pokemonEggMovesButtonsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonEggMovesPanel->SetSizer( pokemonEggMovesSizer );
	pokemonEggMovesPanel->Layout();
	pokemonEggMovesSizer->Fit( pokemonEggMovesPanel );
	pokemonPokemonTypeSizer->Add( pokemonEggMovesPanel, 0, wxEXPAND, 0 );


	pokemonPokemonTypeSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* pokemonTMHMsLabel;
	pokemonTMHMsLabel = new ui::LabeledSeparator( pokemonPokemonType, wxID_ANY, wxT("기술머신 && 비전머신"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTMHMsLabel->Wrap( -1 );
	pokemonPokemonTypeSizer->Add( pokemonTMHMsLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* pokemonTMHMsButtonsSizer;
	pokemonTMHMsButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* pokemonTMHMsCheckAllButton;
	pokemonTMHMsCheckAllButton = new wxButton( pokemonPokemonType, wxID_POKEMON_TMHMS_CHECK_ALL, wxT("모두 선택"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTMHMsCheckAllButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonTMHMsButtonsSizer->Add( pokemonTMHMsCheckAllButton, 0, wxALL, 2 );

	wxButton* pokemonTMHMsClearButton;
	pokemonTMHMsClearButton = new wxButton( pokemonPokemonType, wxID_POKEMON_TMHMS_CLEAR, wxT("모두 해제"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTMHMsClearButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	pokemonTMHMsButtonsSizer->Add( pokemonTMHMsClearButton, 0, wxALL, 2 );


	pokemonPokemonTypeSizer->Add( pokemonTMHMsButtonsSizer, 0, wxALL, 4 );

	m_pokemonTMHMsSizer = new wxGridSizer( 3, 3, 0, 0 );

	wxString m_pokemonHmTmList1Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList1NChoices = sizeof( m_pokemonHmTmList1Choices ) / sizeof( wxString );
	m_pokemonHmTmList1 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList1NChoices, m_pokemonHmTmList1Choices, wxLB_NO_SB );
	m_pokemonHmTmList1->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList1, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList2Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList2NChoices = sizeof( m_pokemonHmTmList2Choices ) / sizeof( wxString );
	m_pokemonHmTmList2 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList2NChoices, m_pokemonHmTmList2Choices, wxLB_NO_SB );
	m_pokemonHmTmList2->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList2, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList3Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList3NChoices = sizeof( m_pokemonHmTmList3Choices ) / sizeof( wxString );
	m_pokemonHmTmList3 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList3NChoices, m_pokemonHmTmList3Choices, wxLB_NO_SB );
	m_pokemonHmTmList3->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList3, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList4Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList4NChoices = sizeof( m_pokemonHmTmList4Choices ) / sizeof( wxString );
	m_pokemonHmTmList4 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList4NChoices, m_pokemonHmTmList4Choices, wxLB_NO_SB );
	m_pokemonHmTmList4->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList4, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList5Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList5NChoices = sizeof( m_pokemonHmTmList5Choices ) / sizeof( wxString );
	m_pokemonHmTmList5 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList5NChoices, m_pokemonHmTmList5Choices, wxLB_NO_SB );
	m_pokemonHmTmList5->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList5, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList6Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList6NChoices = sizeof( m_pokemonHmTmList6Choices ) / sizeof( wxString );
	m_pokemonHmTmList6 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList6NChoices, m_pokemonHmTmList6Choices, wxLB_NO_SB );
	m_pokemonHmTmList6->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList6, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList7Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList7NChoices = sizeof( m_pokemonHmTmList7Choices ) / sizeof( wxString );
	m_pokemonHmTmList7 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList7NChoices, m_pokemonHmTmList7Choices, wxLB_NO_SB );
	m_pokemonHmTmList7->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList7, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList8Choices[] = { wxEmptyString };
	int m_pokemonHmTmList8NChoices = sizeof( m_pokemonHmTmList8Choices ) / sizeof( wxString );
	m_pokemonHmTmList8 = new ui::ColoredCheckListBox( pokemonPokemonType, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_pokemonHmTmList8NChoices, m_pokemonHmTmList8Choices, wxLB_NO_SB );
	m_pokemonHmTmList8->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList8, 0, wxALL|wxEXPAND, 2 );


	pokemonPokemonTypeSizer->Add( m_pokemonTMHMsSizer, 0, wxALL|wxEXPAND, 4 );


	pokemonPokemonType->SetSizer( pokemonPokemonTypeSizer );
	pokemonPokemonType->Layout();
	pokemonPokemonTypeSizer->Fit( pokemonPokemonType );
	m_pokemonContainer->AddPage( pokemonPokemonType, wxEmptyString, true );
	wxPanel* pokemonDummyType;
	pokemonDummyType = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pokemonDummyType->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* pokemonDummyTypeSizer;
	pokemonDummyTypeSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonDummyTypeLabel;
	pokemonDummyTypeLabel = new wxStaticText( pokemonDummyType, wxID_ANY, wxT("더미 데이터는 수정할 수 없습니다."), wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_CENTER_HORIZONTAL );
	pokemonDummyTypeLabel->Wrap( -1 );
	pokemonDummyTypeSizer->Add( pokemonDummyTypeLabel, 0, wxALL|wxEXPAND, 32 );


	pokemonDummyType->SetSizer( pokemonDummyTypeSizer );
	pokemonDummyType->Layout();
	pokemonDummyTypeSizer->Fit( pokemonDummyType );
	m_pokemonContainer->AddPage( pokemonDummyType, wxEmptyString, false );
	wxPanel* pokemonEggType;
	pokemonEggType = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pokemonEggType->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* pokemonEggTypeSizer;
	pokemonEggTypeSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* pokemonEggStatsLabel;
	pokemonEggStatsLabel = new ui::LabeledSeparator( pokemonEggType, wxID_ANY, wxT("기본 정보"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggStatsLabel->Wrap( -1 );
	pokemonEggTypeSizer->Add( pokemonEggStatsLabel, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* pokemonEggInfoGrid;
	pokemonEggInfoGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	pokemonEggInfoGrid->AddGrowableCol( 0 );
	pokemonEggInfoGrid->SetFlexibleDirection( wxBOTH );
	pokemonEggInfoGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonEggNameLabel;
	pokemonEggNameLabel = new wxStaticText( pokemonEggType, wxID_ANY, wxT("이름："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggNameLabel->Wrap( -1 );
	pokemonEggInfoGrid->Add( pokemonEggNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonEggNameText = new wxTextCtrl( pokemonEggType, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_pokemonEggNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_pokemonEggNameText->SetMaxLength( 5 );
	}
	#else
	m_pokemonEggNameText->SetMaxLength( 5 );
	#endif
	m_pokemonEggNameText->SetMinSize( wxSize( 240,-1 ) );
	m_pokemonEggNameText->SetMaxSize( wxSize( 240,-1 ) );

	pokemonEggInfoGrid->Add( m_pokemonEggNameText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 4 );


	pokemonEggTypeSizer->Add( pokemonEggInfoGrid, 0, wxALL, 5 );


	pokemonEggTypeSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* pokemonEggImageLabel;
	pokemonEggImageLabel = new ui::LabeledSeparator( pokemonEggType, wxID_ANY, wxT("이미지 && 색상"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggImageLabel->Wrap( -1 );
	pokemonEggTypeSizer->Add( pokemonEggImageLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* pokemonEggImageCommonSizer;
	pokemonEggImageCommonSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* pokemonEggImageSizer;
	pokemonEggImageSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonEggImageDataLabel;
	pokemonEggImageDataLabel = new wxStaticText( pokemonEggType, wxID_ANY, wxT("이미지："), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	pokemonEggImageDataLabel->Wrap( -1 );
	pokemonEggImageSizer->Add( pokemonEggImageDataLabel, 0, wxALL, 5 );

	m_pokemonEggImage = new ui::ImageEditorPanel( pokemonEggType, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonEggImageSizer->Add( m_pokemonEggImage, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );


	pokemonEggImageCommonSizer->Add( pokemonEggImageSizer, 0, wxLEFT|wxRIGHT|wxTOP, 5 );

	wxBoxSizer* pokemonEggColorSizer;
	pokemonEggColorSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonEggColorLabel;
	pokemonEggColorLabel = new wxStaticText( pokemonEggType, wxID_ANY, wxT("색상："), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	pokemonEggColorLabel->Wrap( -1 );
	pokemonEggColorSizer->Add( pokemonEggColorLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonEggColor_1 = new ui::ColorPickerPanel( pokemonEggType, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonEggColorSizer->Add( m_pokemonEggColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_pokemonEggColor_2 = new ui::ColorPickerPanel( pokemonEggType, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonEggColorSizer->Add( m_pokemonEggColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	wxStaticLine* pokemonEggColorSeparator;
	pokemonEggColorSeparator = new wxStaticLine( pokemonEggType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	pokemonEggColorSeparator->Hide();

	pokemonEggColorSizer->Add( pokemonEggColorSeparator, 0, wxEXPAND|wxLEFT, 5 );

	m_pokemonEggShinyColor_1 = new ui::ColorPickerPanel( pokemonEggType, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	m_pokemonEggShinyColor_1->Hide();

	pokemonEggColorSizer->Add( m_pokemonEggShinyColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_pokemonEggShinyColor_2 = new ui::ColorPickerPanel( pokemonEggType, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	m_pokemonEggShinyColor_2->Hide();

	pokemonEggColorSizer->Add( m_pokemonEggShinyColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );


	pokemonEggImageCommonSizer->Add( pokemonEggColorSizer, 0, wxLEFT|wxRIGHT, 5 );


	pokemonEggTypeSizer->Add( pokemonEggImageCommonSizer, 0, wxEXPAND, 5 );


	pokemonEggTypeSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* pokemonEggImage2Label;
	pokemonEggImage2Label = new ui::LabeledSeparator( pokemonEggType, wxID_ANY, wxT("스몰 스프라이트 (색상은 맵에서만 적용됩니다)"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggImage2Label->Wrap( -1 );
	pokemonEggTypeSizer->Add( pokemonEggImage2Label, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* pokemonEggSmallPictureGrid;
	pokemonEggSmallPictureGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	pokemonEggSmallPictureGrid->SetFlexibleDirection( wxBOTH );
	pokemonEggSmallPictureGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonEggSmallPictureLabel2;
	pokemonEggSmallPictureLabel2 = new wxStaticText( pokemonEggType, wxID_ANY, wxT("이미지： "), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggSmallPictureLabel2->Wrap( -1 );
	pokemonEggSmallPictureGrid->Add( pokemonEggSmallPictureLabel2, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxLEFT, 8 );

	m_pokemonEggSmallPicture = new ui::ImageEditorPanel( pokemonEggType, wxID_ANY, wxDefaultPosition, wxSize( 56,32 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	pokemonEggSmallPictureGrid->Add( m_pokemonEggSmallPicture, 0, wxLEFT, 8 );

	wxStaticText* pokemonEggSmallPictureColorLabel;
	pokemonEggSmallPictureColorLabel = new wxStaticText( pokemonEggType, wxID_ANY, wxT("색상： "), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggSmallPictureColorLabel->Wrap( -1 );
	pokemonEggSmallPictureGrid->Add( pokemonEggSmallPictureColorLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 8 );

	m_pokemonEggSmallPictureColorComboBox = new wxComboBox( pokemonEggType, wxID_ANY, wxT("파란색"), wxDefaultPosition, wxSize( 120,-1 ), 0, NULL, wxCB_READONLY );
	m_pokemonEggSmallPictureColorComboBox->Append( wxT("빨간색") );
	m_pokemonEggSmallPictureColorComboBox->Append( wxT("파란색") );
	m_pokemonEggSmallPictureColorComboBox->Append( wxT("초록색") );
	m_pokemonEggSmallPictureColorComboBox->Append( wxT("갈색") );
	m_pokemonEggSmallPictureColorComboBox->Append( wxT("자홍색") );
	m_pokemonEggSmallPictureColorComboBox->Append( wxT("회색") );
	m_pokemonEggSmallPictureColorComboBox->SetSelection( 1 );
	pokemonEggSmallPictureGrid->Add( m_pokemonEggSmallPictureColorComboBox, 0, wxALL, 8 );


	pokemonEggTypeSizer->Add( pokemonEggSmallPictureGrid, 0, 0, 5 );


	pokemonEggType->SetSizer( pokemonEggTypeSizer );
	pokemonEggType->Layout();
	pokemonEggTypeSizer->Fit( pokemonEggType );
	m_pokemonContainer->AddPage( pokemonEggType, wxEmptyString, false );

	pokemonInnerPanelSizer->Add( m_pokemonContainer, 1, wxALL|wxEXPAND, 2 );


	pokemonInnerPanel->SetSizer( pokemonInnerPanelSizer );
	pokemonInnerPanel->Layout();
	pokemonInnerPanelSizer->Fit( pokemonInnerPanel );
	pokemonPanelSizer->Add( pokemonInnerPanel, 1, wxEXPAND | wxALL, 2 );


	pokemonPanel->SetSizer( pokemonPanelSizer );
	pokemonPanel->Layout();
	pokemonPanelSizer->Fit( pokemonPanel );
	mainTabs->AddPage( pokemonPanel, wxT("포켓몬"), true );
	wxPanel* unownPanel;
	unownPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* unownPanelSizer;
	unownPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* unownPokemonPanel;
	unownPokemonPanel = new wxPanel( unownPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* unownPokemonPanelSizer;
	unownPokemonPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* unownPokemonInnerPanel;
	unownPokemonInnerPanel = new wxPanel( unownPokemonPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxTAB_TRAVERSAL );
	unownPokemonInnerPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* unownPokemonInnerPanelSizer;
	unownPokemonInnerPanelSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* unownPokemonLabel;
	unownPokemonLabel = new ui::LabeledSeparator( unownPokemonInnerPanel, wxID_ANY, wxT("포켓몬 설정"), wxDefaultPosition, wxDefaultSize, 0 );
	unownPokemonLabel->Wrap( -1 );
	unownPokemonInnerPanelSizer->Add( unownPokemonLabel, 0, wxALL|wxEXPAND, 5 );


	unownPokemonInnerPanelSizer->Add( 0, 5, 0, 0, 0 );

	m_unownPokemonComboBox = new wxComboBox( unownPokemonInnerPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0, NULL, wxCB_READONLY );
	unownPokemonInnerPanelSizer->Add( m_unownPokemonComboBox, 0, wxBOTTOM|wxLEFT|wxRIGHT, 10 );


	unownPokemonInnerPanel->SetSizer( unownPokemonInnerPanelSizer );
	unownPokemonInnerPanel->Layout();
	unownPokemonInnerPanelSizer->Fit( unownPokemonInnerPanel );
	unownPokemonPanelSizer->Add( unownPokemonInnerPanel, 1, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 2 );


	unownPokemonPanel->SetSizer( unownPokemonPanelSizer );
	unownPokemonPanel->Layout();
	unownPokemonPanelSizer->Fit( unownPokemonPanel );
	unownPanelSizer->Add( unownPokemonPanel, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 2 );

	m_unownInnerPanel = new wxPanel( unownPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* unownInnerPanelSizer;
	unownInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_unownList = new ui::ColoredListBox( m_unownInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 128,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	unownInnerPanelSizer->Add( m_unownList, 0, wxALL|wxEXPAND, 2 );

	m_unownContainer = new wxPanel( m_unownInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxTAB_TRAVERSAL );
	m_unownContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* unownContainerSizer;
	unownContainerSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* unownImageLabel;
	unownImageLabel = new ui::LabeledSeparator( m_unownContainer, wxID_ANY, wxT("이미지"), wxDefaultPosition, wxDefaultSize, 0 );
	unownImageLabel->Wrap( -1 );
	unownContainerSizer->Add( unownImageLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* unownImageSizer;
	unownImageSizer = new wxBoxSizer( wxHORIZONTAL );

	m_unownFrontImage = new ui::ImageEditorPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownImageSizer->Add( m_unownFrontImage, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_unownBackImage = new ui::ImageEditorPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownImageSizer->Add( m_unownBackImage, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	wxStaticLine* unownImageSeparator;
	unownImageSeparator = new wxStaticLine( m_unownContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	unownImageSizer->Add( unownImageSeparator, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxTOP, 5 );

	m_unownShinyFrontImage = new ui::ImageEditorPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownImageSizer->Add( m_unownShinyFrontImage, 1, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_unownShinyBackImage = new ui::ImageEditorPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownImageSizer->Add( m_unownShinyBackImage, 1, wxBOTTOM|wxLEFT|wxTOP, 5 );


	unownContainerSizer->Add( unownImageSizer, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );

	ui::LabeledSeparator* unownColorsLabel;
	unownColorsLabel = new ui::LabeledSeparator( m_unownContainer, wxID_ANY, wxT("색상 (공용)"), wxDefaultPosition, wxDefaultSize, 0 );
	unownColorsLabel->Wrap( -1 );
	unownContainerSizer->Add( unownColorsLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* unownColorsSizer;
	unownColorsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_unownColor_1 = new ui::ColorPickerPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownColorsSizer->Add( m_unownColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_unownColor_2 = new ui::ColorPickerPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownColorsSizer->Add( m_unownColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	wxStaticLine* unownColorSeparator;
	unownColorSeparator = new wxStaticLine( m_unownContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	unownColorsSizer->Add( unownColorSeparator, 0, wxEXPAND|wxLEFT, 5 );

	m_unownShinyColor_1 = new ui::ColorPickerPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownColorsSizer->Add( m_unownShinyColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_unownShinyColor_2 = new ui::ColorPickerPanel( m_unownContainer, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	unownColorsSizer->Add( m_unownShinyColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );


	unownContainerSizer->Add( unownColorsSizer, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );


	m_unownContainer->SetSizer( unownContainerSizer );
	m_unownContainer->Layout();
	unownContainerSizer->Fit( m_unownContainer );
	unownInnerPanelSizer->Add( m_unownContainer, 1, wxEXPAND | wxALL, 2 );


	m_unownInnerPanel->SetSizer( unownInnerPanelSizer );
	m_unownInnerPanel->Layout();
	unownInnerPanelSizer->Fit( m_unownInnerPanel );
	unownPanelSizer->Add( m_unownInnerPanel, 1, wxEXPAND | wxALL, 2 );


	unownPanel->SetSizer( unownPanelSizer );
	unownPanel->Layout();
	unownPanelSizer->Fit( unownPanel );
	mainTabs->AddPage( unownPanel, wxT("안농"), false );
	wxPanel* itemPanel;
	itemPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* itemPanelSizer;
	itemPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* itemInnerPanel;
	itemInnerPanel = new wxPanel( itemPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* itemInnerPanelSizer;
	itemInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_itemList = new ui::ColoredListBox( itemInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 170,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	itemInnerPanelSizer->Add( m_itemList, 0, wxALL|wxEXPAND, 2 );

	m_itemContainer = new wxScrolledWindow( itemInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxHSCROLL|wxVSCROLL );
	m_itemContainer->SetScrollRate( 5, 16 );
	m_itemContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* itemContainerPanel;
	itemContainerPanel = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* itemPrimaryLabel;
	itemPrimaryLabel = new ui::LabeledSeparator( m_itemContainer, wxID_ANY, wxT("기본 정보"), wxDefaultPosition, wxDefaultSize, 0 );
	itemPrimaryLabel->Wrap( -1 );
	itemContainerPanel->Add( itemPrimaryLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* itemPrimarySizer;
	itemPrimarySizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* itemPrimaryGrid;
	itemPrimaryGrid = new wxFlexGridSizer( 3, 2, 0, 0 );
	itemPrimaryGrid->AddGrowableCol( 1 );
	itemPrimaryGrid->SetFlexibleDirection( wxBOTH );
	itemPrimaryGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	itemPrimaryGrid->SetMinSize( wxSize( 220,-1 ) );
	wxStaticText* itemPrimaryGroupLabel;
	itemPrimaryGroupLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("분류："), wxDefaultPosition, wxDefaultSize, 0 );
	itemPrimaryGroupLabel->Wrap( -1 );
	itemPrimaryGrid->Add( itemPrimaryGroupLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemPrimaryGroupComboBox = new wxComboBox( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_itemPrimaryGroupComboBox->Append( wxT("없음") );
	m_itemPrimaryGroupComboBox->Append( wxT("도구") );
	m_itemPrimaryGroupComboBox->Append( wxT("중요한") );
	m_itemPrimaryGroupComboBox->Append( wxT("볼") );
	m_itemPrimaryGroupComboBox->Append( wxT("기술머신") );
	itemPrimaryGrid->Add( m_itemPrimaryGroupComboBox, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* itemPrimaryNameLabel;
	itemPrimaryNameLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("이름："), wxDefaultPosition, wxDefaultSize, 0 );
	itemPrimaryNameLabel->Wrap( -1 );
	itemPrimaryGrid->Add( itemPrimaryNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemPrimaryNameText = new wxTextCtrl( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_itemPrimaryNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_itemPrimaryNameText->SetMaxLength( 12 );
	}
	#else
	m_itemPrimaryNameText->SetMaxLength( 12 );
	#endif
	itemPrimaryGrid->Add( m_itemPrimaryNameText, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* itemPrimaryPriceLabel;
	itemPrimaryPriceLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("가격："), wxDefaultPosition, wxDefaultSize, 0 );
	itemPrimaryPriceLabel->Wrap( -1 );
	itemPrimaryGrid->Add( itemPrimaryPriceLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemPrimaryPriceSpinCtrl = new wxSpinCtrlDouble( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 39321, 0, 1 );
	m_itemPrimaryPriceSpinCtrl->SetDigits( 0 );
	itemPrimaryGrid->Add( m_itemPrimaryPriceSpinCtrl, 0, wxALL|wxEXPAND, 5 );


	itemPrimarySizer->Add( itemPrimaryGrid, 0, 0, 0 );


	itemPrimarySizer->Add( 0, 8, 0, 0, 0 );

	m_itemPrimaryDescriptionLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("설명 (너비 %d/18)："), wxDefaultPosition, wxDefaultSize, 0 );
	m_itemPrimaryDescriptionLabel->Wrap( -1 );
	itemPrimarySizer->Add( m_itemPrimaryDescriptionLabel, 0, wxALL, 5 );

	m_itemPrimaryDescriptionText = new wxTextCtrl( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,48 ), wxTE_MULTILINE|wxTE_NO_VSCROLL|wxBORDER_SIMPLE );
	m_itemPrimaryDescriptionText->SetFont( wxFont( 14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_itemPrimaryDescriptionText->SetMinSize( wxSize( 320,48 ) );
	m_itemPrimaryDescriptionText->SetMaxSize( wxSize( 320,48 ) );

	itemPrimarySizer->Add( m_itemPrimaryDescriptionText, 0, wxALL, 5 );


	itemContainerPanel->Add( itemPrimarySizer, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );

	ui::LabeledSeparator* itemMenuLabel;
	itemMenuLabel = new ui::LabeledSeparator( m_itemContainer, wxID_ANY, wxT("메뉴"), wxDefaultPosition, wxDefaultSize, 0 );
	itemMenuLabel->Wrap( -1 );
	itemContainerPanel->Add( itemMenuLabel, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* itemMenuGrid;
	itemMenuGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	itemMenuGrid->AddGrowableCol( 1 );
	itemMenuGrid->SetFlexibleDirection( wxBOTH );
	itemMenuGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	itemMenuGrid->SetMinSize( wxSize( 220,-1 ) );
	wxStaticText* itemFieldMenuLabel;
	itemFieldMenuLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("필드："), wxDefaultPosition, wxDefaultSize, 0 );
	itemFieldMenuLabel->Wrap( -1 );
	itemMenuGrid->Add( itemFieldMenuLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemFieldMenuComboBox = new wxComboBox( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_itemFieldMenuComboBox->Append( wxT("사용할 수 없음") );
	m_itemFieldMenuComboBox->Append( wxT("?") );
	m_itemFieldMenuComboBox->Append( wxT("?") );
	m_itemFieldMenuComboBox->Append( wxT("?") );
	m_itemFieldMenuComboBox->Append( wxT("사용만 함") );
	m_itemFieldMenuComboBox->Append( wxT("포켓몬에게 사용") );
	m_itemFieldMenuComboBox->Append( wxT("사용할 때 필드로 돌아감") );
	itemMenuGrid->Add( m_itemFieldMenuComboBox, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* itemBattleMenuLabel;
	itemBattleMenuLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("배틀："), wxDefaultPosition, wxDefaultSize, 0 );
	itemBattleMenuLabel->Wrap( -1 );
	itemMenuGrid->Add( itemBattleMenuLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemBattleMenuComboBox = new wxComboBox( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_itemBattleMenuComboBox->Append( wxT("사용할 수 없음") );
	m_itemBattleMenuComboBox->Append( wxT("?") );
	m_itemBattleMenuComboBox->Append( wxT("?") );
	m_itemBattleMenuComboBox->Append( wxT("?") );
	m_itemBattleMenuComboBox->Append( wxT("사용만 함") );
	m_itemBattleMenuComboBox->Append( wxT("포켓몬에게 사용") );
	m_itemBattleMenuComboBox->Append( wxT("사용할 때 필드로 돌아감") );
	itemMenuGrid->Add( m_itemBattleMenuComboBox, 0, wxALL|wxEXPAND, 5 );


	itemContainerPanel->Add( itemMenuGrid, 0, wxALL, 5 );

	ui::LabeledSeparator* itemEtcLabel;
	itemEtcLabel = new ui::LabeledSeparator( m_itemContainer, wxID_ANY, wxT("기타"), wxDefaultPosition, wxDefaultSize, 0 );
	itemEtcLabel->Wrap( -1 );
	itemContainerPanel->Add( itemEtcLabel, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* itemEtcGrid;
	itemEtcGrid = new wxFlexGridSizer( 3, 2, 0, 0 );
	itemEtcGrid->AddGrowableCol( 1 );
	itemEtcGrid->SetFlexibleDirection( wxBOTH );
	itemEtcGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	itemEtcGrid->SetMinSize( wxSize( 320,-1 ) );
	wxStaticText* itemEtcEffectLabel;
	itemEtcEffectLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("지닌 도구 효과："), wxDefaultPosition, wxDefaultSize, 0 );
	itemEtcEffectLabel->Wrap( -1 );
	itemEtcGrid->Add( itemEtcEffectLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemEtcEffectComboBox = new wxComboBox( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_itemEtcEffectComboBox->Append( wxT("00 - 없음") );
	m_itemEtcEffectComboBox->Append( wxT("01 - HP 회복") );
	m_itemEtcEffectComboBox->Append( wxT("02 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("03 - HP 회복 (개수 소모 없음)") );
	m_itemEtcEffectComboBox->Append( wxT("04 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("05 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("06 - PP 회복") );
	m_itemEtcEffectComboBox->Append( wxT("07 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("08 - 야생 포켓몬과 만날 확률 낮아짐") );
	m_itemEtcEffectComboBox->Append( wxT("09 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("0A - 독상태 회복") );
	m_itemEtcEffectComboBox->Append( wxT("0B - 얼음상태 회복") );
	m_itemEtcEffectComboBox->Append( wxT("0C - 화상상태 회복") );
	m_itemEtcEffectComboBox->Append( wxT("0D - 잠듦상태 회복") );
	m_itemEtcEffectComboBox->Append( wxT("0E - 마비상태 회복") );
	m_itemEtcEffectComboBox->Append( wxT("0F - 모든 상태이상 회복") );
	m_itemEtcEffectComboBox->Append( wxT("10 - 혼란상태 회복") );
	m_itemEtcEffectComboBox->Append( wxT("11 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("12 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("13 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("14 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("15 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("16 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("17 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("18 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("19 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("1A - ?") );
	m_itemEtcEffectComboBox->Append( wxT("1B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("1C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("1D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("1E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("1F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("20 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("21 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("22 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("23 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("24 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("25 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("26 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("27 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("28 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("29 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("2A - 메타몽의 방어력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("2B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("2C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("2D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("2E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("2F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("30 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("31 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("32 - 노말 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("33 - 격투 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("34 - 비행 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("35 - 독 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("36 - 땅 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("37 - 바위 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("38 - 벌레 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("39 - 고스트 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("3A - 화염 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("3B - 물 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("3C - 풀 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("3D - 전기 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("3E - 에스퍼 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("3F - 얼음 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("40 - 드래곤 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("41 - 악 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("42 - 강철 타입 기술 위력 상승") );
	m_itemEtcEffectComboBox->Append( wxT("43 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("44 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("45 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("46 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("47 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("48 - 야생 포켓몬 전투에서 반드시 도망") );
	m_itemEtcEffectComboBox->Append( wxT("49 - 급소에 명중하기 쉽게된다") );
	m_itemEtcEffectComboBox->Append( wxT("4A - 포켓몬이 선제 공격한다") );
	m_itemEtcEffectComboBox->Append( wxT("4B - 상대 포켓몬의 기가 죽는다") );
	m_itemEtcEffectComboBox->Append( wxT("4C - 지닌 포켓몬이 배틀 참여 시 돈 2배") );
	m_itemEtcEffectComboBox->Append( wxT("4D - 상대 포켓몬의 명중률을 낮춘다") );
	m_itemEtcEffectComboBox->Append( wxT("4E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("4F - HP를 1 남기고 버틸 때가 있다") );
	m_itemEtcEffectComboBox->Append( wxT("50 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("51 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("52 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("53 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("54 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("55 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("56 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("57 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("58 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("59 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("5A - ?") );
	m_itemEtcEffectComboBox->Append( wxT("5B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("5C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("5D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("5E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("5F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("60 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("61 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("62 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("63 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("64 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("65 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("66 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("67 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("68 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("69 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("6A - ?") );
	m_itemEtcEffectComboBox->Append( wxT("6B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("6C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("6D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("6E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("6F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("70 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("71 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("72 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("73 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("74 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("75 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("76 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("77 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("78 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("79 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("7A - ?") );
	m_itemEtcEffectComboBox->Append( wxT("7B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("7C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("7D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("7E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("7F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("80 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("81 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("82 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("83 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("84 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("85 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("86 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("87 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("88 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("89 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("8A - ?") );
	m_itemEtcEffectComboBox->Append( wxT("8B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("8C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("8D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("8E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("8F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("90 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("91 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("92 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("93 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("94 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("95 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("96 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("97 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("98 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("99 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("9A - ?") );
	m_itemEtcEffectComboBox->Append( wxT("9B - ?") );
	m_itemEtcEffectComboBox->Append( wxT("9C - ?") );
	m_itemEtcEffectComboBox->Append( wxT("9D - ?") );
	m_itemEtcEffectComboBox->Append( wxT("9E - ?") );
	m_itemEtcEffectComboBox->Append( wxT("9F - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A0 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A1 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A2 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A3 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A4 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A5 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A6 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A7 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A8 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("A9 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("AA - ?") );
	m_itemEtcEffectComboBox->Append( wxT("AB - ?") );
	m_itemEtcEffectComboBox->Append( wxT("AC - ?") );
	m_itemEtcEffectComboBox->Append( wxT("AD - ?") );
	m_itemEtcEffectComboBox->Append( wxT("AE - ?") );
	m_itemEtcEffectComboBox->Append( wxT("AF - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B0 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B1 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B2 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B3 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B4 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B5 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B6 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B7 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B8 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("B9 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("BA - ?") );
	m_itemEtcEffectComboBox->Append( wxT("BB - ?") );
	m_itemEtcEffectComboBox->Append( wxT("BC - ?") );
	m_itemEtcEffectComboBox->Append( wxT("BD - ?") );
	m_itemEtcEffectComboBox->Append( wxT("BE - ?") );
	m_itemEtcEffectComboBox->Append( wxT("BF - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C0 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C1 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C2 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C3 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C4 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C5 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C6 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C7 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C8 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("C9 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("CA - ?") );
	m_itemEtcEffectComboBox->Append( wxT("CB - ?") );
	m_itemEtcEffectComboBox->Append( wxT("CC - ?") );
	m_itemEtcEffectComboBox->Append( wxT("CD - ?") );
	m_itemEtcEffectComboBox->Append( wxT("CE - ?") );
	m_itemEtcEffectComboBox->Append( wxT("CF - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D0 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D1 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D2 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D3 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D4 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D5 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D6 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D7 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D8 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("D9 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("DA - ?") );
	m_itemEtcEffectComboBox->Append( wxT("DB - ?") );
	m_itemEtcEffectComboBox->Append( wxT("DC - ?") );
	m_itemEtcEffectComboBox->Append( wxT("DD - ?") );
	m_itemEtcEffectComboBox->Append( wxT("DE - ?") );
	m_itemEtcEffectComboBox->Append( wxT("DF - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E0 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E1 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E2 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E3 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E4 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E5 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E6 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E7 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E8 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("E9 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("EA - ?") );
	m_itemEtcEffectComboBox->Append( wxT("EB - ?") );
	m_itemEtcEffectComboBox->Append( wxT("EC - ?") );
	m_itemEtcEffectComboBox->Append( wxT("ED - ?") );
	m_itemEtcEffectComboBox->Append( wxT("EE - ?") );
	m_itemEtcEffectComboBox->Append( wxT("EF - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F0 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F1 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F2 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F3 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F4 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F5 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F6 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F7 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F8 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("F9 - ?") );
	m_itemEtcEffectComboBox->Append( wxT("FA - ?") );
	m_itemEtcEffectComboBox->Append( wxT("FB - ?") );
	m_itemEtcEffectComboBox->Append( wxT("FC - ?") );
	m_itemEtcEffectComboBox->Append( wxT("FD - ?") );
	m_itemEtcEffectComboBox->Append( wxT("FE - ?") );
	m_itemEtcEffectComboBox->Append( wxT("FF - ?") );
	itemEtcGrid->Add( m_itemEtcEffectComboBox, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* itemEtcRegisterLabel;
	itemEtcRegisterLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("판매·등록 설정："), wxDefaultPosition, wxDefaultSize, 0 );
	itemEtcRegisterLabel->Wrap( -1 );
	itemEtcGrid->Add( itemEtcRegisterLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemEtcRegisterComboBox = new wxComboBox( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_itemEtcRegisterComboBox->Append( wxT("없음") );
	m_itemEtcRegisterComboBox->Append( wxT("등록 불가") );
	m_itemEtcRegisterComboBox->Append( wxT("판매 불가") );
	m_itemEtcRegisterComboBox->Append( wxT("판매·등록 불가") );
	itemEtcGrid->Add( m_itemEtcRegisterComboBox, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* itemEtcValueLabel;
	itemEtcValueLabel = new wxStaticText( m_itemContainer, wxID_ANY, wxT("아이템 값："), wxDefaultPosition, wxDefaultSize, 0 );
	itemEtcValueLabel->Wrap( -1 );
	itemEtcGrid->Add( itemEtcValueLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_itemEtcValueSpinCtrl = new wxSpinCtrlDouble( m_itemContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_itemEtcValueSpinCtrl->SetDigits( 0 );
	itemEtcGrid->Add( m_itemEtcValueSpinCtrl, 0, wxALL|wxEXPAND, 5 );


	itemContainerPanel->Add( itemEtcGrid, 0, wxALL, 5 );


	m_itemContainer->SetSizer( itemContainerPanel );
	m_itemContainer->Layout();
	itemContainerPanel->Fit( m_itemContainer );
	itemInnerPanelSizer->Add( m_itemContainer, 1, wxEXPAND | wxALL, 2 );


	itemInnerPanel->SetSizer( itemInnerPanelSizer );
	itemInnerPanel->Layout();
	itemInnerPanelSizer->Fit( itemInnerPanel );
	itemPanelSizer->Add( itemInnerPanel, 1, wxEXPAND | wxALL, 2 );


	itemPanel->SetSizer( itemPanelSizer );
	itemPanel->Layout();
	itemPanelSizer->Fit( itemPanel );
	mainTabs->AddPage( itemPanel, wxT("아이템"), false );
	wxPanel* movePanel;
	movePanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* movePanelSizer;
	movePanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* moveInnerPanel;
	moveInnerPanel = new wxPanel( movePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* moveInnerPanelSizer;
	moveInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_moveList = new ui::ColoredListBox( moveInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 128,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	moveInnerPanelSizer->Add( m_moveList, 0, wxALL|wxEXPAND, 2 );

	m_moveContainer = new wxScrolledWindow( moveInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxHSCROLL|wxVSCROLL );
	m_moveContainer->SetScrollRate( 5, 16 );
	m_moveContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* moveContainerSizer;
	moveContainerSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* movePrimaryLabel;
	movePrimaryLabel = new ui::LabeledSeparator( m_moveContainer, wxID_ANY, wxT("기본 정보"), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryLabel->Wrap( -1 );
	moveContainerSizer->Add( movePrimaryLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* movePrimarySizer;
	movePrimarySizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* movePrimaryGrid;
	movePrimaryGrid = new wxFlexGridSizer( 6, 3, 0, 0 );
	movePrimaryGrid->AddGrowableCol( 1 );
	movePrimaryGrid->SetFlexibleDirection( wxBOTH );
	movePrimaryGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	movePrimaryGrid->SetMinSize( wxSize( 240,-1 ) );
	wxStaticText* movePrimaryNumberLabel;
	movePrimaryNumberLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("번호："), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryNumberLabel->Wrap( -1 );
	movePrimaryGrid->Add( movePrimaryNumberLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movePrimaryNumberText = new wxTextCtrl( m_moveContainer, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	movePrimaryGrid->Add( m_movePrimaryNumberText, 0, wxALL|wxEXPAND, 5 );


	movePrimaryGrid->Add( 0, 0, 0, 0, 0 );

	wxStaticText* movePrimaryNameLabel;
	movePrimaryNameLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("이름："), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryNameLabel->Wrap( -1 );
	movePrimaryGrid->Add( movePrimaryNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movePrimaryNameText = new wxTextCtrl( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_movePrimaryNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_movePrimaryNameText->SetMaxLength( 7 );
	}
	#else
	m_movePrimaryNameText->SetMaxLength( 7 );
	#endif
	movePrimaryGrid->Add( m_movePrimaryNameText, 0, wxALL|wxEXPAND, 5 );


	movePrimaryGrid->Add( 0, 0, 0, 0, 0 );

	wxStaticText* movePrimaryTypeLabel;
	movePrimaryTypeLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("타입："), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryTypeLabel->Wrap( -1 );
	movePrimaryGrid->Add( movePrimaryTypeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movePrimaryTypeComboBox = new wxComboBox( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	movePrimaryGrid->Add( m_movePrimaryTypeComboBox, 0, wxALL|wxEXPAND, 5 );


	movePrimaryGrid->Add( 0, 0, 0, 0, 0 );

	wxStaticText* movePrimaryPowerLabel;
	movePrimaryPowerLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("위력："), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryPowerLabel->Wrap( -1 );
	movePrimaryGrid->Add( movePrimaryPowerLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movePrimaryPowerSpinCtrl = new wxSpinCtrlDouble( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_movePrimaryPowerSpinCtrl->SetDigits( 0 );
	movePrimaryGrid->Add( m_movePrimaryPowerSpinCtrl, 0, wxALL|wxEXPAND, 5 );


	movePrimaryGrid->Add( 0, 0, 0, 0, 0 );

	wxStaticText* movePrimaryAccuracyLabel;
	movePrimaryAccuracyLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("명중률："), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryAccuracyLabel->Wrap( -1 );
	movePrimaryGrid->Add( movePrimaryAccuracyLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movePrimaryAccuracySpinCtrl = new wxSpinCtrlDouble( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_movePrimaryAccuracySpinCtrl->SetDigits( 0 );
	movePrimaryGrid->Add( m_movePrimaryAccuracySpinCtrl, 0, wxALL|wxEXPAND, 5 );

	m_movePrimaryAccuracyPercentageLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("(0.00%)"), wxDefaultPosition, wxSize( 64,-1 ), 0 );
	m_movePrimaryAccuracyPercentageLabel->Wrap( -1 );
	movePrimaryGrid->Add( m_movePrimaryAccuracyPercentageLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxStaticText* movePrimaryPPLabel;
	movePrimaryPPLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("PP："), wxDefaultPosition, wxDefaultSize, 0 );
	movePrimaryPPLabel->Wrap( -1 );
	movePrimaryGrid->Add( movePrimaryPPLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movePrimaryPPSpinCtrl = new wxSpinCtrlDouble( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_movePrimaryPPSpinCtrl->SetDigits( 0 );
	movePrimaryGrid->Add( m_movePrimaryPPSpinCtrl, 0, wxALL|wxEXPAND, 5 );


	movePrimaryGrid->Add( 0, 0, 0, 0, 0 );


	movePrimarySizer->Add( movePrimaryGrid, 0, wxBOTTOM|wxLEFT|wxRIGHT, 0 );


	movePrimarySizer->Add( 0, 8, 0, 0, 0 );

	m_movePrimaryDescriptionLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("설명 (너비 %d/18)："), wxDefaultPosition, wxDefaultSize, 0 );
	m_movePrimaryDescriptionLabel->Wrap( -1 );
	movePrimarySizer->Add( m_movePrimaryDescriptionLabel, 0, wxALL, 5 );

	m_movePrimaryDescriptionText = new wxTextCtrl( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,48 ), wxTE_MULTILINE|wxTE_NO_VSCROLL|wxBORDER_SIMPLE );
	m_movePrimaryDescriptionText->SetFont( wxFont( 14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_movePrimaryDescriptionText->SetMinSize( wxSize( 320,48 ) );
	m_movePrimaryDescriptionText->SetMaxSize( wxSize( 320,48 ) );

	movePrimarySizer->Add( m_movePrimaryDescriptionText, 0, wxALL, 5 );


	moveContainerSizer->Add( movePrimarySizer, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );

	ui::LabeledSeparator* moveEffectLabel;
	moveEffectLabel = new ui::LabeledSeparator( m_moveContainer, wxID_ANY, wxT("효과"), wxDefaultPosition, wxDefaultSize, 0 );
	moveEffectLabel->Wrap( -1 );
	moveContainerSizer->Add( moveEffectLabel, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* moveEffectGrid;
	moveEffectGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	moveEffectGrid->AddGrowableCol( 1 );
	moveEffectGrid->SetFlexibleDirection( wxBOTH );
	moveEffectGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	moveEffectGrid->SetMinSize( wxSize( 320,-1 ) );
	wxStaticText* m_moveEffectTypeLabel;
	m_moveEffectTypeLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("타입："), wxDefaultPosition, wxDefaultSize, 0 );
	m_moveEffectTypeLabel->Wrap( -1 );
	moveEffectGrid->Add( m_moveEffectTypeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_moveEffectTypeComboBox = new wxComboBox( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_moveEffectTypeComboBox->Append( wxT("00 - 보통 공격") );
	m_moveEffectTypeComboBox->Append( wxT("01 - 잠듦 공격") );
	m_moveEffectTypeComboBox->Append( wxT("02 - 독 공격") );
	m_moveEffectTypeComboBox->Append( wxT("03 - 흡혈 공격") );
	m_moveEffectTypeComboBox->Append( wxT("04 - 화상 공격") );
	m_moveEffectTypeComboBox->Append( wxT("05 - 얼음 공격") );
	m_moveEffectTypeComboBox->Append( wxT("06 - 마비 공격") );
	m_moveEffectTypeComboBox->Append( wxT("07 - 자폭") );
	m_moveEffectTypeComboBox->Append( wxT("08 - 꿈먹기") );
	m_moveEffectTypeComboBox->Append( wxT("09 - 따라하기") );
	m_moveEffectTypeComboBox->Append( wxT("0A - 공격력 상승") );
	m_moveEffectTypeComboBox->Append( wxT("0B - 방어력 상승") );
	m_moveEffectTypeComboBox->Append( wxT("0C - 스피드 상승") );
	m_moveEffectTypeComboBox->Append( wxT("0D - 특수공격 상승") );
	m_moveEffectTypeComboBox->Append( wxT("0E - 특수방어 상승") );
	m_moveEffectTypeComboBox->Append( wxT("0F - 명중률 상승") );
	m_moveEffectTypeComboBox->Append( wxT("10 - 회피율 상승") );
	m_moveEffectTypeComboBox->Append( wxT("11 - 항상 공격 성공") );
	m_moveEffectTypeComboBox->Append( wxT("12 - 공격력 하락") );
	m_moveEffectTypeComboBox->Append( wxT("13 - 방어력 하락") );
	m_moveEffectTypeComboBox->Append( wxT("14 - 스피드 하락") );
	m_moveEffectTypeComboBox->Append( wxT("15 - 특수공격 하락") );
	m_moveEffectTypeComboBox->Append( wxT("16 - 특수방어 하락") );
	m_moveEffectTypeComboBox->Append( wxT("17 - 명중률 하락") );
	m_moveEffectTypeComboBox->Append( wxT("18 - 회피율 하락") );
	m_moveEffectTypeComboBox->Append( wxT("19 - 상태 원상복귀") );
	m_moveEffectTypeComboBox->Append( wxT("1A - 참기") );
	m_moveEffectTypeComboBox->Append( wxT("1B - 날뜀(혼란할 때까지 반복)") );
	m_moveEffectTypeComboBox->Append( wxT("1C - 강제 포켓몬 변경") );
	m_moveEffectTypeComboBox->Append( wxT("1D - 여러번 맞춤") );
	m_moveEffectTypeComboBox->Append( wxT("1E - 텍스쳐") );
	m_moveEffectTypeComboBox->Append( wxT("1F - 기죽일 수 있음") );
	m_moveEffectTypeComboBox->Append( wxT("20 - 회복") );
	m_moveEffectTypeComboBox->Append( wxT("21 - 맹독") );
	m_moveEffectTypeComboBox->Append( wxT("22 - 고양이돈받기") );
	m_moveEffectTypeComboBox->Append( wxT("23 - 빛의장막") );
	m_moveEffectTypeComboBox->Append( wxT("24 - 트라이어택") );
	m_moveEffectTypeComboBox->Append( wxT("25 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("26 - 일격필살") );
	m_moveEffectTypeComboBox->Append( wxT("27 - 칼바람") );
	m_moveEffectTypeComboBox->Append( wxT("28 - 분노의앞니") );
	m_moveEffectTypeComboBox->Append( wxT("29 - 고정 데미지") );
	m_moveEffectTypeComboBox->Append( wxT("2A - 지속 데미지") );
	m_moveEffectTypeComboBox->Append( wxT("2B - ?") );
	m_moveEffectTypeComboBox->Append( wxT("2C - 더블어택") );
	m_moveEffectTypeComboBox->Append( wxT("2D - 점프킥") );
	m_moveEffectTypeComboBox->Append( wxT("2E - 흰안개") );
	m_moveEffectTypeComboBox->Append( wxT("2F - 기충전") );
	m_moveEffectTypeComboBox->Append( wxT("30 - 공격 시 반동을 입음") );
	m_moveEffectTypeComboBox->Append( wxT("31 - 이상한 빛") );
	m_moveEffectTypeComboBox->Append( wxT("32 - 공격력 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("33 - 방어력 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("34 - 스피드 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("35 - 특수공격 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("36 - 특수방어 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("37 - 명중률 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("38 - 회피율 크게 상승") );
	m_moveEffectTypeComboBox->Append( wxT("39 - 변신") );
	m_moveEffectTypeComboBox->Append( wxT("3A - 공격력 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("3B - 방어력 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("3C - 스피드 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("3D - 특수공격 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("3E - 특수방어 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("3F - 명중률 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("40 - 회피율 크게 하락") );
	m_moveEffectTypeComboBox->Append( wxT("41 - 리플렉터") );
	m_moveEffectTypeComboBox->Append( wxT("42 - 독") );
	m_moveEffectTypeComboBox->Append( wxT("43 - 마비") );
	m_moveEffectTypeComboBox->Append( wxT("44 - 공격 시 공격력 하락") );
	m_moveEffectTypeComboBox->Append( wxT("45 - 공격 시 방어력 하락") );
	m_moveEffectTypeComboBox->Append( wxT("46 - 공격 시 스피드 하락") );
	m_moveEffectTypeComboBox->Append( wxT("47 - 공격 시 특수공격 하락") );
	m_moveEffectTypeComboBox->Append( wxT("48 - 공격 시 특수방어 하락") );
	m_moveEffectTypeComboBox->Append( wxT("49 - 공격 시 명중률 하락") );
	m_moveEffectTypeComboBox->Append( wxT("4A - 공격 시 회피율 하락") );
	m_moveEffectTypeComboBox->Append( wxT("4B - 불새") );
	m_moveEffectTypeComboBox->Append( wxT("4C - 공격 시 혼란에 빠뜨림") );
	m_moveEffectTypeComboBox->Append( wxT("4D - 여러번 맞추면서 독에 빠뜨림") );
	m_moveEffectTypeComboBox->Append( wxT("4E - ?") );
	m_moveEffectTypeComboBox->Append( wxT("4F - 대타출동") );
	m_moveEffectTypeComboBox->Append( wxT("50 - 파괴광선") );
	m_moveEffectTypeComboBox->Append( wxT("51 - 분노") );
	m_moveEffectTypeComboBox->Append( wxT("52 - 흉내내기") );
	m_moveEffectTypeComboBox->Append( wxT("53 - 손가락흔들기") );
	m_moveEffectTypeComboBox->Append( wxT("54 - 씨뿌리기") );
	m_moveEffectTypeComboBox->Append( wxT("55 - 튀어오르기") );
	m_moveEffectTypeComboBox->Append( wxT("56 - 사슬묶기") );
	m_moveEffectTypeComboBox->Append( wxT("57 - 레벨비례 데미지") );
	m_moveEffectTypeComboBox->Append( wxT("58 - 사이코웨이브") );
	m_moveEffectTypeComboBox->Append( wxT("59 - 카운터") );
	m_moveEffectTypeComboBox->Append( wxT("5A - 앵콜") );
	m_moveEffectTypeComboBox->Append( wxT("5B - 아픔나누기") );
	m_moveEffectTypeComboBox->Append( wxT("5C - 코골이") );
	m_moveEffectTypeComboBox->Append( wxT("5D - 텍스쳐2") );
	m_moveEffectTypeComboBox->Append( wxT("5E - 록온") );
	m_moveEffectTypeComboBox->Append( wxT("5F - 스케치") );
	m_moveEffectTypeComboBox->Append( wxT("60 - 상대 얼음을 녹임") );
	m_moveEffectTypeComboBox->Append( wxT("61 - 잠꼬대") );
	m_moveEffectTypeComboBox->Append( wxT("62 - 길동무") );
	m_moveEffectTypeComboBox->Append( wxT("63 - 기사회생") );
	m_moveEffectTypeComboBox->Append( wxT("64 - 원한") );
	m_moveEffectTypeComboBox->Append( wxT("65 - 칼등치기") );
	m_moveEffectTypeComboBox->Append( wxT("66 - 치료방울") );
	m_moveEffectTypeComboBox->Append( wxT("67 - 반드시 먼저 공격") );
	m_moveEffectTypeComboBox->Append( wxT("68 - 트리플킥") );
	m_moveEffectTypeComboBox->Append( wxT("69 - 도둑질") );
	m_moveEffectTypeComboBox->Append( wxT("6A - 검은눈빛") );
	m_moveEffectTypeComboBox->Append( wxT("6B - 악몽") );
	m_moveEffectTypeComboBox->Append( wxT("6C - 화염자동차") );
	m_moveEffectTypeComboBox->Append( wxT("6D - 저주") );
	m_moveEffectTypeComboBox->Append( wxT("6E - ?") );
	m_moveEffectTypeComboBox->Append( wxT("6F - 방어") );
	m_moveEffectTypeComboBox->Append( wxT("70 - 압정뿌리기") );
	m_moveEffectTypeComboBox->Append( wxT("71 - 꿰뚫어보기") );
	m_moveEffectTypeComboBox->Append( wxT("72 - 멸망의 노래") );
	m_moveEffectTypeComboBox->Append( wxT("73 - 모래바람") );
	m_moveEffectTypeComboBox->Append( wxT("74 - 버티기") );
	m_moveEffectTypeComboBox->Append( wxT("75 - 구르기") );
	m_moveEffectTypeComboBox->Append( wxT("76 - 뽐내기") );
	m_moveEffectTypeComboBox->Append( wxT("77 - 연속자르기") );
	m_moveEffectTypeComboBox->Append( wxT("78 - 헤롱헤롱") );
	m_moveEffectTypeComboBox->Append( wxT("79 - 은혜갚기") );
	m_moveEffectTypeComboBox->Append( wxT("7A - 프레젠트") );
	m_moveEffectTypeComboBox->Append( wxT("7B - 화풀이") );
	m_moveEffectTypeComboBox->Append( wxT("7C - 신비의부적") );
	m_moveEffectTypeComboBox->Append( wxT("7D - 성스러운불꽃") );
	m_moveEffectTypeComboBox->Append( wxT("7E - 매그니튜드") );
	m_moveEffectTypeComboBox->Append( wxT("7F - 바턴터치") );
	m_moveEffectTypeComboBox->Append( wxT("80 - 따라가때리기") );
	m_moveEffectTypeComboBox->Append( wxT("81 - 고속스핀") );
	m_moveEffectTypeComboBox->Append( wxT("82 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("83 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("84 - 아침햇살") );
	m_moveEffectTypeComboBox->Append( wxT("85 - 광합성") );
	m_moveEffectTypeComboBox->Append( wxT("86 - 달의불빛") );
	m_moveEffectTypeComboBox->Append( wxT("87 - 잠재파워") );
	m_moveEffectTypeComboBox->Append( wxT("88 - 비바라기") );
	m_moveEffectTypeComboBox->Append( wxT("89 - 쾌청") );
	m_moveEffectTypeComboBox->Append( wxT("8A - 공격 후 방어력 상승") );
	m_moveEffectTypeComboBox->Append( wxT("8B - 공격 후 공격력 상승") );
	m_moveEffectTypeComboBox->Append( wxT("8C - 공격 후 스탯 상승") );
	m_moveEffectTypeComboBox->Append( wxT("8D - 속이다") );
	m_moveEffectTypeComboBox->Append( wxT("8E - 배북") );
	m_moveEffectTypeComboBox->Append( wxT("8F - 자기암시") );
	m_moveEffectTypeComboBox->Append( wxT("90 - 미러코트") );
	m_moveEffectTypeComboBox->Append( wxT("91 - 로케트박치기") );
	m_moveEffectTypeComboBox->Append( wxT("92 - 회오리") );
	m_moveEffectTypeComboBox->Append( wxT("93 - 지진") );
	m_moveEffectTypeComboBox->Append( wxT("94 - 미래예지") );
	m_moveEffectTypeComboBox->Append( wxT("95 - 바람일으키기") );
	m_moveEffectTypeComboBox->Append( wxT("96 - 짓밟기") );
	m_moveEffectTypeComboBox->Append( wxT("97 - 솔라빔") );
	m_moveEffectTypeComboBox->Append( wxT("98 - 번개") );
	m_moveEffectTypeComboBox->Append( wxT("99 - 순간이동") );
	m_moveEffectTypeComboBox->Append( wxT("9A - 집단구타") );
	m_moveEffectTypeComboBox->Append( wxT("9B - 공중날기") );
	m_moveEffectTypeComboBox->Append( wxT("9C - 웅크리기") );
	m_moveEffectTypeComboBox->Append( wxT("9D - ?") );
	m_moveEffectTypeComboBox->Append( wxT("9E - ?") );
	m_moveEffectTypeComboBox->Append( wxT("9F - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A0 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A1 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A2 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A3 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A4 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A5 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A6 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A7 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A8 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("A9 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("AA - ?") );
	m_moveEffectTypeComboBox->Append( wxT("AB - ?") );
	m_moveEffectTypeComboBox->Append( wxT("AC - ?") );
	m_moveEffectTypeComboBox->Append( wxT("AD - ?") );
	m_moveEffectTypeComboBox->Append( wxT("AE - ?") );
	m_moveEffectTypeComboBox->Append( wxT("AF - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B0 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B1 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B2 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B3 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B4 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B5 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B6 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B7 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B8 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("B9 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("BA - ?") );
	m_moveEffectTypeComboBox->Append( wxT("BB - ?") );
	m_moveEffectTypeComboBox->Append( wxT("BC - ?") );
	m_moveEffectTypeComboBox->Append( wxT("BD - ?") );
	m_moveEffectTypeComboBox->Append( wxT("BE - ?") );
	m_moveEffectTypeComboBox->Append( wxT("BF - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C0 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C1 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C2 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C3 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C4 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C5 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C6 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C7 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C8 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("C9 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("CA - ?") );
	m_moveEffectTypeComboBox->Append( wxT("CB - ?") );
	m_moveEffectTypeComboBox->Append( wxT("CC - ?") );
	m_moveEffectTypeComboBox->Append( wxT("CD - ?") );
	m_moveEffectTypeComboBox->Append( wxT("CE - ?") );
	m_moveEffectTypeComboBox->Append( wxT("CF - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D0 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D1 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D2 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D3 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D4 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D5 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D6 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D7 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D8 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("D9 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("DA - ?") );
	m_moveEffectTypeComboBox->Append( wxT("DB - ?") );
	m_moveEffectTypeComboBox->Append( wxT("DC - ?") );
	m_moveEffectTypeComboBox->Append( wxT("DD - ?") );
	m_moveEffectTypeComboBox->Append( wxT("DE - ?") );
	m_moveEffectTypeComboBox->Append( wxT("DF - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E0 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E1 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E2 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E3 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E4 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E5 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E6 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E7 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E8 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("E9 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("EA - ?") );
	m_moveEffectTypeComboBox->Append( wxT("EB - ?") );
	m_moveEffectTypeComboBox->Append( wxT("EC - ?") );
	m_moveEffectTypeComboBox->Append( wxT("ED - ?") );
	m_moveEffectTypeComboBox->Append( wxT("EE - ?") );
	m_moveEffectTypeComboBox->Append( wxT("EF - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F0 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F1 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F2 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F3 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F4 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F5 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F6 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F7 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F8 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("F9 - ?") );
	m_moveEffectTypeComboBox->Append( wxT("FA - ?") );
	m_moveEffectTypeComboBox->Append( wxT("FB - ?") );
	m_moveEffectTypeComboBox->Append( wxT("FC - ?") );
	m_moveEffectTypeComboBox->Append( wxT("FD - ?") );
	m_moveEffectTypeComboBox->Append( wxT("FE - ?") );
	m_moveEffectTypeComboBox->Append( wxT("FF - ?") );
	moveEffectGrid->Add( m_moveEffectTypeComboBox, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* moveEffectValueLabel;
	moveEffectValueLabel = new wxStaticText( m_moveContainer, wxID_ANY, wxT("값："), wxDefaultPosition, wxDefaultSize, 0 );
	moveEffectValueLabel->Wrap( -1 );
	moveEffectGrid->Add( moveEffectValueLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_moveEffectValueSpinCtrl = new wxSpinCtrlDouble( m_moveContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_moveEffectValueSpinCtrl->SetDigits( 0 );
	moveEffectGrid->Add( m_moveEffectValueSpinCtrl, 0, wxALL|wxEXPAND, 5 );


	moveContainerSizer->Add( moveEffectGrid, 0, wxALL, 5 );


	m_moveContainer->SetSizer( moveContainerSizer );
	m_moveContainer->Layout();
	moveContainerSizer->Fit( m_moveContainer );
	moveInnerPanelSizer->Add( m_moveContainer, 1, wxEXPAND | wxALL, 2 );


	moveInnerPanel->SetSizer( moveInnerPanelSizer );
	moveInnerPanel->Layout();
	moveInnerPanelSizer->Fit( moveInnerPanel );
	movePanelSizer->Add( moveInnerPanel, 1, wxEXPAND | wxALL, 2 );


	movePanel->SetSizer( movePanelSizer );
	movePanel->Layout();
	movePanelSizer->Fit( movePanel );
	mainTabs->AddPage( movePanel, wxT("기술"), false );
	wxPanel* tmhmPanel;
	tmhmPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* tmhmPanelSizer;
	tmhmPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* tmhmInnerPanel;
	tmhmInnerPanel = new wxPanel( tmhmPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* tmhmInnerPanelSizer;
	tmhmInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_tmhmList = new ui::ColoredListBox( tmhmInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 170,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	tmhmInnerPanelSizer->Add( m_tmhmList, 0, wxALL|wxEXPAND, 2 );

	m_tmhmContainer = new wxScrolledWindow( tmhmInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxHSCROLL|wxVSCROLL );
	m_tmhmContainer->SetScrollRate( 5, 16 );
	m_tmhmContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* tmhmContainerSizer;
	tmhmContainerSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* tmhmMoveLabel;
	tmhmMoveLabel = new ui::LabeledSeparator( m_tmhmContainer, wxID_ANY, wxT("기술"), wxDefaultPosition, wxDefaultSize, 0 );
	tmhmMoveLabel->Wrap( -1 );
	tmhmContainerSizer->Add( tmhmMoveLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* tmhmMoveSizer;
	tmhmMoveSizer = new wxBoxSizer( wxVERTICAL );

	m_tmhmMoveComboBox = new wxComboBox( m_tmhmContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0, NULL, wxCB_READONLY );
	tmhmMoveSizer->Add( m_tmhmMoveComboBox, 0, wxLEFT|wxRIGHT|wxTOP, 5 );


	tmhmMoveSizer->Add( 0, 14, 0, wxEXPAND, 0 );


	tmhmContainerSizer->Add( tmhmMoveSizer, 0, wxLEFT|wxRIGHT, 5 );

	ui::LabeledSeparator* tmhmPokemonLabel;
	tmhmPokemonLabel = new ui::LabeledSeparator( m_tmhmContainer, wxID_ANY, wxT("배울 수 있는 포켓몬"), wxDefaultPosition, wxDefaultSize, 0 );
	tmhmPokemonLabel->Wrap( -1 );
	tmhmContainerSizer->Add( tmhmPokemonLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* tmhmPokemonButtonsSizer;
	tmhmPokemonButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* tmhmPokemonCheckAllButton;
	tmhmPokemonCheckAllButton = new wxButton( m_tmhmContainer, wxID_CHECK_ALL, wxT("모두 선택"), wxDefaultPosition, wxDefaultSize, 0 );
	tmhmPokemonCheckAllButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	tmhmPokemonButtonsSizer->Add( tmhmPokemonCheckAllButton, 0, wxALL, 5 );

	tmhmPokemonClearButton = new wxButton( m_tmhmContainer, wxID_CLEAR, wxT("모두 해제"), wxDefaultPosition, wxDefaultSize, 0 );
	tmhmPokemonClearButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	tmhmPokemonButtonsSizer->Add( tmhmPokemonClearButton, 0, wxALL, 5 );


	tmhmContainerSizer->Add( tmhmPokemonButtonsSizer, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );

	wxArrayString m_tmhmPokemonListChoices;
	m_tmhmPokemonList = new ui::ColoredCheckListBox( m_tmhmContainer, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_tmhmPokemonListChoices, wxLB_SINGLE );
	tmhmContainerSizer->Add( m_tmhmPokemonList, 1, wxALL|wxEXPAND, 8 );


	m_tmhmContainer->SetSizer( tmhmContainerSizer );
	m_tmhmContainer->Layout();
	tmhmContainerSizer->Fit( m_tmhmContainer );
	tmhmInnerPanelSizer->Add( m_tmhmContainer, 1, wxEXPAND | wxALL, 2 );


	tmhmInnerPanel->SetSizer( tmhmInnerPanelSizer );
	tmhmInnerPanel->Layout();
	tmhmInnerPanelSizer->Fit( tmhmInnerPanel );
	tmhmPanelSizer->Add( tmhmInnerPanel, 1, wxEXPAND | wxALL, 2 );


	tmhmPanel->SetSizer( tmhmPanelSizer );
	tmhmPanel->Layout();
	tmhmPanelSizer->Fit( tmhmPanel );
	mainTabs->AddPage( tmhmPanel, wxT("기술머신"), false );
	wxPanel* trainerGroupPanel;
	trainerGroupPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* trainerGroupPanelSizer;
	trainerGroupPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* trainerGroupInnerPanel;
	trainerGroupInnerPanel = new wxPanel( trainerGroupPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* trainerGroupInnerPanelSizer;
	trainerGroupInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_trainerGroupList = new ui::ColoredListBox( trainerGroupInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	trainerGroupInnerPanelSizer->Add( m_trainerGroupList, 0, wxALL|wxEXPAND, 2 );

	m_trainerGroupContainer = new wxScrolledWindow( trainerGroupInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxHSCROLL|wxVSCROLL );
	m_trainerGroupContainer->SetScrollRate( 5, 16 );
	m_trainerGroupContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* trainerGroupContainerSizer;
	trainerGroupContainerSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* trainerGroupNameLabel;
	trainerGroupNameLabel = new ui::LabeledSeparator( m_trainerGroupContainer, wxID_ANY, wxT("이름"), wxDefaultPosition, wxDefaultSize, 0 );
	trainerGroupNameLabel->Wrap( -1 );
	trainerGroupContainerSizer->Add( trainerGroupNameLabel, 0, wxALL|wxEXPAND, 5 );

	m_trainerGroupNameText = new wxTextCtrl( m_trainerGroupContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_trainerGroupNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_trainerGroupNameText->SetMaxLength( 12 );
	}
	#else
	m_trainerGroupNameText->SetMaxLength( 12 );
	#endif
	trainerGroupContainerSizer->Add( m_trainerGroupNameText, 0, wxALL, 8 );


	trainerGroupContainerSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* trainerGroupImageLabel;
	trainerGroupImageLabel = new ui::LabeledSeparator( m_trainerGroupContainer, wxID_ANY, wxT("이미지 && 색상"), wxDefaultPosition, wxDefaultSize, 0 );
	trainerGroupImageLabel->Wrap( -1 );
	trainerGroupContainerSizer->Add( trainerGroupImageLabel, 0, wxALL|wxEXPAND, 5 );

	m_trainerGroupImageContainer = new wxSimplebook( m_trainerGroupContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* trainerGroupImagePanel;
	trainerGroupImagePanel = new wxPanel( m_trainerGroupImageContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* trainerGroupImagePanelSizer;
	trainerGroupImagePanelSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* trainerGroupImageSizer;
	trainerGroupImageSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* trainerGroupImageImageLabel;
	trainerGroupImageImageLabel = new wxStaticText( trainerGroupImagePanel, wxID_ANY, wxT("이미지："), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	trainerGroupImageImageLabel->Wrap( -1 );
	trainerGroupImageSizer->Add( trainerGroupImageImageLabel, 0, wxALL, 5 );

	m_trainerGroupImage = new ui::ImageEditorPanel( trainerGroupImagePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	trainerGroupImageSizer->Add( m_trainerGroupImage, 0, wxBOTTOM|wxLEFT, 5 );

	m_trainerGroupBackImagePanel = new wxPanel( trainerGroupImagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* trainerGroupBackImagePanelSizer;
	trainerGroupBackImagePanelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticLine* trainerGroupImageSeparator;
	trainerGroupImageSeparator = new wxStaticLine( m_trainerGroupBackImagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	trainerGroupBackImagePanelSizer->Add( trainerGroupImageSeparator, 0, wxBOTTOM|wxEXPAND|wxLEFT, 5 );

	m_trainerGroupBackImage_1 = new ui::ImageEditorPanel( m_trainerGroupBackImagePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	trainerGroupBackImagePanelSizer->Add( m_trainerGroupBackImage_1, 0, wxBOTTOM|wxLEFT, 5 );

	m_trainerGroupBackImage_2 = new ui::ImageEditorPanel( m_trainerGroupBackImagePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,64 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	trainerGroupBackImagePanelSizer->Add( m_trainerGroupBackImage_2, 0, wxBOTTOM|wxLEFT, 5 );


	m_trainerGroupBackImagePanel->SetSizer( trainerGroupBackImagePanelSizer );
	m_trainerGroupBackImagePanel->Layout();
	trainerGroupBackImagePanelSizer->Fit( m_trainerGroupBackImagePanel );
	trainerGroupImageSizer->Add( m_trainerGroupBackImagePanel, 0, 0, 0 );


	trainerGroupImagePanelSizer->Add( trainerGroupImageSizer, 0, wxLEFT|wxRIGHT|wxTOP, 5 );

	wxBoxSizer* trainerGroupColorSizer;
	trainerGroupColorSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* trainerGroupImageColorLabel;
	trainerGroupImageColorLabel = new wxStaticText( trainerGroupImagePanel, wxID_ANY, wxT("색상："), wxDefaultPosition, wxSize( 48,-1 ), 0 );
	trainerGroupImageColorLabel->Wrap( -1 );
	trainerGroupColorSizer->Add( trainerGroupImageColorLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_trainerGroupColor_1 = new ui::ColorPickerPanel( trainerGroupImagePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	trainerGroupColorSizer->Add( m_trainerGroupColor_1, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );

	m_trainerGroupColor_2 = new ui::ColorPickerPanel( trainerGroupImagePanel, wxID_ANY, wxDefaultPosition, wxSize( 64,24 ), wxBORDER_THEME|wxTAB_TRAVERSAL );
	trainerGroupColorSizer->Add( m_trainerGroupColor_2, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );


	trainerGroupImagePanelSizer->Add( trainerGroupColorSizer, 0, wxLEFT|wxRIGHT, 5 );


	trainerGroupImagePanel->SetSizer( trainerGroupImagePanelSizer );
	trainerGroupImagePanel->Layout();
	trainerGroupImagePanelSizer->Fit( trainerGroupImagePanel );
	m_trainerGroupImageContainer->AddPage( trainerGroupImagePanel, wxEmptyString, true );
	wxPanel* trainerGroupImageWarningPanel;
	trainerGroupImageWarningPanel = new wxPanel( m_trainerGroupImageContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* trainerGroupImageWarningPanelSizer;
	trainerGroupImageWarningPanelSizer = new wxBoxSizer( wxVERTICAL );

	m_trainerGroupImageWarningLabel = new wxStaticText( trainerGroupImageWarningPanel, wxID_ANY, wxT("'{rival}' 항목의 이미지를 편집해 주세요."), wxDefaultPosition, wxDefaultSize, 0 );
	m_trainerGroupImageWarningLabel->Wrap( -1 );
	trainerGroupImageWarningPanelSizer->Add( m_trainerGroupImageWarningLabel, 0, wxALL, 32 );


	trainerGroupImageWarningPanel->SetSizer( trainerGroupImageWarningPanelSizer );
	trainerGroupImageWarningPanel->Layout();
	trainerGroupImageWarningPanelSizer->Fit( trainerGroupImageWarningPanel );
	m_trainerGroupImageContainer->AddPage( trainerGroupImageWarningPanel, wxEmptyString, false );

	trainerGroupContainerSizer->Add( m_trainerGroupImageContainer, 0, wxEXPAND | wxALL, 5 );


	trainerGroupContainerSizer->Add( 0, 8, 0, 0, 0 );


	m_trainerGroupContainer->SetSizer( trainerGroupContainerSizer );
	m_trainerGroupContainer->Layout();
	trainerGroupContainerSizer->Fit( m_trainerGroupContainer );
	trainerGroupInnerPanelSizer->Add( m_trainerGroupContainer, 1, wxEXPAND | wxALL, 2 );


	trainerGroupInnerPanel->SetSizer( trainerGroupInnerPanelSizer );
	trainerGroupInnerPanel->Layout();
	trainerGroupInnerPanelSizer->Fit( trainerGroupInnerPanel );
	trainerGroupPanelSizer->Add( trainerGroupInnerPanel, 1, wxEXPAND | wxALL, 2 );


	trainerGroupPanel->SetSizer( trainerGroupPanelSizer );
	trainerGroupPanel->Layout();
	trainerGroupPanelSizer->Fit( trainerGroupPanel );
	mainTabs->AddPage( trainerGroupPanel, wxT("트레이너 그룹"), false );
	wxPanel* typePanel;
	typePanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* typePanelSizer;
	typePanelSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* typeInnerPanel;
	typeInnerPanel = new wxPanel( typePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* typeInnerPanelSizer;
	typeInnerPanelSizer = new wxBoxSizer( wxHORIZONTAL );

	m_typeList = new ui::ColoredListBox( typeInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 128,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	typeInnerPanelSizer->Add( m_typeList, 0, wxALL|wxEXPAND, 2 );

	m_typeContainer = new wxScrolledWindow( typeInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxHSCROLL|wxVSCROLL );
	m_typeContainer->SetScrollRate( 5, 16 );
	m_typeContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* typeContainerSizer;
	typeContainerSizer = new wxBoxSizer( wxVERTICAL );

	ui::LabeledSeparator* typeNameLabel;
	typeNameLabel = new ui::LabeledSeparator( m_typeContainer, wxID_ANY, wxT("이름"), wxDefaultPosition, wxDefaultSize, 0 );
	typeNameLabel->Wrap( -1 );
	typeContainerSizer->Add( typeNameLabel, 0, wxALL|wxEXPAND, 5 );

	m_typeNameText = new wxTextCtrl( m_typeContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_typeNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_typeNameText->SetMaxLength( 5 );
	}
	#else
	m_typeNameText->SetMaxLength( 5 );
	#endif
	typeContainerSizer->Add( m_typeNameText, 0, wxALL, 8 );


	typeContainerSizer->Add( 0, 8, 0, wxEXPAND, 0 );

	ui::LabeledSeparator* typeMatchupsLabel;
	typeMatchupsLabel = new ui::LabeledSeparator( m_typeContainer, wxID_ANY, wxT("상성"), wxDefaultPosition, wxDefaultSize, 0 );
	typeMatchupsLabel->Wrap( -1 );
	typeContainerSizer->Add( typeMatchupsLabel, 0, wxALL|wxEXPAND, 5 );

	m_typeMatchupList = new ui::ColoredListCtrl( m_typeContainer, wxID_ANY, wxDefaultPosition, wxSize( -1,240 ), wxLC_REPORT|wxLC_SINGLE_SEL );
	typeContainerSizer->Add( m_typeMatchupList, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 8 );

	wxBoxSizer* typeMatchupsButtonsSizer;
	typeMatchupsButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_typeMatchupsAddButton = new wxButton( m_typeContainer, wxID_ADD, wxT("추가..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_typeMatchupsAddButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	typeMatchupsButtonsSizer->Add( m_typeMatchupsAddButton, 0, wxRIGHT, 5 );

	m_typeMatchupsEditButton = new wxButton( m_typeContainer, wxID_EDIT, wxT("수정..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_typeMatchupsEditButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	typeMatchupsButtonsSizer->Add( m_typeMatchupsEditButton, 0, wxRIGHT, 5 );

	m_typeMatchupsRemoveButton = new wxButton( m_typeContainer, wxID_REMOVE, wxT("삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_typeMatchupsRemoveButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	typeMatchupsButtonsSizer->Add( m_typeMatchupsRemoveButton, 0, wxRIGHT, 5 );

	m_typeMatchupsClearButton = new wxButton( m_typeContainer, wxID_CLEAR, wxT("전체 삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_typeMatchupsClearButton->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_typeMatchupsClearButton->SetForegroundColour( wxColour( 255, 0, 0 ) );

	typeMatchupsButtonsSizer->Add( m_typeMatchupsClearButton, 0, wxRIGHT, 5 );


	typeContainerSizer->Add( typeMatchupsButtonsSizer, 0, wxLEFT|wxRIGHT, 8 );


	typeContainerSizer->Add( 0, 8, 0, 0, 0 );

	ui::LabeledSeparator* typeWeatherModifierLabel;
	typeWeatherModifierLabel = new ui::LabeledSeparator( m_typeContainer, wxID_ANY, wxT("날씨 보정"), wxDefaultPosition, wxDefaultSize, 0 );
	typeWeatherModifierLabel->Wrap( -1 );
	typeContainerSizer->Add( typeWeatherModifierLabel, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* typeWeatherModifierSizer;
	typeWeatherModifierSizer = new wxBoxSizer( wxHORIZONTAL );

	wxString m_typeWeatherModifierRainRadioBoxChoices[] = { wxT("없음"), wxT("위력 증가"), wxT("위력 하락") };
	int m_typeWeatherModifierRainRadioBoxNChoices = sizeof( m_typeWeatherModifierRainRadioBoxChoices ) / sizeof( wxString );
	m_typeWeatherModifierRainRadioBox = new wxRadioBox( m_typeContainer, wxID_ANY, wxT("비바라기"), wxDefaultPosition, wxDefaultSize, m_typeWeatherModifierRainRadioBoxNChoices, m_typeWeatherModifierRainRadioBoxChoices, 1, wxRA_SPECIFY_COLS );
	m_typeWeatherModifierRainRadioBox->SetSelection( 0 );
	typeWeatherModifierSizer->Add( m_typeWeatherModifierRainRadioBox, 0, wxALL, 4 );

	wxString m_typeWeatherModifierSunRadioBoxChoices[] = { wxT("없음"), wxT("위력 증가"), wxT("위력 하락") };
	int m_typeWeatherModifierSunRadioBoxNChoices = sizeof( m_typeWeatherModifierSunRadioBoxChoices ) / sizeof( wxString );
	m_typeWeatherModifierSunRadioBox = new wxRadioBox( m_typeContainer, wxID_ANY, wxT("쾌청"), wxDefaultPosition, wxDefaultSize, m_typeWeatherModifierSunRadioBoxNChoices, m_typeWeatherModifierSunRadioBoxChoices, 1, wxRA_SPECIFY_COLS );
	m_typeWeatherModifierSunRadioBox->SetSelection( 0 );
	typeWeatherModifierSizer->Add( m_typeWeatherModifierSunRadioBox, 0, wxALL, 4 );

	wxString m_typeWeatherModifierSandstormRadioBoxChoices[] = { wxT("없음"), wxT("위력 증가"), wxT("위력 하락") };
	int m_typeWeatherModifierSandstormRadioBoxNChoices = sizeof( m_typeWeatherModifierSandstormRadioBoxChoices ) / sizeof( wxString );
	m_typeWeatherModifierSandstormRadioBox = new wxRadioBox( m_typeContainer, wxID_ANY, wxT("모래바람"), wxDefaultPosition, wxDefaultSize, m_typeWeatherModifierSandstormRadioBoxNChoices, m_typeWeatherModifierSandstormRadioBoxChoices, 1, wxRA_SPECIFY_COLS );
	m_typeWeatherModifierSandstormRadioBox->SetSelection( 0 );
	typeWeatherModifierSizer->Add( m_typeWeatherModifierSandstormRadioBox, 0, wxALL, 4 );


	typeContainerSizer->Add( typeWeatherModifierSizer, 0, wxALL|wxEXPAND, 4 );


	typeContainerSizer->Add( 0, 8, 0, 0, 0 );


	m_typeContainer->SetSizer( typeContainerSizer );
	m_typeContainer->Layout();
	typeContainerSizer->Fit( m_typeContainer );
	typeInnerPanelSizer->Add( m_typeContainer, 1, wxEXPAND | wxALL, 2 );


	typeInnerPanel->SetSizer( typeInnerPanelSizer );
	typeInnerPanel->Layout();
	typeInnerPanelSizer->Fit( typeInnerPanel );
	typePanelSizer->Add( typeInnerPanel, 1, wxEXPAND | wxALL, 2 );


	typePanel->SetSizer( typePanelSizer );
	typePanel->Layout();
	typePanelSizer->Fit( typePanel );
	mainTabs->AddPage( typePanel, wxT("타입"), false );

	panelSizer->Add( mainTabs, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( panelSizer );
	this->Layout();

	// Connect Events
	m_pokemonEvolutionAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonEvolutionModify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonEvolutionRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonEvolutionClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonMovesImport->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonMovesButtonClick ), NULL, this );
	m_pokemonMovesAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonMovesButtonClick ), NULL, this );
	m_pokemonMovesModify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonMovesButtonClick ), NULL, this );
	m_pokemonMovesRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonMovesButtonClick ), NULL, this );
	m_pokemonMovesClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonMovesButtonClick ), NULL, this );
	m_pokemonEggMovesAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEggMovesButtonClick ), NULL, this );
	m_pokemonEggMovesModify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEggMovesButtonClick ), NULL, this );
	m_pokemonEggMovesRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEggMovesButtonClick ), NULL, this );
	m_pokemonEggMovesClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEggMovesButtonClick ), NULL, this );
	pokemonTMHMsCheckAllButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonTMHMsButtonClick ), NULL, this );
	pokemonTMHMsClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonTMHMsButtonClick ), NULL, this );
	tmhmPokemonCheckAllButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnTMHMsButtonClick ), NULL, this );
	tmhmPokemonClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnTMHMsButtonClick ), NULL, this );
	m_typeMatchupsAddButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnTypeMatchupsButtonClick ), NULL, this );
	m_typeMatchupsEditButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnTypeMatchupsButtonClick ), NULL, this );
	m_typeMatchupsRemoveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnTypeMatchupsButtonClick ), NULL, this );
	m_typeMatchupsClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnTypeMatchupsButtonClick ), NULL, this );
	m_typeWeatherModifierRainRadioBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( DatabasePanelBase::OnTypeWeatherModifierRadioBox ), NULL, this );
	m_typeWeatherModifierSunRadioBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( DatabasePanelBase::OnTypeWeatherModifierRadioBox ), NULL, this );
	m_typeWeatherModifierSandstormRadioBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( DatabasePanelBase::OnTypeWeatherModifierRadioBox ), NULL, this );
}

DatabasePanelBase::~DatabasePanelBase()
{
}

AboutDialogBase::AboutDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* appInfoSizer;
	appInfoSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBitmap* appIconBitmap;
	appIconBitmap = new wxStaticBitmap( this, wxID_ANY, icon_about_png_to_wx_bitmap(), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	appInfoSizer->Add( appIconBitmap, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* appInfoAuthorSizer;
	appInfoAuthorSizer = new wxBoxSizer( wxVERTICAL );

	m_authorText = new wxStaticText( this, wxID_ANY, wxT("{author}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_authorText->Wrap( -1 );
	appInfoAuthorSizer->Add( m_authorText, 0, wxALL|wxEXPAND, 5 );

	m_versionText = new wxStaticText( this, wxID_ANY, wxT("{version}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_versionText->Wrap( -1 );
	appInfoAuthorSizer->Add( m_versionText, 0, wxALL|wxEXPAND, 5 );


	appInfoSizer->Add( appInfoAuthorSizer, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	dialogSizer->Add( appInfoSizer, 0, wxALL|wxEXPAND, 5 );

	m_aboutContentTabs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* versionPanel;
	versionPanel = new wxPanel( m_aboutContentTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* versionSizer;
	versionSizer = new wxBoxSizer( wxVERTICAL );

	m_versionHtml = new wxHtmlWindow( versionPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxBORDER_THEME );
	versionSizer->Add( m_versionHtml, 1, wxALL|wxEXPAND, 5 );


	versionPanel->SetSizer( versionSizer );
	versionPanel->Layout();
	versionSizer->Fit( versionPanel );
	m_aboutContentTabs->AddPage( versionPanel, wxT("버전 기록"), true );
	wxPanel* thirdPartyNoticesPanel;
	thirdPartyNoticesPanel = new wxPanel( m_aboutContentTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* thirdPartyNoticesSizer;
	thirdPartyNoticesSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* thirdPartyNoticesInnerPanel;
	thirdPartyNoticesInnerPanel = new wxPanel( thirdPartyNoticesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME|wxTAB_TRAVERSAL );
	wxBoxSizer* thirdPartyNoticesInnerSizer;
	thirdPartyNoticesInnerSizer = new wxBoxSizer( wxVERTICAL );

	m_thirdPartyNoticesText = new wxTextCtrl( thirdPartyNoticesInnerPanel, wxID_ANY, wxT("{open_source_licenses}"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxBORDER_NONE );
	m_thirdPartyNoticesText->SetFont( wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );

	thirdPartyNoticesInnerSizer->Add( m_thirdPartyNoticesText, 1, wxALL|wxEXPAND, 0 );


	thirdPartyNoticesInnerPanel->SetSizer( thirdPartyNoticesInnerSizer );
	thirdPartyNoticesInnerPanel->Layout();
	thirdPartyNoticesInnerSizer->Fit( thirdPartyNoticesInnerPanel );
	thirdPartyNoticesSizer->Add( thirdPartyNoticesInnerPanel, 1, wxEXPAND | wxALL, 5 );


	thirdPartyNoticesPanel->SetSizer( thirdPartyNoticesSizer );
	thirdPartyNoticesPanel->Layout();
	thirdPartyNoticesSizer->Fit( thirdPartyNoticesPanel );
	m_aboutContentTabs->AddPage( thirdPartyNoticesPanel, wxT("3자 라이선스 고지"), false );
	wxPanel* testPanel;
	testPanel = new wxPanel( m_aboutContentTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* testPanelSizer;
	testPanelSizer = new wxBoxSizer( wxVERTICAL );

	ui::ScriptTextCtrl* testScriptTextCtrl;
	testScriptTextCtrl = new ui::ScriptTextCtrl( testPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB, wxEmptyString );
	testScriptTextCtrl->SetUseTabs( true );
	testScriptTextCtrl->SetTabWidth( 4 );
	testScriptTextCtrl->SetIndent( 4 );
	testScriptTextCtrl->SetTabIndents( true );
	testScriptTextCtrl->SetBackSpaceUnIndents( true );
	testScriptTextCtrl->SetViewEOL( false );
	testScriptTextCtrl->SetViewWhiteSpace( false );
	testScriptTextCtrl->SetMarginWidth( 2, 0 );
	testScriptTextCtrl->SetIndentationGuides( false );
	testScriptTextCtrl->SetReadOnly( false );
	testScriptTextCtrl->SetMarginWidth( 1, 0 );
	testScriptTextCtrl->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	testScriptTextCtrl->SetMarginWidth( 0, testScriptTextCtrl->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") );
		testScriptTextCtrl->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	testScriptTextCtrl->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	testScriptTextCtrl->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	testScriptTextCtrl->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	testScriptTextCtrl->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	testScriptTextCtrl->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	testScriptTextCtrl->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	testScriptTextCtrl->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	testScriptTextCtrl->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	testScriptTextCtrl->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	testScriptTextCtrl->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	testScriptTextCtrl->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	testScriptTextCtrl->SetFont( wxFont( 11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );

	testPanelSizer->Add( testScriptTextCtrl, 1, wxEXPAND | wxALL, 5 );


	testPanel->SetSizer( testPanelSizer );
	testPanel->Layout();
	testPanelSizer->Fit( testPanel );
	m_aboutContentTabs->AddPage( testPanel, wxT("테스트"), false );

	dialogSizer->Add( m_aboutContentTabs, 1, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

	wxPanel* bottomPanel;
	bottomPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bottomSizer;
	bottomSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* okButton;
	okButton = new wxButton( bottomPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );

	okButton->SetDefault();
	bottomSizer->Add( okButton, 0, wxRIGHT, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( bottomPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	cancelButton->Hide();

	bottomSizer->Add( cancelButton, 0, wxRIGHT, 5 );


	bottomPanel->SetSizer( bottomSizer );
	bottomPanel->Layout();
	bottomSizer->Fit( bottomPanel );
	dialogSizer->Add( bottomPanel, 0, wxALIGN_RIGHT|wxALL, 10 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	okButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialogBase::OnOkButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialogBase::OnCancelButtonClick ), NULL, this );
}

AboutDialogBase::~AboutDialogBase()
{
}

EvolutionEditorDialogBase::EvolutionEditorDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* contentPanel;
	contentPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* contentSizer;
	contentSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* pokemonSizer;
	pokemonSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonLabel;
	pokemonLabel = new wxStaticText( contentPanel, wxID_ANY, wxT("진화 후 포켓몬："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonLabel->Wrap( -1 );
	pokemonSizer->Add( pokemonLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemon = new wxComboBox( contentPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	pokemonSizer->Add( m_pokemon, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 16 );


	contentSizer->Add( pokemonSizer, 0, wxALL|wxEXPAND, 5 );

	wxStaticLine* separator_0;
	separator_0 = new wxStaticLine( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	contentSizer->Add( separator_0, 0, wxEXPAND | wxALL, 5 );

	m_levelUpRadio = new wxRadioButton( contentPanel, wxID_ANY, wxT("레벨 업"), wxDefaultPosition, wxDefaultSize, 0 );
	m_levelUpRadio->SetValue( true );
	contentSizer->Add( m_levelUpRadio, 0, wxALL, 5 );

	m_levelUpPanel = new wxPanel( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* levelUpSizer;
	levelUpSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* commonSizer;
	commonSizer = new wxBoxSizer( wxHORIZONTAL );

	m_levelUpCommonRadio = new wxRadioButton( m_levelUpPanel, wxID_ANY, wxT("일반"), wxDefaultPosition, wxDefaultSize, 0 );
	m_levelUpCommonRadio->SetValue( true );
	commonSizer->Add( m_levelUpCommonRadio, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_level = new wxSpinCtrlDouble( m_levelUpPanel, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 0, 1 );
	m_level->SetDigits( 0 );
	commonSizer->Add( m_level, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_levelTypeComboBox = new wxComboBox( m_levelUpPanel, wxID_ANY, wxT("레벨 업"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_levelTypeComboBox->Append( wxT("레벨 업") );
	m_levelTypeComboBox->Append( wxT("공격이 방어보다 높을 때 + 레벨 업") );
	m_levelTypeComboBox->Append( wxT("방어가 공격보다 높을 때 + 레벨 업") );
	m_levelTypeComboBox->Append( wxT("공격과 방어가 같을 때 + 레벨 업") );
	m_levelTypeComboBox->SetSelection( 0 );
	commonSizer->Add( m_levelTypeComboBox, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	levelUpSizer->Add( commonSizer, 0, wxEXPAND, 5 );

	wxBoxSizer* happinessSizer;
	happinessSizer = new wxBoxSizer( wxHORIZONTAL );

	m_happinessRadio = new wxRadioButton( m_levelUpPanel, wxID_ANY, wxT("친밀도"), wxDefaultPosition, wxDefaultSize, 0 );
	happinessSizer->Add( m_happinessRadio, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_happinessTypeComboBox = new wxComboBox( m_levelUpPanel, wxID_ANY, wxT("시간과 관계없이 레벨 업"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_happinessTypeComboBox->Append( wxT("시간과 관계없이 레벨 업") );
	m_happinessTypeComboBox->Append( wxT("낮 시간에 레벨 업") );
	m_happinessTypeComboBox->Append( wxT("밤 시간에 레벨 업") );
	m_happinessTypeComboBox->SetSelection( 0 );
	happinessSizer->Add( m_happinessTypeComboBox, 4, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	levelUpSizer->Add( happinessSizer, 0, wxEXPAND, 5 );


	m_levelUpPanel->SetSizer( levelUpSizer );
	m_levelUpPanel->Layout();
	levelUpSizer->Fit( m_levelUpPanel );
	contentSizer->Add( m_levelUpPanel, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 16 );

	m_useItemRadio = new wxRadioButton( contentPanel, wxID_ANY, wxT("도구 사용"), wxDefaultPosition, wxDefaultSize, 0 );
	contentSizer->Add( m_useItemRadio, 0, wxALL, 5 );

	m_useItemPanel = new wxPanel( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* useItemSizer;
	useItemSizer = new wxBoxSizer( wxVERTICAL );

	m_useItems = new wxComboBox( m_useItemPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	useItemSizer->Add( m_useItems, 1, wxALL|wxEXPAND, 5 );


	m_useItemPanel->SetSizer( useItemSizer );
	m_useItemPanel->Layout();
	useItemSizer->Fit( m_useItemPanel );
	contentSizer->Add( m_useItemPanel, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 16 );

	m_tradeRadio = new wxRadioButton( contentPanel, wxID_ANY, wxT("통신교환"), wxDefaultPosition, wxDefaultSize, 0 );
	contentSizer->Add( m_tradeRadio, 0, wxALL, 5 );

	m_tradePanel = new wxPanel( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* tradeSizer;
	tradeSizer = new wxBoxSizer( wxHORIZONTAL );

	m_tradeGaveItemCheckBox = new wxCheckBox( m_tradePanel, wxID_ANY, wxT("도구를 지닌 상태"), wxDefaultPosition, wxDefaultSize, 0 );
	tradeSizer->Add( m_tradeGaveItemCheckBox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tradeItems = new wxComboBox( m_tradePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	tradeSizer->Add( m_tradeItems, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	m_tradePanel->SetSizer( tradeSizer );
	m_tradePanel->Layout();
	tradeSizer->Fit( m_tradePanel );
	contentSizer->Add( m_tradePanel, 0, wxEXPAND|wxLEFT|wxRIGHT, 16 );


	contentSizer->Add( 0, 8, 0, 0, 0 );

	wxStaticLine* separator_1;
	separator_1 = new wxStaticLine( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	contentSizer->Add( separator_1, 0, wxEXPAND | wxALL, 5 );


	contentPanel->SetSizer( contentSizer );
	contentPanel->Layout();
	contentSizer->Fit( contentPanel );
	dialogSizer->Add( contentPanel, 1, wxEXPAND | wxALL, 8 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButton;
	confirmButton = new wxButton( buttonsPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );

	confirmButton->SetDefault();
	buttonsSizer->Add( confirmButton, 0, wxALL, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( buttonsPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( cancelButton, 0, wxALL, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	dialogSizer->Add( buttonsPanel, 0, wxALIGN_RIGHT|wxALL, 8 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	confirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EvolutionEditorDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EvolutionEditorDialogBase::OnCancelButtonClick ), NULL, this );
}

EvolutionEditorDialogBase::~EvolutionEditorDialogBase()
{
}

MoveEditorDialogBase::MoveEditorDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* contentPanel;
	contentPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* contentPanelSizer;
	contentPanelSizer = new wxBoxSizer( wxVERTICAL );

	m_contentGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	m_contentGrid->AddGrowableCol( 1 );
	m_contentGrid->SetFlexibleDirection( wxBOTH );
	m_contentGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_levelLabel = new wxStaticText( contentPanel, wxID_ANY, wxT("레벨："), wxDefaultPosition, wxDefaultSize, 0 );
	m_levelLabel->Wrap( -1 );
	m_contentGrid->Add( m_levelLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_levelSpinCtrl = new wxSpinCtrlDouble( contentPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1, 1 );
	m_levelSpinCtrl->SetDigits( 0 );
	m_contentGrid->Add( m_levelSpinCtrl, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* moveLabel;
	moveLabel = new wxStaticText( contentPanel, wxID_ANY, wxT("기술："), wxDefaultPosition, wxDefaultSize, 0 );
	moveLabel->Wrap( -1 );
	m_contentGrid->Add( moveLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_movesComboBox = new wxComboBox( contentPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_contentGrid->Add( m_movesComboBox, 0, wxALL|wxEXPAND, 5 );


	contentPanelSizer->Add( m_contentGrid, 0, wxEXPAND, 5 );

	wxStaticLine* contentSeparator;
	contentSeparator = new wxStaticLine( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	contentPanelSizer->Add( contentSeparator, 0, wxEXPAND | wxALL, 5 );


	contentPanel->SetSizer( contentPanelSizer );
	contentPanel->Layout();
	contentPanelSizer->Fit( contentPanel );
	dialogSizer->Add( contentPanel, 1, wxEXPAND | wxALL, 5 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButton;
	confirmButton = new wxButton( buttonsPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );

	confirmButton->SetDefault();
	buttonsSizer->Add( confirmButton, 0, wxALL, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( buttonsPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( cancelButton, 0, wxALL, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	dialogSizer->Add( buttonsPanel, 0, wxALIGN_RIGHT|wxALL, 5 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	confirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MoveEditorDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MoveEditorDialogBase::OnCancelButtonClick ), NULL, this );
}

MoveEditorDialogBase::~MoveEditorDialogBase()
{
}

TypeMatchupEditorDialogBase::TypeMatchupEditorDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* contentPanel;
	contentPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* contentPanelSizer;
	contentPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* contentGrid;
	contentGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	contentGrid->AddGrowableCol( 1 );
	contentGrid->SetFlexibleDirection( wxBOTH );
	contentGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* typeLabel;
	typeLabel = new wxStaticText( contentPanel, wxID_ANY, wxT("공격 대상 타입："), wxDefaultPosition, wxDefaultSize, 0 );
	typeLabel->Wrap( -1 );
	contentGrid->Add( typeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_typeComboBox = new wxComboBox( contentPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	contentGrid->Add( m_typeComboBox, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* effectivenessLabel;
	effectivenessLabel = new wxStaticText( contentPanel, wxID_ANY, wxT("효과："), wxDefaultPosition, wxDefaultSize, 0 );
	effectivenessLabel->Wrap( -1 );
	contentGrid->Add( effectivenessLabel, 0, wxALL, 5 );

	m_effectivenessComboBox = new wxComboBox( contentPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_effectivenessComboBox->Append( wxT("효과가 부족함") );
	m_effectivenessComboBox->Append( wxT("효과가 굉장함") );
	m_effectivenessComboBox->Append( wxT("효과가 없음") );
	contentGrid->Add( m_effectivenessComboBox, 0, wxALL|wxEXPAND, 5 );


	contentPanelSizer->Add( contentGrid, 0, wxEXPAND, 5 );

	m_foresightCheckBox = new wxCheckBox( contentPanel, wxID_ANY, wxT("꿰뚫어보기 상태일 때 효과를 무시"), wxDefaultPosition, wxDefaultSize, 0 );
	contentPanelSizer->Add( m_foresightCheckBox, 0, wxALL, 5 );

	wxStaticLine* contentSeparator;
	contentSeparator = new wxStaticLine( contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	contentPanelSizer->Add( contentSeparator, 0, wxEXPAND | wxALL, 5 );


	contentPanel->SetSizer( contentPanelSizer );
	contentPanel->Layout();
	contentPanelSizer->Fit( contentPanel );
	dialogSizer->Add( contentPanel, 1, wxEXPAND | wxALL, 5 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButton;
	confirmButton = new wxButton( buttonsPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );

	confirmButton->SetDefault();
	buttonsSizer->Add( confirmButton, 0, wxALL, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( buttonsPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( cancelButton, 0, wxALL, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	dialogSizer->Add( buttonsPanel, 0, wxALIGN_RIGHT|wxALL, 5 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	confirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TypeMatchupEditorDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TypeMatchupEditorDialogBase::OnCancelButtonClick ), NULL, this );
}

TypeMatchupEditorDialogBase::~TypeMatchupEditorDialogBase()
{
}

ImportMoveDialogBase::ImportMoveDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,400 ), wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* contentsPanel;
	contentsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* contentsSizer;
	contentsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonListBox = new ui::ColoredListBox( contentsPanel, wxID_ANY, wxDefaultPosition, wxSize( 112,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	contentsSizer->Add( m_pokemonListBox, 0, wxALL|wxEXPAND, 2 );

	wxPanel* editorPanel;
	editorPanel = new wxPanel( contentsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxTAB_TRAVERSAL );
	editorPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );

	m_movesListCtrl = new ui::ColoredListCtrl( editorPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	editorSizer->Add( m_movesListCtrl, 1, wxALL|wxEXPAND, 5 );

	m_ignoreButton = new wxButton( editorPanel, wxID_ANY, wxT("제외"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ignoreButton->SetForegroundColour( wxColour( 0, 0, 0 ) );

	editorSizer->Add( m_ignoreButton, 0, wxALIGN_RIGHT|wxALL, 5 );


	editorPanel->SetSizer( editorSizer );
	editorPanel->Layout();
	editorSizer->Fit( editorPanel );
	contentsSizer->Add( editorPanel, 1, wxEXPAND | wxALL, 2 );


	contentsPanel->SetSizer( contentsSizer );
	contentsPanel->Layout();
	contentsSizer->Fit( contentsPanel );
	dialogSizer->Add( contentsPanel, 1, wxEXPAND | wxALL, 2 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButton;
	confirmButton = new wxButton( buttonsPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );

	confirmButton->SetDefault();
	buttonsSizer->Add( confirmButton, 0, wxALL, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( buttonsPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( cancelButton, 0, wxALL, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	dialogSizer->Add( buttonsPanel, 0, wxALIGN_RIGHT|wxALL, 5 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_ignoreButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImportMoveDialogBase::OnIgnoreButtonClick ), NULL, this );
	confirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImportMoveDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ImportMoveDialogBase::OnCancelButtonClick ), NULL, this );
}

ImportMoveDialogBase::~ImportMoveDialogBase()
{
}

ProgressDialogBase::ProgressDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* contentsPanel;
	contentsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	contentsPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* contentsSizer;
	contentsSizer = new wxBoxSizer( wxVERTICAL );


	contentsSizer->Add( 0, 0, 1, 0, 0 );

	m_progressGauge = new wxGauge( contentsPanel, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_progressGauge->SetValue( 0 );
	contentsSizer->Add( m_progressGauge, 0, wxEXPAND|wxLEFT|wxRIGHT, 24 );

	m_messageLabel = new wxStaticText( contentsPanel, wxID_ANY, wxT("{message}"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL|wxST_NO_AUTORESIZE );
	m_messageLabel->Wrap( -1 );
	contentsSizer->Add( m_messageLabel, 0, wxEXPAND|wxTOP, 16 );


	contentsSizer->Add( 0, 0, 1, 0, 0 );


	contentsPanel->SetSizer( contentsSizer );
	contentsPanel->Layout();
	contentsSizer->Fit( contentsPanel );
	dialogSizer->Add( contentsPanel, 1, wxEXPAND, 5 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );


	buttonsSizer->Add( 0, 0, 1, 0, 5 );

	m_cancelButton = new wxButton( buttonsPanel, wxID_ANY, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( m_cancelButton, 0, wxRIGHT, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	dialogSizer->Add( buttonsPanel, 0, wxALL|wxEXPAND, 10 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ProgressDialogBase::OnInit ) );
	m_cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProgressDialogBase::OnCancelButtonClick ), NULL, this );
}

ProgressDialogBase::~ProgressDialogBase()
{
}

BadDataDialogBase::BadDataDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 560,440 ), wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* topPanel;
	topPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	topPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* listSizer;
	listSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* message;
	message = new wxStaticText( topPanel, wxID_ANY, wxT("아래 목록과 같이 일부 데이터가 손상되었습니다."), wxDefaultPosition, wxDefaultSize, 0 );
	message->Wrap( -1 );
	listSizer->Add( message, 0, wxALL|wxEXPAND, 16 );

	m_badDataList = new ui::ColoredListCtrl( topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	listSizer->Add( m_badDataList, 1, wxALL|wxEXPAND, 5 );


	topPanel->SetSizer( listSizer );
	topPanel->Layout();
	listSizer->Fit( topPanel );
	dialogSizer->Add( topPanel, 1, wxEXPAND | wxALL, 0 );

	wxPanel* bottomPanel;
	bottomPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButon;
	confirmButon = new wxButton( bottomPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxSize( -1,-1 ), 0 );

	confirmButon->SetDefault();
	buttonSizer->Add( confirmButon, 0, wxRIGHT, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( bottomPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	cancelButton->Hide();

	buttonSizer->Add( cancelButton, 0, wxRIGHT, 5 );


	bottomPanel->SetSizer( buttonSizer );
	bottomPanel->Layout();
	buttonSizer->Fit( bottomPanel );
	dialogSizer->Add( bottomPanel, 0, wxALIGN_RIGHT|wxALL, 10 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_SHOW, wxShowEventHandler( BadDataDialogBase::OnDialogShow ) );
	confirmButon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnCancelButtonClick ), NULL, this );
}

BadDataDialogBase::~BadDataDialogBase()
{
}

SearchDialogBase::SearchDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );

	wxBoxSizer* dialogSizer;
	dialogSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* contentsPanel;
	contentsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* contentsPanelSizer;
	contentsPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* keywordLabelSizer;
	keywordLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* keywordLabel;
	keywordLabel = new wxStaticText( contentsPanel, wxID_ANY, wxT("입력："), wxDefaultPosition, wxDefaultSize, 0 );
	keywordLabel->Wrap( -1 );
	keywordLabelSizer->Add( keywordLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_keywordText = new wxTextCtrl( contentsPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	keywordLabelSizer->Add( m_keywordText, 1, wxALL, 5 );


	contentsPanelSizer->Add( keywordLabelSizer, 0, wxALL|wxEXPAND, 5 );

	m_list = new ui::ColoredListCtrl( contentsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	contentsPanelSizer->Add( m_list, 1, wxALL|wxEXPAND, 0 );


	contentsPanel->SetSizer( contentsPanelSizer );
	contentsPanel->Layout();
	contentsPanelSizer->Fit( contentsPanel );
	dialogSizer->Add( contentsPanel, 1, wxEXPAND | wxALL, 4 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_confirmButton = new wxButton( buttonsPanel, wxID_OK, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );

	m_confirmButton->SetDefault();
	buttonsSizer->Add( m_confirmButton, 0, wxALL, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( buttonsPanel, wxID_CANCEL, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( cancelButton, 0, wxALL, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	dialogSizer->Add( buttonsPanel, 0, wxALIGN_RIGHT|wxALL, 5 );


	this->SetSizer( dialogSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_keywordText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SearchDialogBase::OnKeywordTextChanged ), NULL, this );
	m_confirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SearchDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SearchDialogBase::OnCancelButtonClick ), NULL, this );
}

SearchDialogBase::~SearchDialogBase()
{
}
