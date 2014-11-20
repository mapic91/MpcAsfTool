///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "FileExplorerPanelBase.h"

///////////////////////////////////////////////////////////////////////////

FileExplorerPanelBase::FileExplorerPanelBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_genericDirCtrl1 = new wxGenericDirCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_3D_INTERNAL|wxSUNKEN_BORDER, wxEmptyString, 0 );
	
	m_genericDirCtrl1->ShowHidden( false );
	bSizer2->Add( m_genericDirCtrl1, 1, wxEXPAND | wxALL, 0 );
	
	mcb_Fileter = new wxComboBox( m_panel1, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	mcb_Fileter->Append( wxT("所有文件") );
	mcb_Fileter->Append( wxT("MPC ASF SPR RPC") );
	mcb_Fileter->Append( wxT("MPC") );
	mcb_Fileter->Append( wxT("ASF") );
	mcb_Fileter->Append( wxT("SPR") );
	mcb_Fileter->Append( wxT("RPC") );
	mcb_Fileter->SetSelection( 0 );
	bSizer2->Add( mcb_Fileter, 0, wxALL|wxEXPAND, 1 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_genericDirCtrl1->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( FileExplorerPanelBase::OnTreeItemActivated ), NULL, this );
	mcb_Fileter->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FileExplorerPanelBase::OnFilterChange ), NULL, this );
}

FileExplorerPanelBase::~FileExplorerPanelBase()
{
	// Disconnect Events
	m_genericDirCtrl1->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( FileExplorerPanelBase::OnTreeItemActivated ), NULL, this );
	mcb_Fileter->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FileExplorerPanelBase::OnFilterChange ), NULL, this );
	
}
