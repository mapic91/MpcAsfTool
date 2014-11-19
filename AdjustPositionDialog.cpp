#include "AdjustPositionDialog.h"

#include "wx/dcbuffer.h"

//(*InternalHeaders(AdjustPositionDialog)
#include <wx/string.h>
//*)

//(*IdInit(AdjustPositionDialog)
const long AdjustPositionDialog::ID_PANEL1 = wxNewId();
const long AdjustPositionDialog::ID_RADIOBUTTON1 = wxNewId();
const long AdjustPositionDialog::ID_RADIOBUTTON2 = wxNewId();
const long AdjustPositionDialog::ID_STATICTEXT2 = wxNewId();
const long AdjustPositionDialog::ID_SPINCTRL2 = wxNewId();
const long AdjustPositionDialog::ID_STATICTEXT1 = wxNewId();
const long AdjustPositionDialog::ID_SPINCTRL1 = wxNewId();
const long AdjustPositionDialog::ID_STATICTEXT3 = wxNewId();
const long AdjustPositionDialog::ID_SPINCTRL3 = wxNewId();
const long AdjustPositionDialog::ID_STATICTEXT4 = wxNewId();
const long AdjustPositionDialog::ID_SPINCTRL4 = wxNewId();
const long AdjustPositionDialog::ID_CHECKBOX1 = wxNewId();
const long AdjustPositionDialog::ID_BUTTON1 = wxNewId();
const long AdjustPositionDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AdjustPositionDialog,wxDialog)
    //(*EventTable(AdjustPositionDialog)
    //*)
    EVT_SIZE(AdjustPositionDialog::OnSize)
END_EVENT_TABLE()

AdjustPositionDialog::AdjustPositionDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(AdjustPositionDialog)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _T("坐标调整"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    SetClientSize(wxSize(200,400));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Panel_Show = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(600,400), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel_Show->SetMinSize(wxSize(200,200));
    BoxSizer2->Add(Panel_Show, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    RadioButton_j2 = new wxRadioButton(this, ID_RADIOBUTTON1, _T("剑二"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    BoxSizer3->Add(RadioButton_j2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_yyxj = new wxRadioButton(this, ID_RADIOBUTTON2, _T("月影、新剑"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    RadioButton_yyxj->SetValue(true);
    BoxSizer3->Add(RadioButton_yyxj, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("水平偏移"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer4->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_OffX = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL2"));
    SpinCtrl_OffX->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl_OffX, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("垂直偏移"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer4->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_OffY = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL1"));
    SpinCtrl_OffY->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl_OffY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("图片水平"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer6->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_PicX = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL3"));
    SpinCtrl_PicX->SetValue(_T("0"));
    BoxSizer6->Add(SpinCtrl_PicX, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("图片垂直"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer6->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_PicY = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL4"));
    SpinCtrl_PicY->SetValue(_T("0"));
    BoxSizer6->Add(SpinCtrl_PicY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_LockCurrentFrame = new wxCheckBox(this, ID_CHECKBOX1, _T("锁定"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox_LockCurrentFrame->SetValue(false);
    CheckBox_LockCurrentFrame->SetToolTip(_T("锁定当前帧"));
    BoxSizer6->Add(CheckBox_LockCurrentFrame, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    Button_Ok = new wxButton(this, ID_BUTTON1, _T("确认"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer5->Add(Button_Ok, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Cancle = new wxButton(this, ID_BUTTON2, _T("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer5->Add(Button_Cancle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&AdjustPositionDialog::OnRadioButton_j2Select);
    Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&AdjustPositionDialog::OnRadioButton_yyxjSelect);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AdjustPositionDialog::OnSpinCtrl_OffXChange);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AdjustPositionDialog::OnSpinCtrl_OffYChange);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AdjustPositionDialog::OnSpinCtrl_PicXChange);
    Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AdjustPositionDialog::OnSpinCtrl_PicYChange);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AdjustPositionDialog::OnButton_OkClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AdjustPositionDialog::OnButton_CancleClick);
    //*)

    this->SetSize(600, 500);
    this->Center();

    Panel_Show->Connect( wxEVT_PAINT, wxPaintEventHandler( AdjustPositionDialog::OnDraw ), NULL, this );
}

AdjustPositionDialog::~AdjustPositionDialog()
{
    //(*Destroy(AdjustPositionDialog)
    //*)
    Panel_Show->Disconnect( wxEVT_PAINT, wxPaintEventHandler( AdjustPositionDialog::OnDraw ), NULL, this );
}


void AdjustPositionDialog::OnRadioButton_yyxjSelect(wxCommandEvent& event)
{
    SpinCtrl_OffX->Enable(true);
    RedrawShow();
}

void AdjustPositionDialog::OnRadioButton_j2Select(wxCommandEvent& event)
{
    SpinCtrl_OffX->Enable(false);
    RedrawShow();
}

void AdjustPositionDialog::OnSpinCtrl_OffXChange(wxSpinEvent& event)
{
    RedrawShow();
}

void AdjustPositionDialog::OnSpinCtrl_OffYChange(wxSpinEvent& event)
{
    RedrawShow();
}

void AdjustPositionDialog::OnSpinCtrl_PicXChange(wxSpinEvent& event)
{
    RedrawShow();
}

void AdjustPositionDialog::OnSpinCtrl_PicYChange(wxSpinEvent& event)
{
    RedrawShow();
}

void AdjustPositionDialog::OnButton_OkClick(wxCommandEvent& event)
{
    EndModal(wxID_OK);
}

void AdjustPositionDialog::OnButton_CancleClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void AdjustPositionDialog::OnDraw(wxPaintEvent& event)
{

    int width, height, midx, midy;
    Panel_Show->GetClientSize(&width, &height);
    midx = width / 2;
    midy = height /2;

    wxPaintDC dc(Panel_Show);

    if(m_img.IsOk())
    {
        int imgposx, imgposy, imgwidth, imgheight;
        imgwidth = m_img.GetWidth();
        imgheight = m_img.GetHeight();
        if(RadioButton_j2->GetValue()) //j2
        {
            imgposx = midx - imgwidth / 2 + SpinCtrl_PicX->GetValue() - m_PicX;
            imgposy = midy + 16 - imgheight +
                    SpinCtrl_OffY->GetValue() +
                    SpinCtrl_PicY->GetValue() -
                    m_PicY;
        }
        else // yueyin xinjian
        {
            imgposx = midx -
                SpinCtrl_OffX->GetValue() +
                SpinCtrl_PicX->GetValue() -
                m_PicX;
            imgposy = midy -
                SpinCtrl_OffY->GetValue() +
                SpinCtrl_PicY->GetValue() -
                m_PicY;
        }

        wxBitmap drawbmp(m_img);
        wxMemoryDC mdc(drawbmp);
        dc.Blit((wxCoord)imgposx,
                imgposy,
                imgwidth,
                imgheight,
                &mdc,
                0,
                0);
    }

    dc.SetPen(*(wxThePenList->FindOrCreatePen(*wxRED, 1, wxSOLID)));

    wxPoint points[5];
    points[0] = wxPoint(32, 0);
    points[1] = wxPoint(64, 16);
    points[2] = wxPoint(32, 32);
    points[3] = wxPoint(0, 16);
    points[4] = wxPoint(32, 0);
    dc.DrawLines(5, points, midx - 32, midy - 16);
}



