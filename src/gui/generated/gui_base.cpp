///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_base.h"

#include "icon_app.png.h"
#include "icon_exit.png.h"
#include "icon_folder.png.h"
#include "icon_save.png.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menuBar = new wxMenuBar( 0 );
	m_fileMenu = new wxMenu();
	wxMenuItem* m_fileOpenMenuItem;
	m_fileOpenMenuItem = new wxMenuItem( m_fileMenu, wxID_OPEN, wxString( wxT("열기(&O)...") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileOpenMenuItem->SetBitmaps( icon_folder_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileOpenMenuItem->SetBitmap( icon_folder_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( m_fileOpenMenuItem );

	wxMenuItem* m_fileSaveMenuItem;
	m_fileSaveMenuItem = new wxMenuItem( m_fileMenu, wxID_SAVE, wxString( wxT("저장(&S)") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileSaveMenuItem->SetBitmaps( icon_save_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileSaveMenuItem->SetBitmap( icon_save_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( m_fileSaveMenuItem );

	m_fileMenu->AppendSeparator();

	wxMenuItem* m_fileExitMenuItem;
	m_fileExitMenuItem = new wxMenuItem( m_fileMenu, wxID_EXIT, wxString( wxT("닫기(&X)") ) + wxT('\t') + wxT("Alt+F4"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_fileExitMenuItem->SetBitmaps( icon_exit_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	m_fileExitMenuItem->SetBitmap( icon_exit_png_to_wx_bitmap() );
	#endif
	m_fileMenu->Append( m_fileExitMenuItem );

	m_menuBar->Append( m_fileMenu, wxT("파일(&F)") );

	m_helpMenu = new wxMenu();
	wxMenuItem* m_helpAboutMenuItem;
	m_helpAboutMenuItem = new wxMenuItem( m_helpMenu, wxID_ABOUT, wxString( wxT("GS 에디터 정보(&A)...") ) , wxEmptyString, wxITEM_NORMAL );
	m_helpMenu->Append( m_helpAboutMenuItem );

	m_menuBar->Append( m_helpMenu, wxT("도움말(&H)") );

	this->SetMenuBar( m_menuBar );

	m_toolBar = this->CreateToolBar( wxTB_DEFAULT_STYLE|wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY );
	m_toolBar->SetToolSeparation( 25 );
	m_tool10 = m_toolBar->AddTool( wxID_ANY, wxT("tool"), icon_folder_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar->AddSeparator();

	m_tool9 = m_toolBar->AddTool( wxID_ANY, wxT("tool"), icon_exit_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar->Realize();

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileOpenMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileSaveMenuItem->GetId());
	m_fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_fileExitMenuItem->GetId());
	m_helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnMenuSelected ), this, m_helpAboutMenuItem->GetId());
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

	m_appIconBitmap = new wxStaticBitmap( this, wxID_ANY, icon_app_png_to_wx_bitmap(), wxDefaultPosition, wxSize( -1,-1 ), 0 );
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
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	m_TopPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_TopPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* listSizer;
	listSizer = new wxBoxSizer( wxVERTICAL );

	m_messageLabel = new wxStaticText( m_TopPanel, wxID_ANY, wxT("아래 목록과 같이 롬 파일의 데이터가 일부 손상되었습니다."), wxDefaultPosition, wxDefaultSize, 0 );
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
	buttonSizer = new wxBoxSizer( wxVERTICAL );

	m_ConfirmButton = new wxButton( m_bottomPanel, wxID_ANY, wxT("확인"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	buttonSizer->Add( m_ConfirmButton, 0, wxALIGN_RIGHT|wxALL, 5 );


	m_bottomPanel->SetSizer( buttonSizer );
	m_bottomPanel->Layout();
	buttonSizer->Fit( m_bottomPanel );
	mainSizer->Add( m_bottomPanel, 0, wxEXPAND | wxALL, 8 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_ConfirmButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BadDataDialogBase::OnConfirmButtonClick ), NULL, this );
}

BadDataDialogBase::~BadDataDialogBase()
{
}

DatabasePanelBase::DatabasePanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
}

DatabasePanelBase::~DatabasePanelBase()
{
}
