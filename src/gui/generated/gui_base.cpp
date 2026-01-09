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
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menuBar = new wxMenuBar( 0 );
	m_fileMenu = new wxMenu();
	wxMenuItem* m_fileOpenMenuItem;
	m_fileOpenMenuItem = new wxMenuItem( m_fileMenu, wxID_OPEN, wxString( wxT("열기(&O)...") ) + wxT('\t') + wxT("Ctrl+O"), wxT("롬 파일을 엽니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileOpenMenuItem->SetBitmaps( icon_folder_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileOpenMenuItem->SetBitmap( icon_folder_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( m_fileOpenMenuItem );

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

	wxMenuItem* m_fileExitMenuItem;
	m_fileExitMenuItem = new wxMenuItem( m_fileMenu, wxID_EXIT, wxString( wxT("닫기(&X)") ) + wxT('\t') + wxT("Alt+F4"), wxT("프로그램을 종료합니다."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileExitMenuItem->SetBitmaps( icon_exit_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileExitMenuItem->SetBitmap( icon_exit_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( m_fileExitMenuItem );

	m_menuBar->Append( m_fileMenu, wxT("파일(&F)") );

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

	m_menuBar->Append( m_gameMenu, wxT("게임(&G)") );

	m_helpMenu = new wxMenu();
	wxMenuItem* m_helpAboutMenuItem;
	m_helpAboutMenuItem = new wxMenuItem( m_helpMenu, wxID_ABOUT, wxString( wxT("GS 에디터 정보(&A)...") ) , wxT("프로그램의 정보를 봅니다."), wxITEM_NORMAL );
	m_helpMenu->Append( m_helpAboutMenuItem );

	m_menuBar->Append( m_helpMenu, wxT("도움말(&H)") );

	this->SetMenuBar( m_menuBar );

	m_toolBar = this->CreateToolBar( wxTB_DEFAULT_STYLE|wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY );
	m_toolBar->SetToolSeparation( 25 );
	m_openToolbarItem = m_toolBar->AddTool( wxID_OPEN, wxT("open"), icon_folder_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("롬 파일을 엽니다."), NULL );

	m_saveToolbarItem = m_toolBar->AddTool( wxID_SAVE, wxT("save"), icon_save_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("열린 롬 파일을 저장합니다."), NULL );

	m_toolBar->AddSeparator();

	m_testPlayToolbarItem = m_toolBar->AddTool( wxID_TEST_PLAY, wxT("save"), icon_play_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("롬을 빌드하여 테스트합니다."), NULL );

	m_toolBar->AddSeparator();

	m_exitToolbarItem = m_toolBar->AddTool( wxID_EXIT, wxT("exit"), icon_exit_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("프로그램을 종료합니다."), NULL );

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
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileOpenMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileSaveMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExportToIpsMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExportToXdeltaMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExitMenuItem->GetId());
	m_gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_gameTestPlayMenuItem->GetId());
	m_gameMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_gameSetEmulatorMenuItem->GetId());
	m_helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_helpAboutMenuItem->GetId());
	this->Connect( m_openToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_saveToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_testPlayToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
	this->Connect( m_exitToolbarItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ));
}

MainFrameBase::~MainFrameBase()
{
}

AboutDialogBase::AboutDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainBSizer;
	mainBSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* appInfoBSizer;
	appInfoBSizer = new wxBoxSizer( wxHORIZONTAL );

	m_appIconBitmap = new wxStaticBitmap( this, wxID_ANY, icon_about_png_to_wx_bitmap(), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	appInfoBSizer->Add( m_appIconBitmap, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* appInfoBSizer2;
	appInfoBSizer2 = new wxBoxSizer( wxVERTICAL );

	m_authorText = new wxStaticText( this, wxID_ANY, wxT("{author}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_authorText->Wrap( -1 );
	appInfoBSizer2->Add( m_authorText, 0, wxALL|wxEXPAND, 5 );

	m_versionText = new wxStaticText( this, wxID_ANY, wxT("{version}"), wxDefaultPosition, wxDefaultSize, 0 );
	m_versionText->Wrap( -1 );
	appInfoBSizer2->Add( m_versionText, 0, wxALL|wxEXPAND, 5 );


	appInfoBSizer->Add( appInfoBSizer2, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	mainBSizer->Add( appInfoBSizer, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* separatorBSizer;
	separatorBSizer = new wxBoxSizer( wxHORIZONTAL );

	m_separatorText = new wxStaticText( this, wxID_ANY, wxT("버전 기록"), wxDefaultPosition, wxDefaultSize, 0 );
	m_separatorText->Wrap( -1 );
	separatorBSizer->Add( m_separatorText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_appInfoLine = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	separatorBSizer->Add( m_appInfoLine, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	mainBSizer->Add( separatorBSizer, 0, wxEXPAND, 5 );

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

	m_TopPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_TopPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* listSizer;
	listSizer = new wxBoxSizer( wxVERTICAL );

	m_messageLabel = new wxStaticText( m_TopPanel, wxID_ANY, wxT("아래 목록과 같이 일부 데이터가 손상되었습니다.\n롬 파일을 계속 열겠습니까?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_messageLabel->Wrap( -1 );
	listSizer->Add( m_messageLabel, 0, wxALL|wxEXPAND, 16 );

	m_badDataList = new wxListCtrl( m_TopPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	listSizer->Add( m_badDataList, 1, wxALL|wxEXPAND, 5 );


	m_TopPanel->SetSizer( listSizer );
	m_TopPanel->Layout();
	listSizer->Fit( m_TopPanel );
	mainSizer->Add( m_TopPanel, 1, wxEXPAND | wxALL, 0 );

	m_bottomPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );

	m_YesButton = new wxButton( m_bottomPanel, wxID_ANY, wxT("예(&Y)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	buttonSizer->Add( m_YesButton, 0, wxALL, 5 );

	m_NoButton = new wxButton( m_bottomPanel, wxID_ANY, wxT("아니요(&N)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	buttonSizer->Add( m_NoButton, 0, wxALL, 5 );


	m_bottomPanel->SetSizer( buttonSizer );
	m_bottomPanel->Layout();
	buttonSizer->Fit( m_bottomPanel );
	mainSizer->Add( m_bottomPanel, 0, wxALIGN_RIGHT|wxALL, 8 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_SHOW, wxShowEventHandler( BadDataDialogBase::OnDialogShow ) );
	m_YesButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnYesButtonClick ), NULL, this );
	m_NoButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnNoButtonClick ), NULL, this );
}

BadDataDialogBase::~BadDataDialogBase()
{
}

DatabasePanelBase::DatabasePanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	m_mainTabs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pokemonPanel = new wxPanel( m_mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* pokemonSizer;
	pokemonSizer = new wxBoxSizer( wxHORIZONTAL );

	m_pokemonList = new wxListBox( m_pokemonPanel, wxID_ANY, wxDefaultPosition, wxSize( 144,-1 ), 0, NULL, wxLB_SINGLE );
	pokemonSizer->Add( m_pokemonList, 0, wxALL|wxEXPAND, 2 );

	m_pokemonContainer = new wxScrolledWindow( m_pokemonPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxHSCROLL|wxVSCROLL );
	m_pokemonContainer->SetScrollRate( 5, 5 );
	pokemonSizer->Add( m_pokemonContainer, 1, wxEXPAND | wxALL, 2 );


	m_pokemonPanel->SetSizer( pokemonSizer );
	m_pokemonPanel->Layout();
	pokemonSizer->Fit( m_pokemonPanel );
	m_mainTabs->AddPage( m_pokemonPanel, wxT("포켓몬"), false );

	mainSizer->Add( m_mainTabs, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	// Connect Events
	m_pokemonList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( DatabasePanelBase::OnPokemonSelected ), NULL, this );
}

DatabasePanelBase::~DatabasePanelBase()
{
}
