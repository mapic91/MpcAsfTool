#include "MpcAsfTool.h"
#include "DlgAddFrames.h"
#include "wx/filedlg.h"
#include "wx/dirdlg.h"
#include "wx/msgdlg.h"
#include "wx/filename.h"
#include "wx/log.h"

#include "ExportToImg.h"

//(*InternalHeaders(MpcAsfTool)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(MpcAsfTool)
const long MpcAsfTool::ID_STATICTEXT27 = wxNewId();
const long MpcAsfTool::ID_STATICBITMAP1 = wxNewId();
const long MpcAsfTool::ID_SCROLLEDWINDOW2 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT19 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT20 = wxNewId();
const long MpcAsfTool::ID_SLIDER_FRAME = wxNewId();
const long MpcAsfTool::ID_STATICTEXT21 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT24 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL11 = wxNewId();
const long MpcAsfTool::ID_BUTTON1 = wxNewId();
const long MpcAsfTool::ID_BUTTON2 = wxNewId();
const long MpcAsfTool::ID_BUTTON3 = wxNewId();
const long MpcAsfTool::ID_STATICLINE1 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT7 = wxNewId();
const long MpcAsfTool::ID_STATICLINE2 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT1 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL1 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT2 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL2 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT3 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL12 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT5 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL4 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT4 = wxNewId();
const long MpcAsfTool::ID_SLIDER1 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT6 = wxNewId();
const long MpcAsfTool::ID_STATICLINE3 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT8 = wxNewId();
const long MpcAsfTool::ID_STATICLINE4 = wxNewId();
const long MpcAsfTool::ID_CHECKBOX1 = wxNewId();
const long MpcAsfTool::ID_STATICLINE5 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT9 = wxNewId();
const long MpcAsfTool::ID_STATICLINE6 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT10 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL3 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT13 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT25 = wxNewId();
const long MpcAsfTool::ID_STATICLINE9 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT18 = wxNewId();
const long MpcAsfTool::ID_STATICLINE10 = wxNewId();
const long MpcAsfTool::ID_RADIOBUTTON3 = wxNewId();
const long MpcAsfTool::ID_RADIOBUTTON1 = wxNewId();
const long MpcAsfTool::ID_RADIOBUTTON2 = wxNewId();
const long MpcAsfTool::ID_CHECKBOX2 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT11 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL5 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT12 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL6 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT14 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL7 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT15 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL8 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT23 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL10 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT26 = wxNewId();
const long MpcAsfTool::ID_STATICLINE7 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT16 = wxNewId();
const long MpcAsfTool::ID_STATICLINE8 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT17 = wxNewId();
const long MpcAsfTool::ID_COLOURPICKERCTRL1 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT22 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL9 = wxNewId();
const long MpcAsfTool::ID_SCROLLEDWINDOW1 = wxNewId();
const long MpcAsfTool::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MpcAsfTool,wxFrame)
    //(*EventTable(MpcAsfTool)
    //*)
    EVT_SIZE(MpcAsfTool::OnSize)
    EVT_CLOSE(MpcAsfTool::OnClose)
    EVT_MENU(wxID_NEW, MpcAsfTool::OnNew)
    EVT_MENU(wxID_OPEN, MpcAsfTool::OnFileOpen)
    EVT_MENU(wxID_SAVE, MpcAsfTool::OnFileSave)
    EVT_MENU(wxID_SAVEAS, MpcAsfTool::OnFileSaveAs)
    EVT_MENU(ID_EXPORT_TO_GIF, MpcAsfTool::OnExportToGif)
    EVT_MENU(ID_EXPORT_TO_PNG, MpcAsfTool::OnExportToPng)
    EVT_MENU(wxID_EXIT, MpcAsfTool::OnExit)
    EVT_MENU(wxID_HELP, MpcAsfTool::OnHelp)
    EVT_MENU(wxID_ABORT, MpcAsfTool::OnAbout)
    EVT_COMMAND_SCROLL(MpcAsfTool::ID_SLIDER_FRAME, MpcAsfTool::OnSlider_FrameCmdScroll)
    EVT_COMMAND_SCROLL(MpcAsfTool::ID_SLIDER1, MpcAsfTool::OnSlider_IntervalCmdScroll)
END_EVENT_TABLE()

