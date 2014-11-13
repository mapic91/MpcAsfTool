#include "BatDialog.h"

#include "wx/filedlg.h"

//(*InternalHeaders(BatDialog)
#include <wx/string.h>
//*)

//(*IdInit(BatDialog)
const long BatDialog::ID_RICHTEXTCTRL1 = wxNewId();
const long BatDialog::ID_BUTTON1 = wxNewId();
const long BatDialog::ID_BUTTON2 = wxNewId();
const long BatDialog::ID_RADIOBUTTON1 = wxNewId();
const long BatDialog::ID_RADIOBUTTON2 = wxNewId();
const long BatDialog::ID_STATICTEXT1 = wxNewId();
const long BatDialog::ID_BUTTON3 = wxNewId();
const long BatDialog::ID_BUTTON4 = wxNewId();
const long BatDialog::ID_CHECKBOX1 = wxNewId();
const long BatDialog::ID_STATICTEXT2 = wxNewId();
const long BatDialog::ID_COLOURPICKERCTRL1 = wxNewId();
const long BatDialog::ID_STATICTEXT3 = wxNewId();
const long BatDialog::ID_SPINCTRL1 = wxNewId();
const long BatDialog::ID_SPINCTRL2 = wxNewId();
const long BatDialog::ID_SPINCTRL3 = wxNewId();
const long BatDialog::ID_STATICTEXT4 = wxNewId();
const long BatDialog::ID_STATICTEXT5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(BatDialog,wxDialog)
	//(*EventTable(BatDialog)
	//*)
END_EVENT_TABLE()

BatDialog::BatDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(BatDialog)
	Create(parent, wxID_ANY, _T("图片批量导出"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(400,387));
	RichTextCtrl_List = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxPoint(8,16), wxSize(288,240), wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	Button_Add = new wxButton(this, ID_BUTTON1, _T("添加"), wxPoint(304,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button_Empty = new wxButton(this, ID_BUTTON2, _T("清空"), wxPoint(304,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	RadioButton_Gif = new wxRadioButton(this, ID_RADIOBUTTON1, _T("GIF"), wxPoint(320,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	RadioButton_Gif->SetValue(true);
	RadioButton_Png = new wxRadioButton(this, ID_RADIOBUTTON2, _T("PNG"), wxPoint(320,176), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("导出为："), wxPoint(304,120), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	Button_Ok = new wxButton(this, ID_BUTTON3, _T("确定"), wxPoint(72,350), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Button_Cancle = new wxButton(this, ID_BUTTON4, _T("取消"), wxPoint(224,350), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	CheckBox_isShd = new wxCheckBox(this, ID_CHECKBOX1, _T("SHD"), wxPoint(16,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox_isShd->SetValue(true);
	CheckBox_isShd->SetToolTip(_T("是否包含影子"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("底色："), wxPoint(72,272), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	ColourPickerCtrl_BaseColor = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL1, wxColour(255,255,255), wxPoint(112,268), wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("透明域："), wxPoint(176,272), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	SpinCtrl_AlphaMask = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxPoint(230,268), wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL1"));
	SpinCtrl_AlphaMask->SetValue(_T("0"));
	SpinCtrl_FrameEnd = new wxSpinCtrl(this, ID_SPINCTRL2, _T("99999999"), wxPoint(210,305), wxSize(88,21), 0, 1, 99999999, 99999999, _T("ID_SPINCTRL2"));
	SpinCtrl_FrameEnd->SetValue(_T("99999999"));
	SpinCtrl_FrameBegin = new wxSpinCtrl(this, ID_SPINCTRL3, _T("1"), wxPoint(80,305), wxSize(88,21), 0, 1, 99999999, 1, _T("ID_SPINCTRL3"));
	SpinCtrl_FrameBegin->SetValue(_T("1"));
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("到"), wxPoint(180,307), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("帧范围："), wxPoint(24,307), wxDefaultSize, 0, _T("ID_STATICTEXT5"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BatDialog::OnButton_AddClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BatDialog::OnButton_EmptyClick);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&BatDialog::OnRadioButton_GifSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&BatDialog::OnRadioButton_PngSelect);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BatDialog::OnButton_OkClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BatDialog::OnButton_CancleClick);
	//*)
}

BatDialog::~BatDialog()
{
	//(*Destroy(BatDialog)
	//*)
}


void BatDialog::OnButton_AddClick(wxCommandEvent& event)
{
    wxFileDialog filedlg(this, wxT("选择MPC ASF SPR RPC文件"), wxT(""), wxT(""),
                         wxT("MPC ASF SPR RPC(*.mpc,*.asf,*.spr,*.rpc)|*.mpc;*.asf;*.spr;*.rpc|MPC(*.mpc)|*.mpc|ASF(*.asf)|*.asf|SPR(*.spr)|*.spr|RPC(*.rpc)|*.rpc"),
                         wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

    if(filedlg.ShowModal() == wxID_OK)
    {
        wxArrayString files;
        filedlg.GetPaths(files);

        for(size_t i = 0; i < files.GetCount(); i++)
        {
            RichTextCtrl_List->AppendText(files[i]+wxT("\n"));
        }
    }
}

void BatDialog::OnButton_EmptyClick(wxCommandEvent& event)
{
    RichTextCtrl_List->Clear();
}

void BatDialog::OnButton_OkClick(wxCommandEvent& event)
{
    EndModal(wxID_OK);
}

void BatDialog::OnButton_CancleClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void BatDialog::OnRadioButton_GifSelect(wxCommandEvent& event)
{
}

void BatDialog::OnRadioButton_PngSelect(wxCommandEvent& event)
{
}
