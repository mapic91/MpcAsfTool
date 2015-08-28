#include "ExportToImg.h"

#include "wx/msgdlg.h"
//(*InternalHeaders(ExportToImg)
#include <wx/string.h>
//*)

//(*IdInit(ExportToImg)
const long ExportToImg::ID_STATICTEXT1 = wxNewId();
const long ExportToImg::ID_BUTTON1 = wxNewId();
const long ExportToImg::ID_BUTTON2 = wxNewId();
const long ExportToImg::ID_TEXTCTRL1 = wxNewId();
const long ExportToImg::ID_CHECKBOX1 = wxNewId();
const long ExportToImg::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ExportToImg,wxDialog)
	//(*EventTable(ExportToImg)
	//*)
END_EVENT_TABLE()

ExportToImg::ExportToImg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ExportToImg)
	Create(parent, wxID_ANY, _T("请输入"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(278,125));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(-8,-8), wxSize(336,152), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _T("文件名前缀："), wxPoint(32,35), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Button1 = new wxButton(Panel1, ID_BUTTON1, _T("确定"), wxPoint(56,90), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(Panel1, ID_BUTTON2, _T("取消"), wxPoint(152,90), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	TextCtrl_FilePrefix = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxPoint(114,31), wxSize(152,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl_FilePrefix->SetToolTip(_T("不要包含  \\  /  :  *  \?  \"  <  >  | "));
	m_cbReverse = new wxCheckBox(Panel1, ID_CHECKBOX1, _T("帧倒序"), wxPoint(32,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_cbReverse->SetValue(false);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExportToImg::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExportToImg::OnButton2Click);
	//*)
}

ExportToImg::~ExportToImg()
{
	//(*Destroy(ExportToImg)
	//*)
}


void ExportToImg::OnButton1Click(wxCommandEvent& event)
{
    nameprefix = TextCtrl_FilePrefix->GetValue();
    EndModal(wxID_OK);
}
void ExportToImg::OnButton2Click(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