MpcAsfTool::MpcAsfTool(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(MpcAsfTool)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer29;
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer20;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer21;
    wxBoxSizer* BoxSizer23;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer18;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer28;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer27;
    wxBoxSizer* BoxSizer17;
    wxBoxSizer* BoxSizer24;
    wxBoxSizer* BoxSizer26;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxBoxSizer* BoxSizer_ScrollWindow;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer25;

    Create(parent, wxID_ANY, _("MPC ASF 编辑器"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(978,737));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(232,256), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
    StaticText_CurrentFile = new wxStaticText(Panel1, ID_STATICTEXT27, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    BoxSizer28->Add(StaticText_CurrentFile, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer28, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    ScrolledWindow_BmpShow = new wxScrolledWindow(Panel1, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW2"));
    BoxSizer_ScrollWindow = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer_ScrollWindow->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticBitmap_Show = new wxStaticBitmap(ScrolledWindow_BmpShow, ID_STATICBITMAP1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_MISSING_IMAGE")),wxART_OTHER), wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP1"));
    StaticBitmap_Show->SetBackgroundColour(wxColour(255,255,255));
    BoxSizer_ScrollWindow->Add(StaticBitmap_Show, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer_ScrollWindow->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    ScrolledWindow_BmpShow->SetSizer(BoxSizer_ScrollWindow);
    BoxSizer_ScrollWindow->Fit(ScrolledWindow_BmpShow);
    BoxSizer_ScrollWindow->SetSizeHints(ScrolledWindow_BmpShow);
    BoxSizer3->Add(ScrolledWindow_BmpShow, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    StaticText19 = new wxStaticText(Panel1, ID_STATICTEXT19, _("帧："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    BoxSizer29->Add(StaticText19, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Frame_Sum = new wxStaticText(Panel1, ID_STATICTEXT20, _("000"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    StaticText_Frame_Sum->SetToolTip(_("总帧数"));
    BoxSizer29->Add(StaticText_Frame_Sum, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Frame = new wxSlider(Panel1, ID_SLIDER_FRAME, 0, 1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_FRAME"));
    Slider_Frame->Disable();
    BoxSizer29->Add(Slider_Frame, 8, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Frame_Cur = new wxStaticText(Panel1, ID_STATICTEXT21, _("000"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StaticText_Frame_Cur->SetToolTip(_("当前帧"));
    BoxSizer29->Add(StaticText_Frame_Cur, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer29, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT24, _("跳到："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    BoxSizer5->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Frame_Goto = new wxSpinCtrl(Panel1, ID_SPINCTRL11, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 2147483646, 0, _T("ID_SPINCTRL11"));
    SpinCtrl_Frame_Goto->SetValue(_T("0"));
    SpinCtrl_Frame_Goto->Disable();
    BoxSizer5->Add(SpinCtrl_Frame_Goto, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_AddFrames = new wxButton(Panel1, ID_BUTTON1, _("添加"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button_AddFrames->Disable();
    Button_AddFrames->SetToolTip(_("添加帧"));
    BoxSizer5->Add(Button_AddFrames, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_DeleteCurrentFrame = new wxButton(Panel1, ID_BUTTON2, _("删除"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button_DeleteCurrentFrame->Disable();
    Button_DeleteCurrentFrame->SetToolTip(_("删除当前帧"));
    BoxSizer5->Add(Button_DeleteCurrentFrame, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_UnDelete = new wxButton(Panel1, ID_BUTTON3, _("还原"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button_UnDelete->Disable();
    Button_UnDelete->SetToolTip(_("还原上次删除"));
    BoxSizer5->Add(Button_UnDelete, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
    ScrolledWindow_Setting = new wxScrolledWindow(Panel1, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
    BoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine1 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer7->Add(StaticLine1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT7, _("基本参数"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer7->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine2 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    BoxSizer7->Add(StaticLine2, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer7, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT1, _("图片宽度："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer8->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_GlobalWidth = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 9999, 1, _T("ID_SPINCTRL1"));
    SpinCtrl_GlobalWidth->SetValue(_T("1"));
    SpinCtrl_GlobalWidth->Disable();
    BoxSizer8->Add(SpinCtrl_GlobalWidth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT2, _("图片高度："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer8->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_GlobalHeight = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 9999, 1, _T("ID_SPINCTRL2"));
    SpinCtrl_GlobalHeight->SetValue(_T("1"));
    SpinCtrl_GlobalHeight->Disable();
    BoxSizer8->Add(SpinCtrl_GlobalHeight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT3, _("方向：        "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer6->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Direction = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL12, _T("1"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 1, _T("ID_SPINCTRL12"));
    SpinCtrl_Direction->SetValue(_T("1"));
    SpinCtrl_Direction->Disable();
    BoxSizer6->Add(SpinCtrl_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT5, _("垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer6->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Bottom = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL4"));
    SpinCtrl_Bottom->SetValue(_T("0"));
    SpinCtrl_Bottom->Disable();
    BoxSizer6->Add(SpinCtrl_Bottom, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    StaticText4 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT4, _("时间间隔:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer9->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Interval = new wxSlider(ScrolledWindow_Setting, ID_SLIDER1, 100, 0, 200, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    Slider_Interval->Disable();
    BoxSizer9->Add(Slider_Interval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Interval = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT6, _("100"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer9->Add(StaticText_Interval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine3 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    BoxSizer10->Add(StaticLine3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT8, _("MPC"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer10->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine4 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    BoxSizer10->Add(StaticLine4, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer10, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_ShowShd = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX1, _("显示影子（SHD文件）"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox_ShowShd->SetValue(false);
    CheckBox_ShowShd->Disable();
    BoxSizer11->Add(CheckBox_ShowShd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer4->Add(BoxSizer14, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine5 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE5, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
    BoxSizer12->Add(StaticLine5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT9, _("ASF"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer12->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine6 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE6, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE6"));
    BoxSizer12->Add(StaticLine6, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer12, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    StaticText10 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT10, _("水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    BoxSizer15->Add(StaticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Left = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL3"));
    SpinCtrl_Left->SetValue(_T("0"));
    SpinCtrl_Left->Disable();
    BoxSizer15->Add(SpinCtrl_Left, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText13 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    BoxSizer15->Add(StaticText13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText20 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT25, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    BoxSizer15->Add(StaticText20, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer15->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer15, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine9 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE9, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE9"));
    BoxSizer24->Add(StaticLine9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText18 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT18, _("影子"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    BoxSizer24->Add(StaticText18, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine10 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE10, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE10"));
    BoxSizer24->Add(StaticLine10, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer24, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    RadioButton_NoShadow = new wxRadioButton(ScrolledWindow_Setting, ID_RADIOBUTTON3, _("不生成影子"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    RadioButton_NoShadow->SetValue(true);
    RadioButton_NoShadow->Disable();
    BoxSizer16->Add(RadioButton_NoShadow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_MpcShadow = new wxRadioButton(ScrolledWindow_Setting, ID_RADIOBUTTON1, _("方案1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    RadioButton_MpcShadow->Disable();
    RadioButton_MpcShadow->SetToolTip(_("适合剑二"));
    BoxSizer16->Add(RadioButton_MpcShadow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_AsfShadow = new wxRadioButton(ScrolledWindow_Setting, ID_RADIOBUTTON2, _("方案2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    RadioButton_AsfShadow->Disable();
    RadioButton_AsfShadow->SetToolTip(_("适合月影、新剑"));
    BoxSizer16->Add(RadioButton_AsfShadow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_LockFrame = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX2, _("编辑当前帧并锁定"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox_LockFrame->SetValue(false);
    CheckBox_LockFrame->Disable();
    BoxSizer16->Add(CheckBox_LockFrame, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer16, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    StaticText11 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT11, _("光线水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer17->Add(StaticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_SunX = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL5"));
    SpinCtrl_SunX->SetValue(_T("0"));
    SpinCtrl_SunX->Disable();
    BoxSizer17->Add(SpinCtrl_SunX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT12, _("光线垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    BoxSizer17->Add(StaticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_SunY = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL6"));
    SpinCtrl_SunY->SetValue(_T("0"));
    SpinCtrl_SunY->Disable();
    BoxSizer17->Add(SpinCtrl_SunY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer17, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
    StaticText14 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT14, _("影子水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    BoxSizer18->Add(StaticText14, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_ShadowX = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL7"));
    SpinCtrl_ShadowX->SetValue(_T("0"));
    SpinCtrl_ShadowX->Disable();
    BoxSizer18->Add(SpinCtrl_ShadowX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText15 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT15, _("影子垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    BoxSizer18->Add(StaticText15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_ShadowY = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL8"));
    SpinCtrl_ShadowY->SetValue(_T("0"));
    SpinCtrl_ShadowY->Disable();
    BoxSizer18->Add(SpinCtrl_ShadowY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer18, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer27 = new wxBoxSizer(wxHORIZONTAL);
    StaticText23 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT23, _("全局透明度：    "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    StaticText23->SetToolTip(_("对SHD文件无效，对ASF、PNG等文件有效"));
    BoxSizer27->Add(StaticText23, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_ShadowAlpha = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL10, _T("185"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 185, _T("ID_SPINCTRL10"));
    SpinCtrl_ShadowAlpha->SetValue(_T("185"));
    SpinCtrl_ShadowAlpha->Disable();
    BoxSizer27->Add(SpinCtrl_ShadowAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText21 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT26, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    BoxSizer27->Add(StaticText21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer27->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer27, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine7 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE7, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE7"));
    BoxSizer20->Add(StaticLine7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText16 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT16, _("优化"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    StaticText16->SetToolTip(_("对有透明值的文件（ASF、PNG等)存为MPC、GIF时有效"));
    BoxSizer20->Add(StaticText16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine8 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE8, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE8"));
    BoxSizer20->Add(StaticLine8, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer20, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    StaticText17 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT17, _("底色："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    BoxSizer23->Add(StaticText17, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColourPickerCtrl_BaseColor = new wxColourPickerCtrl(ScrolledWindow_Setting, ID_COLOURPICKERCTRL1, wxColour(255,255,255), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    ColourPickerCtrl_BaseColor->Disable();
    BoxSizer23->Add(ColourPickerCtrl_BaseColor, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer23->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText22 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT22, _("透明阈："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    BoxSizer23->Add(StaticText22, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_AlphaMask = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL9"));
    SpinCtrl_AlphaMask->SetValue(_T("0"));
    SpinCtrl_AlphaMask->Disable();
    BoxSizer23->Add(SpinCtrl_AlphaMask, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer23, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer25->Add(BoxSizer4, 9, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer25->Add(BoxSizer26, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
    ScrolledWindow_Setting->SetSizer(BoxSizer25);
    BoxSizer25->Fit(ScrolledWindow_Setting);
    BoxSizer25->SetSizeHints(ScrolledWindow_Setting);
    BoxSizer21->Add(ScrolledWindow_Setting, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer21, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 10, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);
    MenuBar_MpcAsfTool = new wxMenuBar();
    SetMenuBar(MenuBar_MpcAsfTool);

    Connect(ID_SLIDER_FRAME,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MpcAsfTool::OnSlider_FrameCmdScroll);
    Connect(ID_SPINCTRL11,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_Frame_GotoChange);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnButton_DeleteCurrentFrameClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnButton_UnDeleteClick);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_GlobalWidthChange);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_GlobalHeightChange);
    Connect(ID_SPINCTRL12,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_DirectionChange);
    Connect(ID_SPINCTRL4,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_BottomChange);
    Connect(ID_SLIDER1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&MpcAsfTool::OnSlider_IntervalCmdScroll);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnCheckBox_ShowShdClick);
    Connect(ID_SPINCTRL3,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_LeftChange);
    Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&MpcAsfTool::OnRadioButton_NoShadowSelect);
    Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&MpcAsfTool::OnRadioButton_MpcShadowSelect);
    Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&MpcAsfTool::OnRadioButton_AsfShadowSelect);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnCheckBox_LockFrameClick);
    Connect(ID_SPINCTRL5,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_SunXChange);
    Connect(ID_SPINCTRL6,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_SunYChange);
    Connect(ID_SPINCTRL7,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_ShadowXChange);
    Connect(ID_SPINCTRL8,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_ShadowYChange);
    Connect(ID_SPINCTRL10,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_ShadowAlphaChange);
    Connect(ID_COLOURPICKERCTRL1,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&MpcAsfTool::OnColourPickerCtrl1ColourChanged);
    Connect(ID_SPINCTRL9,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_AlphaMaskChange);
    //*)

    ischanged = false;
    currentframeindex = 1;


    wxMenu *menu_file = new wxMenu;
    menu_file->Append(wxID_NEW, _("新建...\tCtrl+N"));
    menu_file->Append(wxID_OPEN, _("打开...\tCtrl+O"));
    menu_file->Append(wxID_SAVE, _("保存\tCtrl+S"));
    menu_file->Append(wxID_SAVEAS, _("另存为...\tCtrl+Alt+S"));
    menu_file->Append(ID_EXPORT_TO_GIF, _("导出为 GIF..."));
    menu_file->Append(ID_EXPORT_TO_PNG, _("导出为 PNG..."));
    menu_file->Append(wxID_EXIT, _("退出\tAlt+f4"));
    menu_file->Enable(wxID_SAVE, false);
    wxMenu *menu_help = new wxMenu;
    menu_help->Append(wxID_HELP,  _("帮助\tF1"));
    menu_help->Append(wxID_ABOUT, _("关于..."));


    MenuBar_MpcAsfTool->Append(menu_file, _("文件(&F)"));
    MenuBar_MpcAsfTool->Append(menu_help, _("帮助(&H)"));

    ScrolledWindow_Setting->SetScrollRate(0, 20);
    ScrolledWindow_BmpShow->SetScrollRate(20, 20);

    this->SetSize(900, 700);
    this->SetSizeHints(wxSize(800, 400));

    manager.Init();
}

MpcAsfTool::~MpcAsfTool()
{
    //(*Destroy(MpcAsfTool)
    //*)
}
void MpcAsfTool::OnSize(wxSizeEvent &event)
{
    if(ScrolledWindow_BmpShow != NULL && this->IsShown())
    {
        ScrolledWindow_BmpShow->Refresh();
    }
    event.Skip();

}
void MpcAsfTool::OnClose(wxCloseEvent &event)
{
    Destroy();
}
void MpcAsfTool::OnNew(wxCommandEvent &event)
{
    if(!ChangeSaved()) return;

    manager.ReNew();
    InitFromManager();
    currentfile.clear();
    StaticText_CurrentFile->SetLabel(wxEmptyString);

    SetStateChange(false);
}
void MpcAsfTool::OnFileOpen(wxCommandEvent &event)
{
    if(!ChangeSaved()) return;

    wxFileDialog filedlg(this, _("选择MPC ASF文件"), _(""), _(""),
                         _("MPC ASF(*.mpc,*.asf)|*.mpc;*.asf|MPC(*.mpc)|*.mpc|ASF(*.asf)|*.asf"),
                         wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(filedlg.ShowModal() == wxID_OK)
    {
        manager.ReNew();
        InitFromManager();
        SetStateChange(false);
        currentfile = wxEmptyString;
        StaticText_CurrentFile->SetLabel(currentfile);

        if(!manager.OpenFile(filedlg.GetPath()))
        {
            wxMessageBox(_("文件打开失败"), _("消息"));
            return;
        }
        currentfile = filedlg.GetPath();
        StaticText_CurrentFile->SetLabel(currentfile);
        currentframeindex = 1;
        InitFromManager();
    }
}
void MpcAsfTool::OnFileSave(wxCommandEvent &event)
{
    SaveFile();
}
void MpcAsfTool::OnFileSaveAs(wxCommandEvent &event)
{
    SaveFile(false);
}
void MpcAsfTool::OnExportToGif(wxCommandEvent &event)
{
    if (manager.GetFrameCounts() == 0)
    {
        wxMessageBox(_("啥也没有，不能导出啊！"), _("消息"), wxOK|wxICON_INFORMATION);
        return;
    }

    wxFileDialog filedlg(this, _("存为GIF文件"), _(""), _(""),
                         _("GIF(*.gif)|*.gif"),
                         wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(filedlg.ShowModal() == wxID_OK)
    {
        if(!manager.SaveToGif(filedlg.GetPath()))
        {
            wxMessageBox(_("存储失败"), _("错误"), wxOK|wxICON_ERROR);
            return;
        }
        else
        {
            wxMessageBox(_("完成！"), _("消息"), wxOK|wxICON_INFORMATION);
            return;
        }
    }
}
void MpcAsfTool::OnExportToPng(wxCommandEvent &event)
{
    if (manager.GetFrameCounts() == 0)
    {
        wxMessageBox(_("啥也没有，不能导出啊！"), _("消息"), wxOK|wxICON_INFORMATION);
        return;
    }

    wxDirDialog dirdlg(this, _("选择导出文件夹"), _(""));

    if(dirdlg.ShowModal() == wxID_OK)
    {
        ExportToImg predlg(this);

        if(!currentfile.IsEmpty())
        {
            predlg.SetNamePrix(wxFileName::FileName(currentfile).GetName());
        }

        if(predlg.ShowModal() == wxID_OK)
        {
            wxString pngpath;
            pngpath = dirdlg.GetPath();
            pngpath += wxFileName::GetPathSeparator();
            pngpath += predlg.GetNamePrefix();

            if(!manager.SaveToPng(pngpath))
            {
                wxMessageBox(_("存储失败"), _("错误"), wxOK|wxICON_ERROR);
                return;
            }
            else
            {
                wxMessageBox(_("完成！"), _("消息"), wxOK|wxICON_INFORMATION);
                return;
            }
        }
    }
}
void MpcAsfTool::OnExit(wxCommandEvent &event)
{
    Destroy();
}
void MpcAsfTool::OnHelp(wxCommandEvent &event)
{

}
void MpcAsfTool::OnAbout(wxCommandEvent &event)
{

}
void MpcAsfTool::OnButton1Click(wxCommandEvent& event)
{
    wxFileDialog filedlg(this, _("选择多个图片文件"), _(""), _(""),
                         _("图片文件(*.png,*gif,*bmp,*.jpg,*.tif,*.ico,*.psd)|*.png;*.gif;*.bmp;*.jpg;*.tif;*.ico;*.psd|\
PNG|*.png|GIF|*.gif|BMP|*.bmp|JPG|*.jpg|TIFF|*.tif|ICO|*.ico|PSD|*.psd|所有文件|*.*"),
                         wxFD_OPEN|wxFD_MULTIPLE|wxFD_FILE_MUST_EXIST);
    if(filedlg.ShowModal() == wxID_OK)
    {
        bool init = false;
        wxArrayString infiles;
        filedlg.GetPaths(infiles);

        if(manager.GetFrameCounts() == 0) init = true;

        DlgAddFrames arrange(this);
        arrange.InitListCtrl(infiles);

        if(arrange.ShowModal() == wxID_OK)
        {
            infiles.clear();
            infiles = arrange.GetArrangedFiles();
            wxArrayString errfiles = manager.AddFiles(infiles);
            if(!errfiles.IsEmpty())
            {
                wxString errstr = _("以下文件添加失败:\n\n");
                for(size_t i = 0; i < errfiles.GetCount(); i++)
                {
                    errstr += errfiles[i];
                    errstr += wxT("\n");
                }
                wxMessageBox(errstr, _("错误"), wxOK|wxICON_ERROR);
            }
            if(init)InitFromManager();
            RefreshFrameSlide();
            RefreshBmpShow();
            if(!infiles.IsEmpty()) SetStateChange(true);
        }
    }
}

void MpcAsfTool::OnColourPickerCtrl1ColourChanged(wxColourPickerEvent& event)
{
    manager.SetBaseColor(event.GetColour());
    RefreshBmpShow();
}
void MpcAsfTool::ReNew()
{
    manager.ReNew();
    manager.Init();
}
void MpcAsfTool::InitFromManager()
{
    currentframeindex = 1;

    Slider_Frame->Enable();
    SpinCtrl_Frame_Goto->Enable();
    Button_AddFrames->Enable();
    Button_DeleteCurrentFrame->Enable();
    Button_UnDelete->Enable();
    SpinCtrl_GlobalWidth->Enable();
    SpinCtrl_GlobalHeight->Enable();
    SpinCtrl_Direction->Enable();
    SpinCtrl_Bottom->Enable();
    Slider_Interval->Enable();
    CheckBox_ShowShd->Enable();
    SpinCtrl_Left->Enable();
    RadioButton_NoShadow->Enable();
    RadioButton_MpcShadow->Enable();
    RadioButton_AsfShadow->Enable();
    CheckBox_LockFrame->Enable();
    SpinCtrl_SunX->Enable();
    SpinCtrl_SunY->Enable();
    SpinCtrl_ShadowX->Enable();
    SpinCtrl_ShadowY->Enable();
    SpinCtrl_ShadowAlpha->Enable();
    ColourPickerCtrl_BaseColor->Enable();
    SpinCtrl_AlphaMask->Enable();

    SpinCtrl_GlobalWidth->SetValue((int)manager.GetGlobalWidth());
    SpinCtrl_GlobalHeight->SetValue((int)manager.GetGlobalHeight());
    SpinCtrl_Direction->SetValue((int)manager.GetDirection());
    SpinCtrl_Bottom->SetValue((int)manager.GetBottom());
    Slider_Interval->SetValue((int)manager.GetInterval());
    manager.SetShdIncluded(CheckBox_ShowShd->GetValue());
    SpinCtrl_Left->SetValue((int)manager.GetLeft());
    if(manager.IsMakeShadow())
    {
        if(manager.GetShadowType() == SHD_MPC)
        {
            RadioButton_MpcShadow->SetValue(true);
        }
        else if(manager.GetShadowType() == SHD_ASF)
        {
            RadioButton_AsfShadow->SetValue(true);
        }
        CheckBox_ShowShd->Enable(false);
        CheckBox_LockFrame->Enable();
        SpinCtrl_SunX->Enable();
        SpinCtrl_SunY->Enable();
        SpinCtrl_ShadowX->Enable();
        SpinCtrl_ShadowY->Enable();
        SpinCtrl_ShadowAlpha->Enable();
    }
    else
    {
        CheckBox_ShowShd->Enable();
        RadioButton_NoShadow->SetValue(true);
        CheckBox_LockFrame->Enable(false);
        SpinCtrl_SunX->Enable(false);
        SpinCtrl_SunY->Enable(false);
        SpinCtrl_ShadowX->Enable(false);
        SpinCtrl_ShadowY->Enable(false);
        SpinCtrl_ShadowAlpha->Enable(false);
    }
    SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
    SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
    SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
    SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
    SpinCtrl_ShadowAlpha->SetValue((int)manager.GetShadowAlpha());
    SpinCtrl_AlphaMask->SetValue((int)manager.GetAlphaMask());
    Slider_Frame->SetMax((int)manager.GetFrameCounts());
    Slider_Frame->SetValue(1);

    manager.SetBaseColor(ColourPickerCtrl_BaseColor->GetColour());

    StaticText_Interval->SetLabel(wxString::Format(wxT("%ld"), manager.GetInterval()));
    StaticText_Frame_Sum->SetLabel(wxString::Format(wxT("%ld"), manager.GetFrameCounts()));
    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), 1));

    if(manager.GetFrameCounts() != 0)
    {
        wxImage img;
        img = manager.GetUndeletedGlobalizedImage(0);
        if(img.IsOk())
        {
            StaticBitmap_Show->SetBitmap(wxBitmap(img));
            ScrolledWindow_BmpShow->SetVirtualSize(wxSize(img.GetWidth(), img.GetHeight()));
            ScrolledWindow_BmpShow->Refresh();
        }
    }
    else
    {
        StaticBitmap_Show->SetBitmap(wxNullBitmap);
        ScrolledWindow_BmpShow->SetVirtualSize(wxSize(5, 5));
        ScrolledWindow_BmpShow->Refresh();
    }
}
void MpcAsfTool::SetStateChange(bool StateChange)
{
    if(StateChange)
    {
        ischanged = true;
        wxMenu *filemenu = MenuBar_MpcAsfTool->GetMenu(0);
        filemenu->Enable(wxID_SAVE, true);
    }
    else
    {
        ischanged = false;
        wxMenu *filemenu = MenuBar_MpcAsfTool->GetMenu(0);
        filemenu->Enable(wxID_SAVE, false);
    }
}
bool MpcAsfTool::SaveFile(bool CurrentFile)
{
    if(manager.GetFrameCounts() == 0)
    {
        wxMessageBox(_("空文件不能保存！"), _("消息"), wxOK|wxICON_INFORMATION);
        return false;
    }

    if(currentfile.IsEmpty() || !CurrentFile)
    {

        wxString capital;
        if(!CurrentFile) capital = _("另存为");
        else capital = _("保存文件");

        wxFileDialog filedlg(this, capital, _(""), _(""),
                             _("MPC ASF(*.mpc,*.asf)|*.mpc;*.asf|MPC(*.mpc)|*.mpc|ASF(*.asf)|*.asf"),
                             wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if(filedlg.ShowModal() == wxID_OK)
        {
            wxString ext;
            ext = wxFileName::FileName(filedlg.GetPath()).GetExt();

            if(ext.CmpNoCase(wxT("asf")) == 0)
            {
                if(!manager.SaveToAsf(filedlg.GetPath()))
                {
                    wxMessageBox(_("文件保存失败！"), _("错误"), wxOK|wxICON_ERROR);
                    return false;
                }
            }
            else if(ext.CmpNoCase(wxT("mpc")) == 0)
            {
                if(!manager.SaveToMpc(filedlg.GetPath()))
                {
                    wxMessageBox(_("文件保存失败！"), _("错误"), wxOK|wxICON_ERROR);
                    return false;
                }
            }
            currentfile = filedlg.GetPath();
            StaticText_CurrentFile->SetLabel(currentfile);
            SetStateChange(false);
            manager.ReNew();
            manager.OpenFile(currentfile);
        }
        else return false;
    }
    else
    {
        wxString ext;
        ext = wxFileName::FileName(currentfile).GetExt();

        if(ext.CmpNoCase(wxT("asf")) == 0)
        {
            if(!manager.SaveToAsf(currentfile))
            {
                wxMessageBox(_("文件保存失败！"), _("错误"), wxOK|wxICON_ERROR);
                return false;
            }
        }
        else if(ext.CmpNoCase(wxT("mpc")) == 0)
        {
            if(!manager.SaveToMpc(currentfile))
            {
                wxMessageBox(_("文件保存失败！"), _("错误"), wxOK|wxICON_ERROR);
                return false;
            }
        }
        SetStateChange(false);
    }
    return true;
}
void MpcAsfTool::RefreshBmpShow()
{
    if(manager.GetFrameCounts() != 0)
    {
        wxImage img;
        img = manager.GetUndeletedGlobalizedImage((unsigned long )Slider_Frame->GetValue()-1);
        if(img.IsOk())
        {
            StaticBitmap_Show->SetBitmap(wxBitmap(img));
            ScrolledWindow_BmpShow->SetVirtualSize(wxSize(img.GetWidth(), img.GetHeight()));
            ScrolledWindow_BmpShow->Refresh();
        }
    }
    else
    {
        StaticBitmap_Show->SetBitmap(wxNullBitmap);
        ScrolledWindow_BmpShow->SetVirtualSize(wxSize(5, 5));
        ScrolledWindow_BmpShow->Refresh();
    }
}
void MpcAsfTool::RefreshFrameSlide()
{
    Slider_Frame->SetMax((int)manager.GetFrameCounts());
    Slider_Frame->SetValue(currentframeindex);

    StaticText_Frame_Sum->SetLabel(wxString::Format(wxT("%ld"), manager.GetFrameCounts()));
    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), currentframeindex));
}
void MpcAsfTool::SetLockState()
{
    unsigned long index = (unsigned long)(currentframeindex-1);
    if(!RadioButton_NoShadow->GetValue())
    {
        CheckBox_LockFrame->SetValue(manager.IsFrameLocked(index));

        if(CheckBox_LockFrame->GetValue())
        {
            SpinCtrl_SunX->SetValue((int)manager.GetFrameSunX(index));
            SpinCtrl_SunY->SetValue((int)manager.GetFrameSunY(index));
            SpinCtrl_ShadowX->SetValue((int)manager.GetFrameShadowX(index));
            SpinCtrl_ShadowY->SetValue((int)manager.GetFrameShadowY(index));
        }
        else
        {
            SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
            SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
            SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
            SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
        }
    }
}
bool MpcAsfTool::ChangeSaved()
{
    if(ischanged)
    {

        int ret;
        ret = wxMessageBox(_("文件已更改，是否保存？"), _("消息"), wxYES_NO|wxCANCEL|wxICON_QUESTION);
        if(ret == wxYES)
        {
            if(!SaveFile())
            {
                return false;
            }
        }
        else if(ret == wxCANCEL) return false;
        else if(ret == wxNO) return true;
        else return true;
    }
    else return true;

    return true;
}
void MpcAsfTool::OnSlider_FrameCmdScroll(wxScrollEvent& event)
{
    if(currentframeindex == Slider_Frame->GetValue()) return;
    else currentframeindex = Slider_Frame->GetValue();
    wxImage img;

    img = manager.GetUndeletedGlobalizedImage((unsigned long)Slider_Frame->GetValue()-1);
    if(img.IsOk())
    {
        StaticBitmap_Show->SetBitmap(wxBitmap(img));
        ScrolledWindow_BmpShow->SetVirtualSize(wxSize(img.GetWidth(), img.GetHeight()));
        ScrolledWindow_BmpShow->Refresh();
    }

    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), Slider_Frame->GetValue()));

    SetLockState();
}

void MpcAsfTool::OnSpinCtrl_Frame_GotoChange(wxSpinEvent& event)
{
    if(event.GetPosition() == 0) return;
    if(currentframeindex == event.GetPosition()) return;
    if(manager.GetFrameCounts() < (unsigned long)event.GetPosition()) return;

    currentframeindex = event.GetPosition();

    Slider_Frame->SetValue(event.GetPosition());
    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), event.GetPosition()));

    wxImage img;

    img = manager.GetUndeletedGlobalizedImage((unsigned long)event.GetPosition()-1);
    if(img.IsOk())
    {
        StaticBitmap_Show->SetBitmap(wxBitmap(img));
        ScrolledWindow_BmpShow->SetVirtualSize(wxSize(img.GetWidth(), img.GetHeight()));
        ScrolledWindow_BmpShow->Refresh();
    }

    SetLockState();
}

void MpcAsfTool::OnButton_DeleteCurrentFrameClick(wxCommandEvent& event)
{
    if(manager.DeleteFrame((unsigned long)Slider_Frame->GetValue()-1))
    {
        if(currentframeindex > 1)currentframeindex--;
        RefreshFrameSlide();
        RefreshBmpShow();
        SetStateChange(true);
        SetLockState();
    }
}

void MpcAsfTool::OnButton_UnDeleteClick(wxCommandEvent& event)
{
    if(manager.UnDeleteFrame())
    {
        if(currentframeindex < (int)manager.GetFrameCounts()) currentframeindex++;
        RefreshFrameSlide();
        RefreshBmpShow();
        SetStateChange(true);
        SetLockState();
    }

}

void MpcAsfTool::OnSpinCtrl_GlobalWidthChange(wxSpinEvent& event)
{
    SetStateChange(true);
    manager.SetGlobalWidth((long)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_GlobalHeightChange(wxSpinEvent& event)
{
    SetStateChange(true);
    manager.SetGlobalHeight((long)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_DirectionChange(wxSpinEvent& event)
{
    SetStateChange(true);
    manager.SetDirection((long)event.GetPosition());
}

void MpcAsfTool::OnSpinCtrl_BottomChange(wxSpinEvent& event)
{
    SetStateChange(true);
    manager.SetBottom((long)event.GetPosition());
}

void MpcAsfTool::OnSlider_IntervalCmdScroll(wxScrollEvent& event)
{
    SetStateChange(true);
    manager.SetInterval((unsigned long)event.GetPosition());
    StaticText_Interval->SetLabel(wxString::Format(wxT("%ld"), event.GetPosition()));
}

void MpcAsfTool::OnCheckBox_ShowShdClick(wxCommandEvent& event)
{
    manager.SetShdIncluded(event.IsChecked());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_LeftChange(wxSpinEvent& event)
{
    SetStateChange(true);
    manager.SetLeft((long)event.GetPosition());
}

void MpcAsfTool::OnRadioButton_NoShadowSelect(wxCommandEvent& event)
{
    SetStateChange(true);
    CheckBox_ShowShd->Enable();
    CheckBox_LockFrame->Enable(false);
    SpinCtrl_SunX->Enable(false);
    SpinCtrl_SunY->Enable(false);
    SpinCtrl_ShadowX->Enable(false);
    SpinCtrl_ShadowY->Enable(false);
    SpinCtrl_ShadowAlpha->Enable(false);
    manager.SetMakeShadow(false);
    RefreshBmpShow();
}

void MpcAsfTool::OnRadioButton_MpcShadowSelect(wxCommandEvent& event)
{
    // unsigned long index = (unsigned long)(currentframeindex -1);

    SetStateChange(true);
    CheckBox_ShowShd->Enable(false);
    CheckBox_LockFrame->Enable();
    SpinCtrl_SunX->Enable();
    SpinCtrl_SunY->Enable();
    SpinCtrl_ShadowX->Enable();
    SpinCtrl_ShadowY->Enable();
    SpinCtrl_ShadowAlpha->Enable();

    manager.SetMakeShadow(true, SHD_MPC);

    SetLockState();
    RefreshBmpShow();
}

void MpcAsfTool::OnRadioButton_AsfShadowSelect(wxCommandEvent& event)
{
    // unsigned long index = (unsigned long)(currentframeindex -1);

    SetStateChange(true);
    CheckBox_ShowShd->Enable(false);
    CheckBox_LockFrame->Enable();
    SpinCtrl_SunX->Enable();
    SpinCtrl_SunY->Enable();
    SpinCtrl_ShadowX->Enable();
    SpinCtrl_ShadowY->Enable();
    SpinCtrl_ShadowAlpha->Enable();

    manager.SetMakeShadow(true, SHD_ASF);

    SetLockState();
    RefreshBmpShow();
}

void MpcAsfTool::OnCheckBox_LockFrameClick(wxCommandEvent& event)
{
    unsigned long index = (unsigned long)(currentframeindex -1);

    SetStateChange(true);

    manager.SetFrameLock((unsigned long)index, event.IsChecked());

    if(event.IsChecked())
    {
        manager.SetFrameSunX(index, (long)SpinCtrl_SunX->GetValue());
        manager.SetFrameSunY(index, (long)SpinCtrl_SunY->GetValue());
        manager.SetFrameShadowX(index, (long)SpinCtrl_ShadowX->GetValue());
        manager.SetFrameShadowY(index, (long)SpinCtrl_ShadowY->GetValue());
    }
    else
    {
        SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
        SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
        SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
        SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
    }
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_SunXChange(wxSpinEvent& event)
{
    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameSunX(index, (long)event.GetPosition());
    }
    else
    {
        manager.SetGlobalSunx((long)event.GetPosition());
    }
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_SunYChange(wxSpinEvent& event)
{
    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameSunY(index, (long)event.GetPosition());
    }
    else
    {
        manager.SetGlobalSuny((long)event.GetPosition());
    }
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_ShadowXChange(wxSpinEvent& event)
{
    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameShadowX(index, (long)event.GetPosition());
    }
    else
    {
        manager.SetGlobalShadowx((long)event.GetPosition());
    }
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_ShadowYChange(wxSpinEvent& event)
{
    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameShadowY(index, (long)event.GetPosition());
    }
    else
    {
        manager.SetGlobalShadowy((long)event.GetPosition());
    }
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_ShadowAlphaChange(wxSpinEvent& event)
{
    manager.SetShadowAlpha((unsigned char)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_AlphaMaskChange(wxSpinEvent& event)
{
    manager.SetAlphaMask((unsigned char)event.GetPosition());
    RefreshBmpShow();
}
