#include "ProgressDlg.h"

//(*InternalHeaders(ProgressDlg)
#include <wx/string.h>
//*)

//(*IdInit(ProgressDlg)
const long ProgressDlg::ID_STATICTEXT1 = wxNewId();
const long ProgressDlg::ID_STATICTEXT2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ProgressDlg,wxDialog)
	//(*EventTable(ProgressDlg)
	//*)
END_EVENT_TABLE()

ProgressDlg::ProgressDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ProgressDlg)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW, _T("id"));
	SetClientSize(wxSize(800,200));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, wxEmptyString, wxPoint(152,136), wxDefaultSize, wxTRANSPARENT_WINDOW, _T("ID_STATICTEXT1"));
	StaticText_Progress = new wxStaticText(this, ID_STATICTEXT2, _T("......."), wxPoint(0,88), wxSize(100,20), wxALIGN_CENTRE|wxTRANSPARENT_WINDOW, _T("ID_STATICTEXT2"));
	//*)
}

ProgressDlg::~ProgressDlg()
{
	//(*Destroy(ProgressDlg)
	//*)
}

