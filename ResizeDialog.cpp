#include "ResizeDialog.h"

//(*InternalHeaders(ResizeDialog)
#include <wx/string.h>
//*)

//(*IdInit(ResizeDialog)
const long ResizeDialog::ID_STATICTEXT1 = wxNewId();
const long ResizeDialog::ID_SPINCTRL1 = wxNewId();
const long ResizeDialog::ID_STATICTEXT2 = wxNewId();
const long ResizeDialog::ID_SPINCTRL2 = wxNewId();
const long ResizeDialog::ID_STATICTEXT3 = wxNewId();
const long ResizeDialog::ID_SPINCTRL3 = wxNewId();
const long ResizeDialog::ID_STATICTEXT4 = wxNewId();
const long ResizeDialog::ID_CHECKBOX1 = wxNewId();
const long ResizeDialog::ID_BUTTON1 = wxNewId();
const long ResizeDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ResizeDialog,wxDialog)
    //(*EventTable(ResizeDialog)
    //*)
END_EVENT_TABLE()

ResizeDialog::ResizeDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(ResizeDialog)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, id, _T("缩放图片"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(435,155));
    Move(wxDefaultPosition);
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("宽：    "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    msc_Width = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 1, 99999, 0, _T("ID_SPINCTRL1"));
    msc_Width->SetValue(_T("0"));
    BoxSizer2->Add(msc_Width, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("高：    "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer2->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    msc_Height = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 1, 99999, 0, _T("ID_SPINCTRL2"));
    msc_Height->SetValue(_T("0"));
    BoxSizer2->Add(msc_Height, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("比例："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    msc_Percent = new wxSpinCtrl(this, ID_SPINCTRL3, _T("100"), wxDefaultPosition, wxDefaultSize, 0, 1, 9999, 100, _T("ID_SPINCTRL3"));
    msc_Percent->SetValue(_T("100"));
    BoxSizer3->Add(msc_Percent, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("%"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer3->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mcb_KeepRatio = new wxCheckBox(this, ID_CHECKBOX1, _T("保持长宽比"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    mcb_KeepRatio->SetValue(true);
    BoxSizer3->Add(mcb_KeepRatio, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    mb_Ok = new wxButton(this, ID_BUTTON1, _T("确定"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer4->Add(mb_Ok, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mb_Cancle = new wxButton(this, ID_BUTTON2, _T("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer4->Add(mb_Cancle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ResizeDialog::Onmsc_WidthChange);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ResizeDialog::Onmsc_HeightChange);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ResizeDialog::Onmsc_PercentChange);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ResizeDialog::Onmcb_KeepRatioClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ResizeDialog::Onmb_OkClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ResizeDialog::Onmb_CancleClick);
    //*)
}

ResizeDialog::~ResizeDialog()
{
    //(*Destroy(ResizeDialog)
    //*)
}
void ResizeDialog::SizeChange()
{
	if(m_CurrentWidth == 0 || m_CurrentHeight == 0) return;

}
void ResizeDialog::PercentChange()
{
	float ratio = (float)msc_Percent->GetValue()/(float)100;
    msc_Width->SetValue((int)(ratio*m_CurrentWidth));
    msc_Height->SetValue((int)(ratio*m_CurrentHeight));
}

void ResizeDialog::Onmb_OkClick(wxCommandEvent& event)
{
    EndModal(wxID_OK);
}

void ResizeDialog::Onmb_CancleClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void ResizeDialog::Onmsc_PercentChange(wxSpinEvent& event)
{
	PercentChange();
}

void ResizeDialog::Onmsc_WidthChange(wxSpinEvent& event)
{
	if(m_CurrentWidth == 0 || m_CurrentHeight == 0) return;
    if(!mcb_KeepRatio->GetValue()) return;
	float ratio = (float)event.GetValue()/(float)m_CurrentWidth;
	msc_Height->SetValue((int)(ratio*m_CurrentHeight));
	msc_Percent->SetValue((int)(ratio*100));
}

void ResizeDialog::Onmsc_HeightChange(wxSpinEvent& event)
{
	if(m_CurrentWidth == 0 || m_CurrentHeight == 0) return;
    if(!mcb_KeepRatio->GetValue()) return;
    float ratio = (float)event.GetValue()/(float)m_CurrentWidth;
    msc_Width->SetValue((int)(ratio*m_CurrentWidth));
    msc_Percent->SetValue((int)(ratio*100));
}

void ResizeDialog::Onmcb_KeepRatioClick(wxCommandEvent& event)
{
	if(!event.IsChecked()) return;
    PercentChange();
}
