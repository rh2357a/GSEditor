///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

#include "gui_base.h"

#include "icon_about.png.h"
#include "icon_exit.png.h"
#include "icon_folder.png.h"
#include "icon_play.png.h"
#include "icon_save.png.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 720,560 ), wxDefaultSize );

	wxMenuBar* menuBar;
	menuBar = new wxMenuBar( 0 );
	m_fileMenu = new wxMenu();
	wxMenuItem* fileOpenMenuItem;
	fileOpenMenuItem = new wxMenuItem( m_fileMenu, wxID_OPEN, wxString( wxT("열기(&O)...") ) + wxT('\t') + wxT("Ctrl+O"), wxT("롬 파일을 엽니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	fileOpenMenuItem->SetBitmaps( icon_folder_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	fileOpenMenuItem->SetBitmap( icon_folder_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( fileOpenMenuItem );

	m_fileSaveMenuItem = new wxMenuItem( m_fileMenu, wxID_SAVE, wxString( wxT("저장(&S)") ) + wxT('\t') + wxT("Ctrl+S"), wxT("열린 롬 파일을 저장합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileSaveMenuItem->SetBitmaps( icon_save_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileSaveMenuItem->SetBitmap( icon_save_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( m_fileSaveMenuItem );

	m_fileMenu->AppendSeparator();

	m_fileExportToIpsMenuItem = new wxMenuItem( m_fileMenu, wxID_IPS, wxString( wxT("IPS 패치 생성...") ) , wxT("IPS 형식의 패치 파일을 생성합니다."), wxITEM_NORMAL );
	m_fileMenu->Append( m_fileExportToIpsMenuItem );

	m_fileExportToXdeltaMenuItem = new wxMenuItem( m_fileMenu, wxID_XDELTA, wxString( wxT("xdelta 패치 생성...") ) , wxT("xdelta 형식의 패치 파일을 생성합니다."), wxITEM_NORMAL );
	m_fileMenu->Append( m_fileExportToXdeltaMenuItem );

	m_fileMenu->AppendSeparator();

	wxMenuItem* fileExitMenuItem;
	fileExitMenuItem = new wxMenuItem( m_fileMenu, wxID_EXIT, wxString( wxT("닫기(&X)") ) + wxT('\t') + wxT("Alt+F4"), wxT("프로그램을 종료합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	fileExitMenuItem->SetBitmaps( icon_exit_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	fileExitMenuItem->SetBitmap( icon_exit_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( fileExitMenuItem );

	menuBar->Append( m_fileMenu, wxT("파일(&F)") );

	m_gameMenu = new wxMenu();
	m_gameTestPlayMenuItem = new wxMenuItem( m_gameMenu, wxID_TEST_PLAY, wxString( wxT("테스트 플레이(&P)") ) + wxT('\t') + wxT("F5"), wxT("롬을 빌드하여 테스트합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_gameTestPlayMenuItem->SetBitmaps( icon_play_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_gameTestPlayMenuItem->SetBitmap( icon_play_png_to_wx_bitmap() );
	#endif
	m_gameMenu->Append( m_gameTestPlayMenuItem );

	m_gameMenu->AppendSeparator();

	m_gameSetEmulatorMenuItem = new wxMenuItem( m_gameMenu, wxID_EMULATOR, wxString( wxT("에뮬레이터 설정(&E)") ) , wxT("테스트를 위해 에뮬레이터를 등록합니다."), wxITEM_NORMAL );
	m_gameMenu->Append( m_gameSetEmulatorMenuItem );

	menuBar->Append( m_gameMenu, wxT("게임(&G)") );

	m_helpMenu = new wxMenu();
	wxMenuItem* helpAboutMenuItem;
	helpAboutMenuItem = new wxMenuItem( m_helpMenu, wxID_ABOUT, wxString( wxT("GS 에디터 정보(&A)...") ) , wxT("프로그램의 정보를 봅니다."), wxITEM_NORMAL );
	m_helpMenu->Append( helpAboutMenuItem );

	menuBar->Append( m_helpMenu, wxT("도움말(&H)") );

	this->SetMenuBar( menuBar );

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

	m_mainPanel = new gui::controls::DatabasePanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	mainSizer->Add( m_mainPanel, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnClose ) );
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, fileOpenMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileSaveMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExportToIpsMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExportToXdeltaMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, fileExitMenuItem->GetId());
	m_gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_gameTestPlayMenuItem->GetId());
	m_gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_gameSetEmulatorMenuItem->GetId());
	m_helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, helpAboutMenuItem->GetId());
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

	wxBoxSizer* appInfoLabelSizer;
	appInfoLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* appInfoLabel;
	appInfoLabel = new wxStaticText( this, wxID_ANY, wxT("버전 기록"), wxDefaultPosition, wxDefaultSize, 0 );
	appInfoLabel->Wrap( -1 );
	appInfoLabelSizer->Add( appInfoLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxStaticLine* appInfoLine;
	appInfoLine = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	appInfoLabelSizer->Add( appInfoLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	mainBSizer->Add( appInfoLabelSizer, 0, wxEXPAND, 5 );

	m_versionHtml = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxBORDER_THEME );
	mainBSizer->Add( m_versionHtml, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( mainBSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

AboutDialogBase::~AboutDialogBase()
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

	m_badDataList = new wxListCtrl( topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxBORDER_STATIC );
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
	buttonSizer->Add( confirmButon, 0, wxALL, 5 );

	wxButton* yesButton;
	yesButton = new wxButton( bottomPanel, wxID_ANY, wxT("예(&Y)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	yesButton->Hide();

	buttonSizer->Add( yesButton, 0, wxALL, 5 );

	wxButton* noButton;
	noButton = new wxButton( bottomPanel, wxID_ANY, wxT("아니요(&N)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	noButton->Hide();

	buttonSizer->Add( noButton, 0, wxALL, 5 );


	bottomPanel->SetSizer( buttonSizer );
	bottomPanel->Layout();
	buttonSizer->Fit( bottomPanel );
	mainSizer->Add( bottomPanel, 0, wxALIGN_RIGHT|wxALL, 8 );


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

	m_pokemonList = new wxListBox( pokemonInnerPanel, wxID_ANY, wxDefaultPosition, wxSize( 144,-1 ), 0, NULL, wxLB_SINGLE|wxBORDER_STATIC );
	pokemonInnerPanelSizer->Add( m_pokemonList, 0, wxALL|wxEXPAND, 2 );

	m_pokemonContainer = new wxScrolledWindow( pokemonInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC|wxVSCROLL );
	m_pokemonContainer->SetScrollRate( 5, 5 );
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
	pokemonInfoGrid->AddGrowableCol( 1 );
	pokemonInfoGrid->SetFlexibleDirection( wxBOTH );
	pokemonInfoGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText* pokemonNoLabel;
	pokemonNoLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("번호："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonNoLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonNoLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonNoText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	#ifdef __WXGTK__
	if ( !m_pokemonNoText->HasFlag( wxTE_MULTILINE ) )
	{
	m_pokemonNoText->SetMaxLength( 5 );
	}
	#else
	m_pokemonNoText->SetMaxLength( 5 );
	#endif
	pokemonInfoGrid->Add( m_pokemonNoText, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonNameLabel;
	pokemonNameLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("이름："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonNameLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonNameLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonNameText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_pokemonNameText->HasFlag( wxTE_MULTILINE ) )
	{
	m_pokemonNameText->SetMaxLength( 5 );
	}
	#else
	m_pokemonNameText->SetMaxLength( 5 );
	#endif
	pokemonInfoGrid->Add( m_pokemonNameText, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonGenderRateLabel;
	pokemonGenderRateLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("성비율："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonGenderRateLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonGenderRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonGenderRateComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
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

	pokemonInfoGrid->Add( m_pokemonGenderRateComboBox, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonGrowthRateLabel;
	pokemonGrowthRateLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("성장률："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonGrowthRateLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonGrowthRateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonGrowthRateComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_pokemonGrowthRateComboBox->Append( wxT("중간 빠름 (125 ~ 1,000,000)") );
	m_pokemonGrowthRateComboBox->Append( wxT("약간 빠름 (313 ~ 849,970)") );
	m_pokemonGrowthRateComboBox->Append( wxT("약간 느림 (523 ~ 949,930)") );
	m_pokemonGrowthRateComboBox->Append( wxT("중간 느림 (135 ~ 1,059,860)") );
	m_pokemonGrowthRateComboBox->Append( wxT("빠름 (100 ~ 800,000)") );
	m_pokemonGrowthRateComboBox->Append( wxT("느림 (156 ~ 1,250,000)") );
	m_pokemonGrowthRateComboBox->SetFont( wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );

	pokemonInfoGrid->Add( m_pokemonGrowthRateComboBox, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );

	wxStaticText* pokemonTypeLabel;
	pokemonTypeLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("타입："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonTypeLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonTypeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* pokemonTypeSizer;
	pokemonTypeSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonType1ComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	pokemonTypeSizer->Add( m_pokemonType1ComboBox, 1, wxALL, 2 );

	m_pokemonType2ComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	pokemonTypeSizer->Add( m_pokemonType2ComboBox, 1, wxALL, 2 );


	pokemonInfoGrid->Add( pokemonTypeSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 2 );

	wxStaticText* pokemonItemsLabel;
	pokemonItemsLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("지닌물건："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonItemsLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonItemsLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* pokemonItemsSizer;
	pokemonItemsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonItem1ComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	pokemonItemsSizer->Add( m_pokemonItem1ComboBox, 1, wxALL, 2 );

	m_pokemonItem2ComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	pokemonItemsSizer->Add( m_pokemonItem2ComboBox, 1, wxALL, 2 );


	pokemonInfoGrid->Add( pokemonItemsSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 2 );

	wxStaticText* pokemonEggGroupLabel;
	pokemonEggGroupLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("알 그룹："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonEggGroupLabel->Wrap( -1 );
	pokemonInfoGrid->Add( pokemonEggGroupLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* pokemonEggGroupSizer;
	pokemonEggGroupSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonEggGroup1ComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
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
	pokemonEggGroupSizer->Add( m_pokemonEggGroup1ComboBox, 1, wxALL, 2 );

	m_pokemonEggGroup2ComboBox = new wxComboBox( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
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
	pokemonEggGroupSizer->Add( m_pokemonEggGroup2ComboBox, 1, wxALL, 2 );


	pokemonInfoGrid->Add( pokemonEggGroupSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 2 );


	pokemonStatsSizer->Add( pokemonInfoGrid, 0, wxEXPAND, 5 );


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
	pokemonStatsSpAtkLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("특수 공격："), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonStatsSpAtkLabel->Wrap( -1 );
	pokemonStatsGrid->Add( pokemonStatsSpAtkLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_pokemonStatsSpAtkValue = new wxSpinCtrlDouble( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0, 1 );
	m_pokemonStatsSpAtkValue->SetDigits( 0 );
	pokemonStatsGrid->Add( m_pokemonStatsSpAtkValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 4 );


	pokemonStatsGrid->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* pokemonStatsSpDefHpLabel;
	pokemonStatsSpDefHpLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("특수 방어："), wxDefaultPosition, wxDefaultSize, 0 );
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

	wxBoxSizer* pokemonImageLabelSizer;
	pokemonImageLabelSizer = new wxBoxSizer( wxHORIZONTAL );

	wxStaticText* pokemonImageLabel;
	pokemonImageLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("이미지"), wxDefaultPosition, wxDefaultSize, 0 );
	pokemonImageLabel->Wrap( -1 );
	pokemonImageLabelSizer->Add( pokemonImageLabel, 0, wxALL, 5 );

	wxStaticLine* pokemonImageLabelLine;
	pokemonImageLabelLine = new wxStaticLine( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	pokemonImageLabelSizer->Add( pokemonImageLabelLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pokemonPanelContentSizer->Add( pokemonImageLabelSizer, 0, wxEXPAND, 5 );

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


	pokemonDexSizer->Add( pokemonDexInfoGrid, 0, wxALL, 5 );

	m_pokemonDexDescriptionLabel = new wxStaticText( m_pokemonContainer, wxID_ANY, wxT("{description_label}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonDexDescriptionLabel->Wrap( -1 );
	pokemonDexSizer->Add( m_pokemonDexDescriptionLabel, 0, wxALL, 5 );

	m_pokemonDexDescriptionText = new wxTextCtrl( m_pokemonContainer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,72 ), wxTE_MULTILINE|wxTE_NO_VSCROLL );
	m_pokemonDexDescriptionText->SetFont( wxFont( 14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );
	m_pokemonDexDescriptionText->SetMinSize( wxSize( -1,72 ) );
	m_pokemonDexDescriptionText->SetMaxSize( wxSize( -1,72 ) );

	pokemonDexSizer->Add( m_pokemonDexDescriptionText, 0, wxALL|wxEXPAND, 5 );


	pokemonPanelContentSizer->Add( pokemonDexSizer, 0, wxALL|wxEXPAND, 5 );

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

	m_pokemonEvolutionsList = new wxListCtrl( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	m_pokemonEvolutionsList->SetMinSize( wxSize( -1,128 ) );

	pokemonPanelContentSizer->Add( m_pokemonEvolutionsList, 0, wxALL|wxEXPAND, 8 );

	m_pokemonLearnMovesList = new wxListCtrl( m_pokemonContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	m_pokemonLearnMovesList->SetMinSize( wxSize( -1,160 ) );

	pokemonPanelContentSizer->Add( m_pokemonLearnMovesList, 0, wxALL|wxEXPAND, 8 );

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


	m_pokemonContainer->SetSizer( pokemonPanelContentSizer );
	m_pokemonContainer->Layout();
	pokemonPanelContentSizer->Fit( m_pokemonContainer );
	pokemonInnerPanelSizer->Add( m_pokemonContainer, 1, wxEXPAND | wxALL, 2 );


	pokemonInnerPanel->SetSizer( pokemonInnerPanelSizer );
	pokemonInnerPanel->Layout();
	pokemonInnerPanelSizer->Fit( pokemonInnerPanel );
	pokemonPanelSizer->Add( pokemonInnerPanel, 1, wxEXPAND | wxALL, 2 );


	pokemonPanel->SetSizer( pokemonPanelSizer );
	pokemonPanel->Layout();
	pokemonPanelSizer->Fit( pokemonPanel );
	mainTabs->AddPage( pokemonPanel, wxT("포켓몬"), false );
	wxPanel* movesPanel;
	movesPanel = new wxPanel( mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	mainTabs->AddPage( movesPanel, wxT("기술"), false );

	mainSizer->Add( mainTabs, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	// Connect Events
	m_pokemonList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( DatabasePanelBase::OnPokemonSelected ), NULL, this );
}

DatabasePanelBase::~DatabasePanelBase()
{
}
