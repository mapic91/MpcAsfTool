///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FILEEXPLORERPANELBASE_H__
#define __FILEEXPLORERPANELBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/dirctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class FileExplorerPanelBase
///////////////////////////////////////////////////////////////////////////////
class FileExplorerPanelBase : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxGenericDirCtrl* m_genericDirCtrl1;
		wxComboBox* mcb_Fileter;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTreeItemActivated( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnFilterChange( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FileExplorerPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wjll"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 353,451 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~FileExplorerPanelBase();
	
};

#endif //__FILEEXPLORERPANELBASE_H__
