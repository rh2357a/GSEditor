///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui/controls/colored.h"
#include "ui/panels/database_panel.h"

#include "ui_base.h"

#include "icon_about.png.h"
#include "icon_exit.png.h"
#include "icon_folder.png.h"
#include "icon_play.png.h"
#include "icon_save.png.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 740,560 ), wxDefaultSize );

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
	wxMenuItem* gameTestPlayMenuItem;
	gameTestPlayMenuItem = new wxMenuItem( gameMenu, wxID_TEST_PLAY, wxString( wxT("테스트 플레이(&P)") ) + wxT('\t') + wxT("F5"), wxT("롬을 빌드하여 테스트합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	gameTestPlayMenuItem->SetBitmaps( icon_play_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	gameTestPlayMenuItem->SetBitmap( icon_play_png_to_wx_bitmap() );
	#endif
	gameMenu->Append( gameTestPlayMenuItem );

	gameMenu->AppendSeparator();

	wxMenuItem* gameExportToIpsMenuItem;
	gameExportToIpsMenuItem = new wxMenuItem( gameMenu, wxID_IPS, wxString( wxT("IPS 패치 생성...") ) , wxT("IPS 형식의 패치 파일을 생성합니다."), wxITEM_NORMAL );
	gameMenu->Append( gameExportToIpsMenuItem );

	wxMenuItem* gameExportToXdeltaMenuItem;
	gameExportToXdeltaMenuItem = new wxMenuItem( gameMenu, wxID_XDELTA, wxString( wxT("xdelta 패치 생성...") ) , wxT("xdelta 형식의 패치 파일을 생성합니다."), wxITEM_NORMAL );
	gameMenu->Append( gameExportToXdeltaMenuItem );

	m_mainMenuBar->Append( gameMenu, wxT("게임(&G)") );

	wxMenu* settingsMenu;
	settingsMenu = new wxMenu();
	m_settingsSetEmulatorMenuItem = new wxMenuItem( settingsMenu, wxID_EMULATOR, wxString( wxT("에뮬레이터 설정(&E)...") ) , wxEmptyString, wxITEM_NORMAL );
	settingsMenu->Append( m_settingsSetEmulatorMenuItem );

	m_mainMenuBar->Append( settingsMenu, wxT("설정(&S)") );

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
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, fileExitMenuItem->GetId());
	gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, gameTestPlayMenuItem->GetId());
	gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, gameExportToIpsMenuItem->GetId());
	gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, gameExportToXdeltaMenuItem->GetId());
	settingsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_settingsSetEmulatorMenuItem->GetId());
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, helpAboutMenuItem->GetId());
	this->Connect( openToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_saveToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_testPlayToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( exitToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
}

MainFrameBase::~MainFrameBase()
{
}

AboutDialogBase::AboutDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainBSizer;
	mainBSizer = new wxBoxSizer( wxVERTICAL );

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


	mainBSizer->Add( appInfoSizer, 0, wxALL|wxEXPAND, 5 );

	wxNotebook* aboutContentTabs;
	aboutContentTabs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* versionPanel;
	versionPanel = new wxPanel( aboutContentTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* versionSizer;
	versionSizer = new wxBoxSizer( wxVERTICAL );

	m_versionHtml = new wxHtmlWindow( versionPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxBORDER_STATIC );
	versionSizer->Add( m_versionHtml, 1, wxALL|wxEXPAND, 5 );


	versionPanel->SetSizer( versionSizer );
	versionPanel->Layout();
	versionSizer->Fit( versionPanel );
	aboutContentTabs->AddPage( versionPanel, wxT("버전 기록"), true );
	wxPanel* thirdPartyNoticesPanel;
	thirdPartyNoticesPanel = new wxPanel( aboutContentTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* thirdPartyNoticesSizer;
	thirdPartyNoticesSizer = new wxBoxSizer( wxVERTICAL );

	m_thirdPartyNoticesText = new wxTextCtrl( thirdPartyNoticesPanel, wxID_ANY, wxT("{open_source_licenses}"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxBORDER_STATIC );
	m_thirdPartyNoticesText->SetFont( wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );

	thirdPartyNoticesSizer->Add( m_thirdPartyNoticesText, 1, wxALL|wxEXPAND, 5 );


	thirdPartyNoticesPanel->SetSizer( thirdPartyNoticesSizer );
	thirdPartyNoticesPanel->Layout();
	thirdPartyNoticesSizer->Fit( thirdPartyNoticesPanel );
	aboutContentTabs->AddPage( thirdPartyNoticesPanel, wxT("3자 라이선스 고지"), false );

	mainBSizer->Add( aboutContentTabs, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( mainBSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

AboutDialogBase::~AboutDialogBase()
{
}

ProgressDialogBase::ProgressDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

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
	mainSizer->Add( contentsPanel, 1, wxEXPAND, 5 );

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
	mainSizer->Add( buttonsPanel, 0, wxALL|wxEXPAND, 10 );


	this->SetSizer( mainSizer );
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

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	wxPanel* topPanel;
	topPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	topPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* listSizer;
	listSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* messageV1;
	messageV1 = new wxStaticText( topPanel, wxID_ANY, wxT("아래 목록과 같이 일부 데이터가 손상되었습니다.\n롬 파일을 계속 열겠습니까?"), wxDefaultPosition, wxDefaultSize, 0 );
	messageV1->Wrap( -1 );
	messageV1->Hide();

	listSizer->Add( messageV1, 0, wxALL|wxEXPAND, 16 );

	wxStaticText* messageV2;
	messageV2 = new wxStaticText( topPanel, wxID_ANY, wxT("아래 목록과 같이 일부 데이터가 손상되었습니다."), wxDefaultPosition, wxDefaultSize, 0 );
	messageV2->Wrap( -1 );
	listSizer->Add( messageV2, 0, wxALL|wxEXPAND, 16 );

	m_badDataList = new ui::ColoredListCtrl( topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxBORDER_STATIC );
	listSizer->Add( m_badDataList, 1, wxALL|wxEXPAND, 5 );


	topPanel->SetSizer( listSizer );
	topPanel->Layout();
	listSizer->Fit( topPanel );
	mainSizer->Add( topPanel, 1, wxEXPAND | wxALL, 0 );

	wxPanel* bottomPanel;
	bottomPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButon;
	confirmButon = new wxButton( bottomPanel, wxID_ANY, wxT("확인"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	buttonSizer->Add( confirmButon, 0, wxRIGHT, 5 );

	wxButton* yesButton;
	yesButton = new wxButton( bottomPanel, wxID_ANY, wxT("예(&Y)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	yesButton->Hide();

	buttonSizer->Add( yesButton, 0, wxRIGHT, 5 );

	wxButton* noButton;
	noButton = new wxButton( bottomPanel, wxID_ANY, wxT("아니요(&N)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	noButton->Hide();

	buttonSizer->Add( noButton, 0, wxRIGHT, 5 );


	bottomPanel->SetSizer( buttonSizer );
	bottomPanel->Layout();
	buttonSizer->Fit( bottomPanel );
	mainSizer->Add( bottomPanel, 0, wxALIGN_RIGHT|wxALL, 10 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_SHOW, wxShowEventHandler( BadDataDialogBase::OnDialogShow ) );
	confirmButon->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnConfirmButtonClick ), NULL, this );
	yesButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnYesButtonClick ), NULL, this );
	noButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnNoButtonClick ), NULL, this );
}

BadDataDialogBase::~BadDataDialogBase()
{
}

EvolutionEditorDialogBase::EvolutionEditorDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

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

	m_happinessTypeComboBox = new wxComboBox( m_levelUpPanel, wxID_ANY, wxT("시간과 상관없이 레벨 업"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_happinessTypeComboBox->Append( wxT("시간과 상관없이 레벨 업") );
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
	mainSizer->Add( contentPanel, 1, wxEXPAND | wxALL, 8 );

	wxPanel* buttonsPanel;
	buttonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* confirmButton;
	confirmButton = new wxButton( buttonsPanel, wxID_ANY, wxT("확인"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( confirmButton, 0, wxALL, 5 );

	wxButton* cancelButton;
	cancelButton = new wxButton( buttonsPanel, wxID_ANY, wxT("취소"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( cancelButton, 0, wxALL, 5 );


	buttonsPanel->SetSizer( buttonsSizer );
	buttonsPanel->Layout();
	buttonsSizer->Fit( buttonsPanel );
	mainSizer->Add( buttonsPanel, 0, wxALIGN_RIGHT|wxALL, 8 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	confirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EvolutionEditorDialogBase::OnConfirmButtonClick ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EvolutionEditorDialogBase::OnCancelButtonClick ), NULL, this );
}

EvolutionEditorDialogBase::~EvolutionEditorDialogBase()
{
}

DatabasePanelBase::DatabasePanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

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

	m_pokemonContainer = new wxScrolledWindow( pokemonInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxVSCROLL );
	m_pokemonContainer->SetScrollRate( 5, 16 );
	m_pokemonContainer->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* pokemonPanelContentSizer;
	pokemonPanelContentSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* pokemonStatsLabelSizer;
	pokemonStatsLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonStatsLabel;
	pokemonStatsLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("기본 정보 && 능력치"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsLabel->Wrap( -1 );
	pokemonStatsLabelSizer->Add( pokemonStatsLabel, 0, wxALL, 5 );

	wxStaticLine* pokemonStatsLabelLine;
	pokemonStatsLabelLine = new wxStaticLine( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	pokemonStatsLabelSizer->Add( pokemonStatsLabelLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonStatsLabelSizer, 0, wxEXPAND, 5 );

	wxBoxSizer* pokemonStatsSizer;
	pokemonStatsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxFlexGridSizer* pokemonInfoGrid;
	pokemonInfoGrid = new wxFlexGridSizer( 7, 2, 0, 0 );
	pokemonInfoGrid->AddGrowableCol( 0 );
	pokemonInfoGrid->SetFlexibleDirection( wxBOTH );
	pokemonInfoGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonNoLabel;
	pokemonNoLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("번호："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonNoLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonNoLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonNoText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxT("-"), wxDefaultPosition, wxSize( 240,-1 ), wxTE_READONLY );
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
	pokemonNameLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("이름："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonNameLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonNameText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0 );
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
	pokemonGenderRateLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("성비율："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonGenderRateLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonGenderRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonGenderRateComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0, NULL, wxCB_READONLY );
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
	pokemonGrowthRateLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("성장률："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonGrowthRateLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonGrowthRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonGrowthRateComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), 0, NULL, wxCB_READONLY );
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
	pokemonTypeLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("타입："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTypeLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonTypeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxPanel* pokemonTypePanel;
	pokemonTypePanel = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 240,-1 ), wxTAB_TRAVERSAL );
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
	pokemonItemsLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("지닌물건："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonItemsLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonItemsLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxPanel* pokemonItemsPanel;
	pokemonItemsPanel = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 240,-1 ), wxTAB_TRAVERSAL );
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
	pokemonEggGroupLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("알 그룹："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggGroupLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonEggGroupLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxPanel* pokemonEggGroupPanel;
	pokemonEggGroupPanel = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 240,-1 ), wxTAB_TRAVERSAL );
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
	pokemonStatsHpLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("HP："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsHpLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsHpLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsHpValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsHpValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsHpValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsAtkLabel;
	pokemonStatsAtkLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("공격："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsAtkLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsAtkLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsAtkValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsAtkValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsAtkValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsDefLabel;
	pokemonStatsDefLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("방어："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsDefLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsDefLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsDefValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsDefValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsDefValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpAtkLabel;
	pokemonStatsSpAtkLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("특수공격："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpAtkLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpAtkLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpAtkValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpAtkValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpAtkValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpDefHpLabel;
	pokemonStatsSpDefHpLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("특수방어："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpDefHpLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpDefHpLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpDefValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpDefValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpDefValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpdLabel;
	pokemonStatsSpdLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("스피드："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpdLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpdLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpdValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpdValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpdValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsExpLabel;
	pokemonStatsExpLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("경험치："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsExpLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsExpLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsExpValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsExpValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsExpValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsCatchRateLabel;
	pokemonStatsCatchRateLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("포획률："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsCatchRateLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsCatchRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsCatchRateValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsCatchRateValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsCatchRateValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	m_pokemonCatchRatePercentage = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("{percentage}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonCatchRatePercentage->Wrap( -1 );
	pokemonStatsGrid->Add( m_pokemonCatchRatePercentage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonStatsSizer->Add( pokemonStatsGrid, 0, 0, 5 );


	pokemonPanelContentSizer->Add( pokemonStatsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonPanelContentSizer->Add( 0, 8, 0, 0, 0 );

	wxBoxSizer* pokemonImageLabelSizer;
	pokemonImageLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonImageLabel;
	pokemonImageLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("이미지 && 색상"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonImageLabel->Wrap( -1 );
	pokemonImageLabelSizer->Add( pokemonImageLabel, 0, wxALL, 5 );

	wxStaticLine* pokemonImageLabelLine;
	pokemonImageLabelLine = new wxStaticLine( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	pokemonImageLabelSizer->Add( pokemonImageLabelLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonImageLabelSizer, 0, wxEXPAND, 5 );


	pokemonPanelContentSizer->Add( 0, 8, 0, 0, 0 );

	wxBoxSizer* pokemonDexLabelSizer;
	pokemonDexLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonDexLabel;
	pokemonDexLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("도감"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexLabel->Wrap( -1 );
	pokemonDexLabelSizer->Add( pokemonDexLabel, 0, wxALL, 5 );

	wxStaticLine* pokemonDexLabelLine;
	pokemonDexLabelLine = new wxStaticLine( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	pokemonDexLabelSizer->Add( pokemonDexLabelLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonDexLabelSizer, 0, wxEXPAND, 5 );

	wxBoxSizer* pokemonDexSizer;
	pokemonDexSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* pokemonDexInfoGrid;
	pokemonDexInfoGrid = new wxFlexGridSizer( 3, 2, 0, 0 );
	pokemonDexInfoGrid->AddGrowableCol( 1 );
	pokemonDexInfoGrid->SetFlexibleDirection( wxBOTH );
	pokemonDexInfoGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonDexSpeciesNameLabel;
	pokemonDexSpeciesNameLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("분류명："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexSpeciesNameLabel->Wrap( -1 );
	pokemonDexInfoGrid->Add( pokemonDexSpeciesNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonDexSpeciesNameText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
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
	pokemonDexHeightLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("키："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexHeightLabel->Wrap( -1 );
	pokemonDexInfoGrid->Add( pokemonDexHeightLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonDexHeightValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 25.5, 0, 0.1 );
	m_pokemonDexHeightValue->SetDigits( 1 );
	pokemonDexInfoGrid->Add( m_pokemonDexHeightValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonDexWeightLabel;
	pokemonDexWeightLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("몸무게："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonDexWeightLabel->Wrap( -1 );
	pokemonDexInfoGrid->Add( pokemonDexWeightLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonDexWeightValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999.9, 0, 0.1 );
	m_pokemonDexWeightValue->SetDigits( 1 );
	pokemonDexInfoGrid->Add( m_pokemonDexWeightValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonDexSizer->Add( pokemonDexInfoGrid, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );

	m_pokemonDexDescriptionLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("{description_label}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonDexDescriptionLabel->Wrap( -1 );
	pokemonDexSizer->Add( m_pokemonDexDescriptionLabel, 0, wxALL, 5 );

	m_pokemonDexDescriptionText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,72 ), wxTE_MULTILINE|wxTE_NO_VSCROLL|wxBORDER_SIMPLE );
	m_pokemonDexDescriptionText->SetFont( wxFont( 14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_pokemonDexDescriptionText->SetMinSize( wxSize( 320,72 ) );
	m_pokemonDexDescriptionText->SetMaxSize( wxSize( 320,72 ) );

	pokemonDexSizer->Add( m_pokemonDexDescriptionText, 0, wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonDexSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonPanelContentSizer->Add( 0, 8, 0, 0, 0 );

	wxBoxSizer* pokemonEvoLearnsLabelSizer;
	pokemonEvoLearnsLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonEvoLearnsLabel;
	pokemonEvoLearnsLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("진화 && 자력기"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvoLearnsLabel->Wrap( -1 );
	pokemonEvoLearnsLabelSizer->Add( pokemonEvoLearnsLabel, 0, wxALL, 5 );

	wxStaticLine* pokemonEvoLearnsLabelLine;
	pokemonEvoLearnsLabelLine = new wxStaticLine( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	pokemonEvoLearnsLabelSizer->Add( pokemonEvoLearnsLabelLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonEvoLearnsLabelSizer, 0, wxEXPAND, 5 );


	pokemonPanelContentSizer->Add( 0, 8, 0, 0, 0 );

	wxPanel* pokemonEvolutionsPanel;
	pokemonEvolutionsPanel = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonEvolutionsSizer;
	pokemonEvolutionsSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonEvolutionsLabel;
	pokemonEvolutionsLabel = new wxStaticText( pokemonEvolutionsPanel, wxID_ANY, wxT("진화"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvolutionsLabel->Wrap( -1 );
	pokemonEvolutionsSizer->Add( pokemonEvolutionsLabel, 0, wxLEFT|wxTOP, 8 );

	m_pokemonEvolutionsList = new ui::ColoredListCtrl( pokemonEvolutionsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxBORDER_SIMPLE );
	m_pokemonEvolutionsList->SetMinSize( wxSize( 512,125 ) );

	pokemonEvolutionsSizer->Add( m_pokemonEvolutionsList, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 8 );

	wxBoxSizer* pokemonEvolutionsButtonsSizer;
	pokemonEvolutionsButtonsSizer = new wxBoxSizer( wxHORIZONTAL );


	pokemonEvolutionsButtonsSizer->Add( 0, 0, 1, 0, 0 );

	m_pokemonEvolutionAdd = new wxButton( pokemonEvolutionsPanel, wxID_POKEMON_EVOLUTION_ADD, wxT("추가..."), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionAdd, 0, wxALL, 2 );

	m_pokemonEvolutionModify = new wxButton( pokemonEvolutionsPanel, wxID_POKEMON_EVOLUTION_MODIFY, wxT("수정..."), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionModify, 0, wxALL, 2 );

	m_pokemonEvolutionRemove = new wxButton( pokemonEvolutionsPanel, wxID_POKEMON_EVOLUTION_REMOVE, wxT("삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionRemove, 0, wxALL, 2 );

	m_pokemonEvolutionClear = new wxButton( pokemonEvolutionsPanel, wxID_POKEMON_EVOLUTION_CLEAR, wxT("전체 삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonEvolutionClear->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_pokemonEvolutionClear->SetForegroundColour( wxColour( 255, 0, 0 ) );

	pokemonEvolutionsButtonsSizer->Add( m_pokemonEvolutionClear, 0, wxALL, 2 );


	pokemonEvolutionsSizer->Add( pokemonEvolutionsButtonsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonEvolutionsPanel->SetSizer( pokemonEvolutionsSizer );
	pokemonEvolutionsPanel->Layout();
	pokemonEvolutionsSizer->Fit( pokemonEvolutionsPanel );
	pokemonPanelContentSizer->Add( pokemonEvolutionsPanel, 0, 0, 0 );

	wxPanel* pokemonLearnMovesPanel;
	pokemonLearnMovesPanel = new wxPanel( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonLearnMovesSizer;
	pokemonLearnMovesSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticText* pokemonLearnMovesLabel;
	pokemonLearnMovesLabel = new wxStaticText( pokemonLearnMovesPanel, wxID_ANY, wxT("자력기"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonLearnMovesLabel->Wrap( -1 );
	pokemonLearnMovesSizer->Add( pokemonLearnMovesLabel, 0, wxLEFT|wxTOP, 8 );

	m_pokemonLearnMovesList = new ui::ColoredListCtrl( pokemonLearnMovesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxBORDER_SIMPLE );
	m_pokemonLearnMovesList->SetMinSize( wxSize( 512,180 ) );

	pokemonLearnMovesSizer->Add( m_pokemonLearnMovesList, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 8 );

	wxBoxSizer* pokemonLearnMovesButtonsSizer;
	pokemonLearnMovesButtonsSizer = new wxBoxSizer( wxHORIZONTAL );


	pokemonLearnMovesButtonsSizer->Add( 0, 0, 1, 0, 0 );

	m_pokemonLearnMovesImport = new wxButton( pokemonLearnMovesPanel, wxID_POKEMON_LEARN_MOVES_IMPORT, wxT("가져오기..."), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonLearnMovesButtonsSizer->Add( m_pokemonLearnMovesImport, 0, wxALL, 2 );

	m_pokemonLearnMovesAdd = new wxButton( pokemonLearnMovesPanel, wxID_POKEMON_LEARN_MOVES_ADD, wxT("추가..."), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonLearnMovesButtonsSizer->Add( m_pokemonLearnMovesAdd, 0, wxALL, 2 );

	m_pokemonLearnMovesModify = new wxButton( pokemonLearnMovesPanel, wxID_POKEMON_LEARN_MOVES_MODIFY, wxT("수정..."), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonLearnMovesButtonsSizer->Add( m_pokemonLearnMovesModify, 0, wxALL, 2 );

	m_pokemonLearnMovesRemove = new wxButton( pokemonLearnMovesPanel, wxID_POKEMON_LEARN_MOVES_REMOVE, wxT("삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonLearnMovesButtonsSizer->Add( m_pokemonLearnMovesRemove, 0, wxALL, 2 );

	m_pokemonLearnMovesClear = new wxButton( pokemonLearnMovesPanel, wxID_POKEMON_LEARN_MOVES_CLEAR, wxT("전체 삭제"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonLearnMovesClear->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_pokemonLearnMovesClear->SetForegroundColour( wxColour( 255, 0, 0 ) );

	pokemonLearnMovesButtonsSizer->Add( m_pokemonLearnMovesClear, 0, wxALL, 2 );


	pokemonLearnMovesSizer->Add( pokemonLearnMovesButtonsSizer, 0, wxALL|wxEXPAND, 5 );


	pokemonLearnMovesPanel->SetSizer( pokemonLearnMovesSizer );
	pokemonLearnMovesPanel->Layout();
	pokemonLearnMovesSizer->Fit( pokemonLearnMovesPanel );
	pokemonPanelContentSizer->Add( pokemonLearnMovesPanel, 0, 0, 0 );


	pokemonPanelContentSizer->Add( 0, 8, 0, 0, 0 );

	wxBoxSizer* pokemonTMHMsLabelSizer;
	pokemonTMHMsLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonTMHMsLabel;
	pokemonTMHMsLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("기술머신 && 비전머신"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTMHMsLabel->Wrap( -1 );
	pokemonTMHMsLabelSizer->Add( pokemonTMHMsLabel, 0, wxALL, 5 );

	wxStaticLine* pokemonTMHMsLabelLine;
	pokemonTMHMsLabelLine = new wxStaticLine( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	pokemonTMHMsLabelSizer->Add( pokemonTMHMsLabelLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonTMHMsLabelSizer, 0, wxEXPAND, 5 );

	wxBoxSizer* pokemonTMHMsButtonsSizer;
	pokemonTMHMsButtonsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxButton* pokemonTMHMsCheckAllButton;
	pokemonTMHMsCheckAllButton = new wxButton( m_pokemonContainer, wxID_POKEMON_TMHMS_CHECK_ALL, wxT("모두 선택"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTMHMsButtonsSizer->Add( pokemonTMHMsCheckAllButton, 0, wxALL, 2 );

	wxButton* pokemonTMHMsClearButton;
	pokemonTMHMsClearButton = new wxButton( m_pokemonContainer, wxID_POKEMON_TMHMS_CLEAR, wxT("모두 해제"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTMHMsButtonsSizer->Add( pokemonTMHMsClearButton, 0, wxALL, 2 );


	pokemonPanelContentSizer->Add( pokemonTMHMsButtonsSizer, 0, wxALL, 4 );

	m_pokemonTMHMsSizer = new wxGridSizer( 3, 3, 0, 0 );

	wxString m_pokemonHmTmList1Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList1NChoices = sizeof( m_pokemonHmTmList1Choices ) / sizeof( wxString );
	m_pokemonHmTmList1 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList1NChoices, m_pokemonHmTmList1Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList1->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList1, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList2Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList2NChoices = sizeof( m_pokemonHmTmList2Choices ) / sizeof( wxString );
	m_pokemonHmTmList2 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList2NChoices, m_pokemonHmTmList2Choices, wxLB_NO_SB );
	m_pokemonHmTmList2->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList2, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList3Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList3NChoices = sizeof( m_pokemonHmTmList3Choices ) / sizeof( wxString );
	m_pokemonHmTmList3 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList3NChoices, m_pokemonHmTmList3Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList3->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList3, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList4Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList4NChoices = sizeof( m_pokemonHmTmList4Choices ) / sizeof( wxString );
	m_pokemonHmTmList4 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList4NChoices, m_pokemonHmTmList4Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList4->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList4, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList5Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList5NChoices = sizeof( m_pokemonHmTmList5Choices ) / sizeof( wxString );
	m_pokemonHmTmList5 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList5NChoices, m_pokemonHmTmList5Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList5->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList5, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList6Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList6NChoices = sizeof( m_pokemonHmTmList6Choices ) / sizeof( wxString );
	m_pokemonHmTmList6 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList6NChoices, m_pokemonHmTmList6Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList6->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList6, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList7Choices[] = { wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString };
	int m_pokemonHmTmList7NChoices = sizeof( m_pokemonHmTmList7Choices ) / sizeof( wxString );
	m_pokemonHmTmList7 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList7NChoices, m_pokemonHmTmList7Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList7->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList7, 0, wxALL|wxEXPAND, 2 );

	wxString m_pokemonHmTmList8Choices[] = { wxEmptyString };
	int m_pokemonHmTmList8NChoices = sizeof( m_pokemonHmTmList8Choices ) / sizeof( wxString );
	m_pokemonHmTmList8 = new ui::ColoredCheckListBox( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxSize( 160,-1 ), m_pokemonHmTmList8NChoices, m_pokemonHmTmList8Choices, wxLB_NO_SB|wxBORDER_SIMPLE );
	m_pokemonHmTmList8->SetMinSize( wxSize( 160,-1 ) );

	m_pokemonTMHMsSizer->Add( m_pokemonHmTmList8, 0, wxALL|wxEXPAND, 2 );


	pokemonPanelContentSizer->Add( m_pokemonTMHMsSizer, 0, wxALL|wxEXPAND, 4 );


	m_pokemonContainer->SetSizer( pokemonPanelContentSizer );
	m_pokemonContainer->Layout();
	pokemonPanelContentSizer->Fit( m_pokemonContainer );
	pokemonInnerPanelSizer->Add( m_pokemonContainer, 1, wxALL|wxEXPAND, 2 );


	pokemonInnerPanel->SetSizer( pokemonInnerPanelSizer );
	pokemonInnerPanel->Layout();
	pokemonInnerPanelSizer->Fit( pokemonInnerPanel );
	pokemonPanelSizer->Add( pokemonInnerPanel, 1, wxEXPAND | wxALL, 2 );


	pokemonPanel->SetSizer( pokemonPanelSizer );
	pokemonPanel->Layout();
	pokemonPanelSizer->Fit( pokemonPanel );
	mainTabs->AddPage( pokemonPanel, wxT("포켓몬"), true );
	wxPanel* movesPanel;
	movesPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	mainTabs->AddPage( movesPanel, wxT("기술"), false );

	mainSizer->Add( mainTabs, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	// Connect Events
	m_pokemonList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( DatabasePanelBase::OnPokemonSelected ), NULL, this );
	m_pokemonEvolutionAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonEvolutionModify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonEvolutionRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonEvolutionClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonEvolutionsButtonClick ), NULL, this );
	m_pokemonLearnMovesImport->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonLearnMovesButtonClick ), NULL, this );
	m_pokemonLearnMovesAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonLearnMovesButtonClick ), NULL, this );
	m_pokemonLearnMovesModify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonLearnMovesButtonClick ), NULL, this );
	m_pokemonLearnMovesRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonLearnMovesButtonClick ), NULL, this );
	m_pokemonLearnMovesClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonLearnMovesButtonClick ), NULL, this );
	pokemonTMHMsCheckAllButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonTMHMsButtonClick ), NULL, this );
	pokemonTMHMsClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DatabasePanelBase::OnPokemonTMHMsButtonClick ), NULL, this );
}

DatabasePanelBase::~DatabasePanelBase()
{
}
