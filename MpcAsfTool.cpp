#include "MpcAsfTool.h"
#include "DlgAddFrames.h"
#include "wx/filedlg.h"
#include "wx/dirdlg.h"
#include "wx/msgdlg.h"
#include "wx/filename.h"
#include "wx/log.h"
#include "ICO/jxqynyd.hpp"
#include "wx/stdpaths.h"
#include "wx/utils.h"
#include "wx/accel.h"
#include "wx/utils.h"

#include "ExportToImg.h"
#include "About.h"
#include "BatDialog.h"
#include "ResizeDialog.h"

//(*InternalHeaders(MpcAsfTool)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(MpcAsfTool)
const long MpcAsfTool::ID_STATICTEXT27 = wxNewId();
const long MpcAsfTool::ID_CHECKBOX5 = wxNewId();
const long MpcAsfTool::ID_STATICBITMAP1 = wxNewId();
const long MpcAsfTool::ID_SCROLLEDWINDOW2 = wxNewId();
const long MpcAsfTool::ID_BUTTON4 = wxNewId();
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
const long MpcAsfTool::ID_BUTTON5 = wxNewId();
const long MpcAsfTool::ID_STATICLINE11 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT28 = wxNewId();
const long MpcAsfTool::ID_STATICLINE12 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT29 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL13 = wxNewId();
const long MpcAsfTool::ID_STATICTEXT30 = wxNewId();
const long MpcAsfTool::ID_SPINCTRL14 = wxNewId();
const long MpcAsfTool::ID_CHECKBOX6 = wxNewId();
const long MpcAsfTool::ID_CHECKBOX4 = wxNewId();
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
const long MpcAsfTool::ID_CHECKBOX3 = wxNewId();
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
const long MpcAsfTool::ID_STATICTEXT31 = wxNewId();
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
    EVT_MENU(ID_BAT, MpcAsfTool::OnBat)
    EVT_MENU(wxID_EXIT, MpcAsfTool::OnExit)
    EVT_MENU(ID_FRAME_PREVIOUS, MpcAsfTool::PreviousFrame)
    EVT_MENU(ID_FRAME_NEXT, MpcAsfTool::NextFrame)
    EVT_MENU(ID_RESIZE, MpcAsfTool::Resize)
    EVT_MENU(ID_RESIZECURRENT, MpcAsfTool::ResizeCurrent)
    EVT_MENU(wxID_HELP, MpcAsfTool::OnHelp)
    EVT_MENU(wxID_ABOUT, MpcAsfTool::OnAbout)
    EVT_MENU(ID_TRAVESAL, MpcAsfTool::OnTravesal)
    EVT_MENU(ID_RETURN, MpcAsfTool::OnReturn)
    EVT_MENU(ID_BAT_PIC_CANCLE, MpcAsfTool::OnBatPicCancle)
    EVT_TIMER(ID_ANIMATE_TIMER, MpcAsfTool::OnAnimateTimer)
    EVT_COMMAND_SCROLL(MpcAsfTool::ID_SLIDER_FRAME, MpcAsfTool::OnSlider_FrameCmdScroll)
    EVT_COMMAND_SCROLL(MpcAsfTool::ID_SLIDER1, MpcAsfTool::OnSlider_IntervalCmdScroll)
END_EVENT_TABLE()


bool MpcAsfDrop::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
    if(mainfram == NULL) return false;

    if(mainfram->DragOpenFile(filenames)) return true;
    else return false;
}
MpcAsfTool::MpcAsfTool(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxImage showbmp(jxqynyd_xpm);
    showbmp.SetMaskColour(0xFC, 0xFE, 0xFC);
    showbmp.SetMask(true);
    wxBitmap showbitmap(showbmp);

    //(*Initialize(MpcAsfTool)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer29;
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer19;
    wxBoxSizer* BoxSizer20;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer21;
    wxBoxSizer* BoxSizer13;
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

    Create(parent, wxID_ANY, _T("MPC ASF 编辑器"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(978,737));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(232,256), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
    StaticText_CurrentFile = new wxStaticText(Panel1, ID_STATICTEXT27, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    BoxSizer28->Add(StaticText_CurrentFile, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_KeepSet = new wxCheckBox(Panel1, ID_CHECKBOX5, _T("保留设置"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox_KeepSet->SetValue(false);
    CheckBox_KeepSet->Disable();
    CheckBox_KeepSet->SetToolTip(_T("打开一个文件时，该文件使用当前设置，方便需要相同设置的多文件连续编辑。\n保留的有以下。\n基本参数：图片宽度、图片高度、垂直偏移\n图片偏移：都保留，对”辅助线“无影响\nMPC： 不影响\nASF：都保留\n影子：方案、全局影子设置、全局透明度\n优化：都保留，对”底色“无影响\n\n\n"));
    BoxSizer28->Add(CheckBox_KeepSet, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer28, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    ScrolledWindow_BmpShow = new wxScrolledWindow(Panel1, ID_SCROLLEDWINDOW2, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW2"));
    BoxSizer_ScrollWindow = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer_ScrollWindow->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticBitmap_Show = new wxStaticBitmap(ScrolledWindow_BmpShow, ID_STATICBITMAP1, showbitmap, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP1"));
    BoxSizer_ScrollWindow->Add(StaticBitmap_Show, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer_ScrollWindow->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    ScrolledWindow_BmpShow->SetSizer(BoxSizer_ScrollWindow);
    BoxSizer_ScrollWindow->Fit(ScrolledWindow_BmpShow);
    BoxSizer_ScrollWindow->SetSizeHints(ScrolledWindow_BmpShow);
    BoxSizer3->Add(ScrolledWindow_BmpShow, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    Button_Animate = new wxButton(Panel1, ID_BUTTON4, _T("播放"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button_Animate->Disable();
    BoxSizer19->Add(Button_Animate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer19, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    StaticText19 = new wxStaticText(Panel1, ID_STATICTEXT19, _T("帧："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    BoxSizer29->Add(StaticText19, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Frame_Sum = new wxStaticText(Panel1, ID_STATICTEXT20, _T("000"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    StaticText_Frame_Sum->SetToolTip(_T("总帧数"));
    BoxSizer29->Add(StaticText_Frame_Sum, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Frame = new wxSlider(Panel1, ID_SLIDER_FRAME, 0, 1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_FRAME"));
    Slider_Frame->Disable();
    BoxSizer29->Add(Slider_Frame, 8, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Frame_Cur = new wxStaticText(Panel1, ID_STATICTEXT21, _T("000"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StaticText_Frame_Cur->SetToolTip(_T("当前帧"));
    BoxSizer29->Add(StaticText_Frame_Cur, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer29, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT24, _T("跳到："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    BoxSizer5->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Frame_Goto = new wxSpinCtrl(Panel1, ID_SPINCTRL11, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 2147483646, 0, _T("ID_SPINCTRL11"));
    SpinCtrl_Frame_Goto->SetValue(_T("0"));
    SpinCtrl_Frame_Goto->Disable();
    BoxSizer5->Add(SpinCtrl_Frame_Goto, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_AddFrames = new wxButton(Panel1, ID_BUTTON1, _T("添加"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button_AddFrames->Disable();
    Button_AddFrames->SetToolTip(_T("添加帧"));
    BoxSizer5->Add(Button_AddFrames, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_DeleteCurrentFrame = new wxButton(Panel1, ID_BUTTON2, _T("删除"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button_DeleteCurrentFrame->Disable();
    Button_DeleteCurrentFrame->SetToolTip(_T("删除当前帧"));
    BoxSizer5->Add(Button_DeleteCurrentFrame, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_UnDelete = new wxButton(Panel1, ID_BUTTON3, _T("还原"), wxDefaultPosition, wxSize(40,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button_UnDelete->Disable();
    Button_UnDelete->SetToolTip(_T("还原上次删除"));
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
    StaticText7 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT7, _T("基本参数"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer7->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine2 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    BoxSizer7->Add(StaticLine2, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer7, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT1, _T("图片宽度："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer8->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_GlobalWidth = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 9999, 1, _T("ID_SPINCTRL1"));
    SpinCtrl_GlobalWidth->SetValue(_T("1"));
    SpinCtrl_GlobalWidth->Disable();
    BoxSizer8->Add(SpinCtrl_GlobalWidth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT2, _T("图片高度："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer8->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_GlobalHeight = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 9999, 1, _T("ID_SPINCTRL2"));
    SpinCtrl_GlobalHeight->SetValue(_T("1"));
    SpinCtrl_GlobalHeight->Disable();
    BoxSizer8->Add(SpinCtrl_GlobalHeight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT3, _T("方向个数："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer6->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Direction = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL12, _T("1"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 1, _T("ID_SPINCTRL12"));
    SpinCtrl_Direction->SetValue(_T("1"));
    SpinCtrl_Direction->Disable();
    BoxSizer6->Add(SpinCtrl_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT5, _T("垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer6->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Bottom = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL4"));
    SpinCtrl_Bottom->SetValue(_T("0"));
    SpinCtrl_Bottom->Disable();
    BoxSizer6->Add(SpinCtrl_Bottom, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    StaticText4 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT4, _T("时间间隔:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer9->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Interval = new wxSlider(ScrolledWindow_Setting, ID_SLIDER1, 100, 0, 200, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    Slider_Interval->Disable();
    BoxSizer9->Add(Slider_Interval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_Interval = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT6, _T("100"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer9->Add(StaticText_Interval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer9->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_AdjustPosition = new wxButton(ScrolledWindow_Setting, ID_BUTTON5, _T("坐标调整"), wxDefaultPosition, wxSize(80,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer9->Add(Button_AdjustPosition, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine11 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE11, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE11"));
    BoxSizer13->Add(StaticLine11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText24 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT28, _T("图片偏移"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
    BoxSizer13->Add(StaticText24, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine12 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE12, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE12"));
    BoxSizer13->Add(StaticLine12, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer13, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    StaticText25 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT29, _T("水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
    BoxSizer14->Add(StaticText25, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_PicOffX = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL13, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL13"));
    SpinCtrl_PicOffX->SetValue(_T("0"));
    SpinCtrl_PicOffX->Disable();
    BoxSizer14->Add(SpinCtrl_PicOffX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText26 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT30, _T("垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
    BoxSizer14->Add(StaticText26, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_PicOffY = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL14, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL14"));
    SpinCtrl_PicOffY->SetValue(_T("0"));
    SpinCtrl_PicOffY->Disable();
    BoxSizer14->Add(SpinCtrl_PicOffY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_LockPicOffset = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX6, _T("锁定"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox_LockPicOffset->SetValue(false);
    CheckBox_LockPicOffset->SetToolTip(_T("锁定当前帧"));
    BoxSizer14->Add(CheckBox_LockPicOffset, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_AssiLine = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX4, _T("辅助线"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox_AssiLine->SetValue(false);
    CheckBox_AssiLine->Disable();
    CheckBox_AssiLine->SetToolTip(_T("不影响最终的文件保存"));
    BoxSizer14->Add(CheckBox_AssiLine, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer14, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine3 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    BoxSizer10->Add(StaticLine3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT8, _T("MPC"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer10->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine4 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    BoxSizer10->Add(StaticLine4, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer10, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_ShowShd = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX1, _T("显示影子（SHD文件）"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox_ShowShd->SetValue(false);
    CheckBox_ShowShd->Disable();
    BoxSizer11->Add(CheckBox_ShowShd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine5 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE5, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
    BoxSizer12->Add(StaticLine5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT9, _T("ASF"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer12->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine6 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE6, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE6"));
    BoxSizer12->Add(StaticLine6, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer12, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    StaticText10 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT10, _T("水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
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
    BoxSizer4->Add(BoxSizer15, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine9 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE9, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE9"));
    BoxSizer24->Add(StaticLine9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText18 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT18, _T("影子"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    BoxSizer24->Add(StaticText18, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine10 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE10, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE10"));
    BoxSizer24->Add(StaticLine10, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer24, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    RadioButton_NoShadow = new wxRadioButton(ScrolledWindow_Setting, ID_RADIOBUTTON3, _T("不生成影子"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    RadioButton_NoShadow->SetValue(true);
    RadioButton_NoShadow->Disable();
    BoxSizer16->Add(RadioButton_NoShadow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_MpcShadow = new wxRadioButton(ScrolledWindow_Setting, ID_RADIOBUTTON1, _T("方案1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    RadioButton_MpcShadow->Disable();
    RadioButton_MpcShadow->SetToolTip(_T("适合剑二"));
    BoxSizer16->Add(RadioButton_MpcShadow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton_AsfShadow = new wxRadioButton(ScrolledWindow_Setting, ID_RADIOBUTTON2, _T("方案2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    RadioButton_AsfShadow->Disable();
    RadioButton_AsfShadow->SetToolTip(_T("适合月影、新剑"));
    BoxSizer16->Add(RadioButton_AsfShadow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_LockFrame = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX2, _T("编辑当前帧并锁定"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox_LockFrame->SetValue(false);
    CheckBox_LockFrame->Disable();
    BoxSizer16->Add(CheckBox_LockFrame, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_NextLock = new wxCheckBox(ScrolledWindow_Setting, ID_CHECKBOX3, _T("连续锁定"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox_NextLock->SetValue(false);
    CheckBox_NextLock->Disable();
    BoxSizer16->Add(CheckBox_NextLock, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer16, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    StaticText11 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT11, _T("光线水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer17->Add(StaticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_SunX = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL5"));
    SpinCtrl_SunX->SetValue(_T("0"));
    SpinCtrl_SunX->Disable();
    BoxSizer17->Add(SpinCtrl_SunX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT12, _T("光线垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    BoxSizer17->Add(StaticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_SunY = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL6"));
    SpinCtrl_SunY->SetValue(_T("0"));
    SpinCtrl_SunY->Disable();
    BoxSizer17->Add(SpinCtrl_SunY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer17, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
    StaticText14 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT14, _T("影子水平偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    BoxSizer18->Add(StaticText14, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_ShadowX = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL7"));
    SpinCtrl_ShadowX->SetValue(_T("0"));
    SpinCtrl_ShadowX->Disable();
    BoxSizer18->Add(SpinCtrl_ShadowX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText15 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT15, _T("影子垂直偏移："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    BoxSizer18->Add(StaticText15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_ShadowY = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL8"));
    SpinCtrl_ShadowY->SetValue(_T("0"));
    SpinCtrl_ShadowY->Disable();
    BoxSizer18->Add(SpinCtrl_ShadowY, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer18, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer27 = new wxBoxSizer(wxHORIZONTAL);
    StaticText23 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT23, _T("全局透明度：    "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    StaticText23->SetToolTip(_T("对SHD文件无效，对ASF、PNG等文件有效"));
    BoxSizer27->Add(StaticText23, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_ShadowAlpha = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL10, _T("120"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 120, _T("ID_SPINCTRL10"));
    SpinCtrl_ShadowAlpha->SetValue(_T("120"));
    SpinCtrl_ShadowAlpha->Disable();
    BoxSizer27->Add(SpinCtrl_ShadowAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText21 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT26, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    BoxSizer27->Add(StaticText21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer27->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer27, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine7 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE7, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE7"));
    BoxSizer20->Add(StaticLine7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText16 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT16, _T("优化"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    BoxSizer20->Add(StaticText16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine8 = new wxStaticLine(ScrolledWindow_Setting, ID_STATICLINE8, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE8"));
    BoxSizer20->Add(StaticLine8, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer20, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    StaticText17 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT17, _T("底色："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    StaticText17->SetToolTip(_T("对有透明值的文件（ASF、PNG等)存为MPC、GIF时有效"));
    BoxSizer23->Add(StaticText17, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColourPickerCtrl_BaseColor = new wxColourPickerCtrl(ScrolledWindow_Setting, ID_COLOURPICKERCTRL1, wxColour(255,255,255), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    ColourPickerCtrl_BaseColor->Disable();
    BoxSizer23->Add(ColourPickerCtrl_BaseColor, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer23->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText22 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT22, _T("透明阈："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    StaticText22->SetToolTip(_T("对有透明值的文件（ASF、PNG等)有效"));
    BoxSizer23->Add(StaticText22, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_AlphaMask = new wxSpinCtrl(ScrolledWindow_Setting, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL9"));
    SpinCtrl_AlphaMask->SetValue(_T("0"));
    SpinCtrl_AlphaMask->Disable();
    BoxSizer23->Add(SpinCtrl_AlphaMask, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer23, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer25->Add(BoxSizer4, 9, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer26 = new wxBoxSizer(wxHORIZONTAL);
    StaticText27 = new wxStaticText(ScrolledWindow_Setting, ID_STATICTEXT31, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
    BoxSizer26->Add(StaticText27, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer25->Add(BoxSizer26, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnCheckBox_KeepSetClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnButton_AnimateClick);
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
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnButton_AdjustPositionClick);
    Connect(ID_SPINCTRL13,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_PicOffXChange);
    Connect(ID_SPINCTRL14,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&MpcAsfTool::OnSpinCtrl_PicOffYChange);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnCheckBox_LockPicOffsetClick);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&MpcAsfTool::OnCheckBox_AssiLineClick);
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
    batpiccancle = true;
    assiline = false;
    currentframeindex = 1;
    prevsunx = 0;
    prevsuny = 0;
    prevshdx = 0;
    prevshdy = 0;

    animatetimer.SetOwner(this, ID_ANIMATE_TIMER);
    animateindex = 0;
    isplay = false;

    wxAcceleratorEntry ace[4];
    ace[0].Set(wxACCEL_NORMAL, WXK_TAB, ID_TRAVESAL);
    ace[1].Set(wxACCEL_NORMAL, WXK_RETURN, ID_RETURN);
    ace[2].Set(wxACCEL_NORMAL, (int)'a', ID_FRAME_PREVIOUS);
    ace[3].Set(wxACCEL_NORMAL, (int)'d', ID_FRAME_NEXT);
    wxAcceleratorTable act(2,ace);
    SetAcceleratorTable(act);

    m_adjustPosDlg = new AdjustPositionDialog(this);

    MpcAsfDrop *droptag = new MpcAsfDrop(this);
    SetDropTarget(droptag);

    wxMenu *menu_file = new wxMenu;
    menu_file->Append(wxID_NEW, wxT("新建...\tCtrl+N"));
    menu_file->Append(wxID_OPEN, wxT("打开...\tCtrl+O"));
    menu_file->Append(wxID_SAVE, wxT("保存\tCtrl+S"));
    menu_file->Append(wxID_SAVEAS, wxT("另存为...\tCtrl+Alt+S"));
    menu_file->Append(ID_EXPORT_TO_GIF, wxT("导出为 GIF..."));
    menu_file->Append(ID_EXPORT_TO_PNG, wxT("导出为 PNG..."));
    menu_file->Append(ID_BAT, wxT("图片批量导出...\tCtrl+P"));
    menu_file->Append(wxID_EXIT, wxT("退出\tAlt+f4"));
    menu_file->Enable(wxID_SAVE, false);
    menu_file->Enable(wxID_SAVEAS, false);
    menu_file->Enable(ID_EXPORT_TO_GIF, false);
    menu_file->Enable(ID_EXPORT_TO_PNG, false);
    wxMenu *menu_frame = new wxMenu;
    menu_frame->Append(ID_FRAME_PREVIOUS, wxT("上一帧\tA"));
    menu_frame->Append(ID_FRAME_NEXT, wxT("下一帧\tD"));
    wxMenu *menu_process = new wxMenu;
    menu_process->Append(ID_RESIZE, wxT("缩放所有..."));
    menu_process->Append(ID_RESIZECURRENT, wxT("缩放当前帧..."));
    wxMenu *menu_help = new wxMenu;
    menu_help->Append(wxID_HELP,  wxT("帮助\tF1"));
    menu_help->Append(wxID_ABOUT, wxT("关于..."));
    wxMenu *menu_batpicconv = new wxMenu;
    menu_batpicconv->Append(ID_BAT_PIC_CANCLE, wxT("取消"));

    MenuBar_BatPicConv = new wxMenuBar();

    MenuBar_MpcAsfTool->Append(menu_file, wxT("文件(&F)"));
    MenuBar_MpcAsfTool->Append(menu_frame, wxT("帧(&I)"));
    MenuBar_MpcAsfTool->Append(menu_process, wxT("图像处理"));
    MenuBar_MpcAsfTool->Append(menu_help, wxT("帮助(&H)"));
    MenuBar_BatPicConv->Append(menu_batpicconv, wxT("批处理"));


    ScrolledWindow_Setting->SetScrollRate(0, 20);
    ScrolledWindow_BmpShow->SetScrollRate(20, 20);

    this->SetIcon(wxICON(aaaa));
    this->SetSize(1000, 710);
    this->SetSizeHints(wxSize(830, 400));

    //Tab Sequence
    InitTabSequence();

    //Pnaels
    m_fileExplorer = new FileExplorerPanel(this);
    m_fileExplorer->Show();

    manager.Init();
}

MpcAsfTool::~MpcAsfTool()
{
    //(*Destroy(MpcAsfTool)
    //*)
    if(m_adjustPosDlg != NULL) delete m_adjustPosDlg;
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
    if(!batpiccancle)
    {
        if(wxMessageBox(wxT("停止批量转换？"), wxT("消息"), wxOK|wxCANCEL) == wxOK)
        {
            batpiccancle = true;
        }
        else return;
    }

    ReNewFocus();

    if(!ChangeSaved()) return;

    Destroy();
}
void MpcAsfTool::OnNew(wxCommandEvent &event)
{
    ReNewFocus();

    if(!ChangeSaved()) return;
    prevsunx = 0;
    prevsuny = 0;
    prevshdx = 0;
    prevshdy = 0;

    EnableCtrl();
    InitGlobalShadowFromManager();
    if(CheckBox_KeepSet->IsChecked())
    {
        InitPrevShadowFromManagerGlobalShadow();
    }
    manager.ReNew();
    if(CheckBox_KeepSet->IsChecked())
    {
        InitToManager();
    }
    if(isplay)
    {
        StopAnimate();
        BeginAnimate();
    }
    InitFromManager();
    currentfile.clear();
    StaticText_CurrentFile->SetLabel(wxEmptyString);

    if(CheckBox_KeepSet->IsChecked())
        SetStateChange(true);
    else
        SetStateChange(false);
}
void MpcAsfTool::OnFileOpen(wxCommandEvent &event)
{
    ReNewFocus();

    if(!ChangeSaved()) return;

    wxFileDialog filedlg(this, wxT("选择MPC ASF SPR RPC文件"), wxT(""), wxT(""),
                         wxT("MPC ASF SPR RPC(*.mpc,*.asf,*.spr,*.rpc)|*.mpc;*.asf;*.spr;*.rpc|MPC(*.mpc)|*.mpc|ASF(*.asf)|*.asf|SPR(*.spr)|*.spr|RPC(*.rpc)|*.rpc"),
                         wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(filedlg.ShowModal() == wxID_OK)
    {
        OpenFile(filedlg.GetPath());
    }
}
bool MpcAsfTool::DragOpenFile(const wxArrayString &files)
{
    ReNewFocus();

    if(!ChangeSaved() || files.IsEmpty()) return false;

    return OpenFile(files[0]);
}
bool MpcAsfTool::OpenFile(const wxString path)
{
    bool res;

    prevsunx = 0;
    prevsuny = 0;
    prevshdx = 0;
    prevshdy = 0;

    InitGlobalShadowFromManager();
    if(CheckBox_KeepSet->IsChecked())
    {
        InitPrevShadowFromManagerGlobalShadow();
    }
    manager.ReNew();
    if(CheckBox_KeepSet->IsChecked())
    {
        InitToManager();
    }
    InitFromManager();
    currentfile = wxEmptyString;
    StaticText_CurrentFile->SetLabel(currentfile);
    SetStateChange(false);

    res = manager.OpenFile(path);
    if(isplay)
    {
        StopAnimate();
        BeginAnimate();
    }

    if(!res)
    {
        wxMessageBox(wxT("文件打开失败"), wxT("消息"));
        return false;
    }

    EnableCtrl();
    currentfile = path;
    StaticText_CurrentFile->SetLabel(currentfile);
    currentframeindex = 1;
    if(CheckBox_KeepSet->IsChecked())
    {
        InitToManager();
    }
    InitFromManager();

    return true;
}
void MpcAsfTool::OnFileSave(wxCommandEvent &event)
{
    ReNewFocus();

    SaveFile();
}
void MpcAsfTool::OnFileSaveAs(wxCommandEvent &event)
{
    ReNewFocus();

    SaveFile(false);
}
void MpcAsfTool::OnExportToGif(wxCommandEvent &event)
{
    ReNewFocus();

    if (manager.GetFrameCounts() == 0)
    {
        wxMessageBox(wxT("啥也没有，不能导出啊！"), wxT("消息"), wxOK|wxICON_INFORMATION);
        return;
    }

    wxFileDialog filedlg(this, wxT("存为GIF文件"), wxT(""), wxT(""),
                         wxT("GIF(*.gif)|*.gif"),
                         wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(filedlg.ShowModal() == wxID_OK)
    {
        if(!manager.SaveToGif(filedlg.GetPath()))
        {
            wxMessageBox(wxT("存储失败"), wxT("错误"), wxOK|wxICON_ERROR);
            return;
        }
        else
        {
            wxMessageBox(wxT("完成！"), wxT("消息"), wxOK|wxICON_INFORMATION);
            return;
        }
    }
}
void MpcAsfTool::OnExportToPng(wxCommandEvent &event)
{
    ReNewFocus();

    if (manager.GetFrameCounts() == 0)
    {
        wxMessageBox(wxT("啥也没有，不能导出啊！"), wxT("消息"), wxOK|wxICON_INFORMATION);
        return;
    }

    wxDirDialog dirdlg(this, wxT("选择导出文件夹"), wxT(""));

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
                wxMessageBox(wxT("存储失败"), wxT("错误"), wxOK|wxICON_ERROR);
                return;
            }
            else
            {
                wxMessageBox(wxT("完成！"), wxT("消息"), wxOK|wxICON_INFORMATION);
                return;
            }
        }
    }
}
void MpcAsfTool::OnBat(wxCommandEvent &event)
{
    BatDialog batdlg(this);

    if(batdlg.ShowModal() == wxID_OK)
    {
        wxRichTextCtrl *lctl = batdlg.GetListTextCtrl();
        int frameBegin = batdlg.GetFrameBegin();
        int frameEnd = batdlg.GetFrameEnd();
        wxArrayString files, errs;
        int filecounts;
        wxString filename,outpath,temp;
        WorkManager conv;

        wxDirDialog dirdlg(this, wxT("选择导出文件夹"), wxT(""));
        if(dirdlg.ShowModal() != wxID_OK) return;
        outpath = dirdlg.GetPath() + wxFileName::GetPathSeparator();

        filecounts = lctl->GetNumberOfLines();
        for(int i = 0; i < filecounts; i++)
        {
            temp = lctl->GetLineText((long)i);
            temp.Trim(true);
            temp.Trim(false);
            if(!temp.IsEmpty())
            {
                files.Add(temp);
            }
        }

		float ratio = batdlg.getScaleRatio();
        filecounts = (int)files.GetCount();
        if(filecounts != 0)
        {
            batpiccancle = false;

            wxString frmt = this->GetTitle();
            wxSize frms = this->GetSize();
            wxSize frmms = this->GetMinSize();
            wxSize frmcs = this->GetClientSize();
            this->SetSizeHints(wxSize(0,0),
                               wxSize(frms.GetWidth(), frms.GetHeight() - frmcs.GetHeight()));
            this->SetSize(frms.GetWidth(), frms.GetHeight() - frmcs.GetHeight());
            this->SetMenuBar(MenuBar_BatPicConv);
            for(int j = 0; j < filecounts; j++)
            {
                if(batpiccancle) break;

                this->SetTitle(frmt+wxString::Format(wxT(" - 正在转换: %d/%d"), filecounts, j));
                wxTheApp->Yield(true);
                conv.ReNew();
                conv.SetShdIncluded(batdlg.isShd());
                conv.SetBaseColor(batdlg.GetBaseColor());
                conv.SetAlphaMask(batdlg.GetAlphaMask());
                if(conv.OpenFile(files[j], frameBegin, frameEnd))
                {
                	if(ratio != 1)
					{
						ResizeAll(&conv,
								(int)(ratio*conv.GetGlobalWidth()),
								(int)(ratio*conv.GetGlobalHeight()));
					}

                    filename = wxFileName::FileName(files[j]).GetName();
                    if(batdlg.isGif())
                    {
                        if(!conv.SaveToGif(outpath+filename+wxT(".gif")))
                        {
                            errs.Add(files[j]);
                        }
                    }
                    else if(batdlg.isPng())
                    {
                        if(!conv.SaveToPng(outpath+filename))
                        {
                            errs.Add(files[j]);
                        }
                    }
                    else if(batdlg.isAsf())
					{
						if(!conv.SaveToAsf(outpath+filename+wxT(".asf")))
						{
							errs.Add(files[j]);
						}
					}
					else if(batdlg.isMpc())
					{
						if(!conv.SaveToMpc(outpath+filename+wxT(".mpc")))
						{
							errs.Add(files[j]);
						}
					}
                }
                else errs.Add(files[j]);
            }
            this->SetTitle(frmt);
            this->SetMenuBar(MenuBar_MpcAsfTool);
            this->SetSizeHints(frmms);
            this->SetSize(frms);
            batpiccancle = true;

            if(errs.GetCount() != 0)
            {
                wxString stre;
                stre = _T("以下文件失败：\n");
                for(size_t eri = 0; eri < errs.GetCount(); eri++)
                {
                    stre += errs[eri] + wxT("\n");
                }
                wxMessageBox(stre, wxT("消息"), wxOK|wxICON_ERROR);
            }
            else
            {
                if(!batpiccancle) wxMessageBox(_T("完成！"), _T("消息"), wxOK);
            }
        }
    }
}
void MpcAsfTool::OnExit(wxCommandEvent &event)
{
    if(!batpiccancle)
    {
        if(wxMessageBox(wxT("停止批量转换？"), wxT("消息"), wxOK|wxCANCEL) == wxOK)
        {
            batpiccancle = true;
        }
        else return;
    }

    ReNewFocus();

    if(!ChangeSaved()) return;
    batpiccancle = true;
    Destroy();
}
void MpcAsfTool::OnTravesal(wxCommandEvent &event)
{

    wxWindow *focw;
    focw = wxWindow::FindFocus();
    if(focw == NULL)return;

    if(!tabseq.SetNextFocuse(focw))
    {
        //no control focused,set second one
        tabseq.SetNextFocuse(tabseq.GetWindow(0));
    }
}
void MpcAsfTool::OnReturn(wxCommandEvent &event)
{
    wxWindow *focw;
    focw = wxWindow::FindFocus();

    if(focw)
    {
        this->SetFocus();
        focw->SetFocus();

        if(focw->IsKindOf(CLASSINFO(wxButton)))
        {
            wxButton *but = (wxButton*)focw;
            if(but->IsEnabled())
            {
                wxCommandEvent butevent(wxEVT_COMMAND_BUTTON_CLICKED, but->GetId());
                but->ProcessCommand(butevent);
            }
        }
        else if(focw->IsKindOf(CLASSINFO(wxSpinCtrl)))
        {
            wxSpinCtrl *spictl = (wxSpinCtrl*)focw;
            spictl->SetSelection(-1, -1);
        }
    }
}
void MpcAsfTool::OnBatPicCancle(wxCommandEvent &event)
{
    batpiccancle = true;
}
void MpcAsfTool::OnAnimateTimer(wxTimerEvent &event)
{
    SetBmpShow((animateindex++)%manager.GetFrameCounts(), assiline);
}
void MpcAsfTool::PreviousFrame(wxCommandEvent &event)
{
    ReNewFocus();

    if(currentframeindex > 1)
    {
        currentframeindex--;
        SetLockState();
        Slider_Frame->SetValue(currentframeindex);
        StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), currentframeindex));
        RefreshBmpShow();

    }

}
void MpcAsfTool::NextFrame(wxCommandEvent &event)
{
    ReNewFocus();

    if(currentframeindex < (int)manager.GetFrameCounts())
    {
        currentframeindex++;
        SetLockState();
        Slider_Frame->SetValue(currentframeindex);
        StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), currentframeindex));
        RefreshBmpShow();
    }

}

FILOCRGBQUAD* ResizeTo(FILOCRGBQUAD *data, int currentWidth, int currentHeight, int toWidth, int toHeight)
{
    FILOCRGBQUAD *scaledData = NULL;
    FIBITMAP *bitmap = FreeImage_Allocate(currentWidth, currentHeight, 32);
    if(bitmap)
    {
        FILOCRGBQUAD *bits = (FILOCRGBQUAD*)FreeImage_GetBits(bitmap);
        int length = currentWidth*currentHeight;
        for(int i = 0; i < length; i++)
            bits[i] = data[i];
        FIBITMAP *scaled = FreeImage_Rescale(bitmap, toWidth, toHeight, FILTER_BICUBIC);
        if(scaled)
        {
            scaledData = new FILOCRGBQUAD[toWidth*toHeight];
            bits = (FILOCRGBQUAD*)FreeImage_GetBits(scaled);
            length = toWidth*toHeight;
            for(int j = 0; j < length; j++)
            {
                scaledData[j] = bits[j];
            }
            FreeImage_Unload(scaled);
        }
        FreeImage_Unload(bitmap);
    }
    return scaledData;
}

void MpcAsfTool::ResizeFrame(WorkManager *manager, int i, int toWidth, int toHeight)
{
    FRAMERGBA *frame;
    FILOCRGBQUAD *data;
    frame = manager->GetFrameData(i);
    if(frame != NULL)
    {
        data = manager->GetUndeletedGlobalizedFrameData(i);
        if(data != NULL)
        {
            if(frame->data) delete[] frame->data;
            frame->data = ResizeTo(data, manager->GetGlobalWidth(), manager->GetGlobalHeight(), toWidth, toHeight);
            delete[] data;
        }
        data = manager->GetUndeletedGlobalizedShdFrameData(i);
        if(data != NULL)
        {
            if(frame->shddata) delete[] frame->shddata;
            frame->shddata = ResizeTo(data, manager->GetGlobalWidth(), manager->GetGlobalHeight(), toWidth, toHeight);
            delete[] data;
        }
        frame->width = toWidth;
        frame->height = toHeight;
        frame->ispicoffsetlocked = false;
        SetStateChange(true);
    }
}

void MpcAsfTool::ResizeAll(WorkManager *manager, int toWidth, int toHeight)
{
    int frameCount = manager->GetFrameCounts();

    for(int i = 0; i < frameCount; i++)
    {
        ResizeFrame(manager, i, toWidth, toHeight);
    }
    manager->SetGlobalWidth(toWidth);
    manager->SetGlobalHeight(toHeight);
}

void MpcAsfTool::Resize(wxCommandEvent& event)
{
    ResizeDialog dialog(this);
    dialog.SetCurrentWidth(manager.GetGlobalWidth());
    dialog.SetCurrentHeight(manager.GetGlobalHeight());
    if(dialog.ShowModal() == wxID_OK)
    {
        int toWidth = dialog.GetWidth();
        int toHeight = dialog.GetHeight();
        if(toWidth == manager.GetGlobalWidth() &&
			toHeight == manager.GetGlobalHeight())return;
        ResizeAll(&manager, toWidth, toHeight);
        SpinCtrl_GlobalWidth->SetValue(toWidth);
        SpinCtrl_GlobalHeight->SetValue(toHeight);
        RefreshBmpShow();
    }
}

void MpcAsfTool::ResizeCurrent(wxCommandEvent& event)
{
    ResizeDialog dialog(this);
    dialog.SetCurrentWidth(manager.GetGlobalWidth());
    dialog.SetCurrentHeight(manager.GetGlobalHeight());
    if(dialog.ShowModal() == wxID_OK)
    {
        ResizeFrame(&manager, currentframeindex - 1, dialog.GetWidth(), dialog.GetHeight());
        RefreshBmpShow();
    }
}

void MpcAsfTool::OnHelp(wxCommandEvent &event)
{
    wxString exepath, execmd;
    exepath = wxStandardPaths::Get().GetExecutablePath();
    exepath = wxFileName::FileName(exepath).GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
    //wxMessageBox(exepath);
    exepath += wxT("help.chm");
    execmd = wxT("hh \"") + exepath + wxT("\"");
    wxExecute(execmd);
}
void MpcAsfTool::OnAbout(wxCommandEvent &event)
{
    About abtdlg(this);
    abtdlg.ShowModal();
}
void MpcAsfTool::OnButton1Click(wxCommandEvent& event)
{
    wxFileDialog filedlg(this, wxT("选择多个图片文件"), wxT(""), wxT(""),
                         wxT("图片文件(*.spr,*.png,*gif,*bmp,*.jpg,*.tif,*.ico,*.psd)|*.spr;*.png;*.gif;*.bmp;*.jpg;*.tif;*.ico;*.psd|\
SPR(剑网、剑侠世界图片资源文件)|*.spr|PNG|*.png|GIF|*.gif|BMP|*.bmp|JPG|*.jpg|TIFF|*.tif|ICO|*.ico|PSD|*.psd|所有文件|*.*"),
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
                wxString errstr = wxT("以下文件添加失败:\n\n");
                for(size_t i = 0; i < errfiles.GetCount(); i++)
                {
                    errstr += errfiles[i];
                    errstr += wxT("\n");
                }
                wxMessageBox(errstr, wxT("错误"), wxOK|wxICON_ERROR);
            }
            if(init)InitFromManager();
            RefreshFrameSlide();
            RefreshBmpShow();
            if(isplay)
            {
                StopAnimate();
                BeginAnimate();
            }
            if(!infiles.IsEmpty()) SetStateChange(true);
        }
    }
}

void MpcAsfTool::OnColourPickerCtrl1ColourChanged(wxColourPickerEvent& event)
{
    SetStateChange(true);

    manager.SetBaseColor(event.GetColour());
    RefreshBmpShow();
}
void MpcAsfTool::ReNew()
{
    manager.ReNew();
    manager.Init();
}
void MpcAsfTool::EnableCtrl()
{
    wxMenu *filemenu = MenuBar_MpcAsfTool->GetMenu(0);
    filemenu->Enable(wxID_SAVEAS, true);
    filemenu->Enable(ID_EXPORT_TO_GIF, true);
    filemenu->Enable(ID_EXPORT_TO_PNG, true);

    CheckBox_KeepSet->Enable();
    Slider_Frame->Enable();
    SpinCtrl_Frame_Goto->Enable();
    Button_Animate->Enable();
    Button_AddFrames->Enable();
    Button_DeleteCurrentFrame->Enable();
    Button_UnDelete->Enable();
    SpinCtrl_GlobalWidth->Enable();
    SpinCtrl_GlobalHeight->Enable();
    SpinCtrl_Direction->Enable();
    SpinCtrl_Bottom->Enable();
    Slider_Interval->Enable();
    SpinCtrl_PicOffX->Enable();
    SpinCtrl_PicOffY->Enable();
    CheckBox_AssiLine->Enable();
    CheckBox_ShowShd->Enable();
    SpinCtrl_Left->Enable();
    RadioButton_NoShadow->Enable();
    RadioButton_MpcShadow->Enable();
    RadioButton_AsfShadow->Enable();
    CheckBox_LockFrame->Enable();
    CheckBox_NextLock->SetValue(false);
    if(CheckBox_LockFrame->GetValue())
    {
        CheckBox_NextLock->Enable();
    }
    else
    {
        CheckBox_NextLock->Enable(false);
    }
    SpinCtrl_SunX->Enable();
    SpinCtrl_SunY->Enable();
    SpinCtrl_ShadowX->Enable();
    SpinCtrl_ShadowY->Enable();
    SpinCtrl_ShadowAlpha->Enable();
    ColourPickerCtrl_BaseColor->Enable();
    SpinCtrl_AlphaMask->Enable();
}
void MpcAsfTool::InitFromManager()
{
    currentframeindex = 1;

    Slider_Frame->SetValue(0);
    SpinCtrl_GlobalWidth->SetValue((int)manager.GetGlobalWidth());
    SpinCtrl_GlobalHeight->SetValue((int)manager.GetGlobalHeight());
    SpinCtrl_Direction->SetValue((int)manager.GetDirection());
    SpinCtrl_Bottom->SetValue((int)manager.GetBottom());
    Slider_Interval->SetValue((int)manager.GetInterval());

    FRAMERGBA *frame = manager.GetFrameData(currentframeindex-1);
    if(frame && frame->ispicoffsetlocked)
	{
		CheckBox_LockPicOffset->SetValue(true);
		SpinCtrl_PicOffX->SetValue(frame->picoffx);
		SpinCtrl_PicOffY->SetValue(frame->picoffy);
	}
	else
	{
		CheckBox_LockPicOffset->SetValue(false);
		SpinCtrl_PicOffX->SetValue((int)manager.GetPicOffX());
		SpinCtrl_PicOffY->SetValue((int)manager.GetPicOffY());
	}

    manager.SetShdIncluded(CheckBox_ShowShd->GetValue());
    SpinCtrl_Left->SetValue((int)manager.GetLeft());
    CheckBox_LockFrame->SetValue(manager.IsFrameLocked(0));
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
        CheckBox_NextLock->SetValue(false);
        if(CheckBox_LockFrame->GetValue())
        {
            CheckBox_NextLock->Enable();

            SpinCtrl_SunX->SetValue((int)manager.GetFrameSunX(0));
            SpinCtrl_SunY->SetValue((int)manager.GetFrameSunY(0));
            SpinCtrl_ShadowX->SetValue((int)manager.GetFrameShadowX(0));
            SpinCtrl_ShadowY->SetValue((int)manager.GetFrameShadowY(0));
        }
        else
        {
            CheckBox_NextLock->Enable(false);

            SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
            SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
            SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
            SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
        }
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
        CheckBox_NextLock->SetValue(false);
        CheckBox_NextLock->Enable(false);
        SpinCtrl_SunX->Enable(false);
        SpinCtrl_SunY->Enable(false);
        SpinCtrl_ShadowX->Enable(false);
        SpinCtrl_ShadowY->Enable(false);
        SpinCtrl_ShadowAlpha->Enable(false);

        SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
        SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
        SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
        SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
    }
    SpinCtrl_ShadowAlpha->SetValue((int)manager.GetShadowAlpha());
    SpinCtrl_AlphaMask->SetValue((int)manager.GetAlphaMask());
    Slider_Frame->SetMax((int)manager.GetFrameCounts());
    Slider_Frame->SetValue(1);

    manager.SetBaseColor(ColourPickerCtrl_BaseColor->GetColour());

    StaticText_Interval->SetLabel(wxString::Format(wxT("%ld"), manager.GetInterval()));
    StaticText_Frame_Sum->SetLabel(wxString::Format(wxT("%ld"), manager.GetFrameCounts()));
    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), 1));

    RefreshBmpShow();
}
void MpcAsfTool::InitGlobalShadowFromManager()
{
    SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
    SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
    SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
    SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
}
void MpcAsfTool::InitPrevShadowFromManagerGlobalShadow()
{
    prevsunx = (int)manager.GetGlobalSunx();
    prevsuny = (int)manager.GetGlobalSuny();
    prevshdx = (int)manager.GetGlobalShadowx();
    prevshdy = (int)manager.GetGlobalShadowy();
}
void MpcAsfTool::InitToManager()
{
    manager.SetGlobalWidth((long)SpinCtrl_GlobalWidth->GetValue());
    manager.SetGlobalHeight((long)SpinCtrl_GlobalHeight->GetValue());
    manager.SetBottom((long)SpinCtrl_Bottom->GetValue());
    manager.SetPicOffX((long)SpinCtrl_PicOffX->GetValue());
    manager.SetPicOffY((long)SpinCtrl_PicOffY->GetValue());
    manager.SetLeft((long)SpinCtrl_Left->GetValue());
    if(RadioButton_MpcShadow->GetValue())
        manager.SetMakeShadow(true, SHD_MPC);
    else if(RadioButton_AsfShadow->GetValue())
        manager.SetMakeShadow(true, SHD_ASF);
    else
        manager.SetMakeShadow(false);
    manager.SetGlobalShadowx((long)SpinCtrl_ShadowX->GetValue());
    manager.SetGlobalShadowy((long)SpinCtrl_ShadowY->GetValue());
    manager.SetGlobalSunx((long)SpinCtrl_SunX->GetValue());
    manager.SetGlobalSuny((long)SpinCtrl_SunY->GetValue());
    manager.SetShadowAlpha((unsigned char)SpinCtrl_ShadowAlpha->GetValue());
    manager.SetBaseColor(ColourPickerCtrl_BaseColor->GetColour());
    manager.SetAlphaMask((unsigned char)SpinCtrl_AlphaMask->GetValue());
}
void MpcAsfTool::SetStateChange(bool StateChange)
{
    if(StateChange)
    {
        if(!currentfile.IsEmpty())
        {
            if(StaticText_CurrentFile->GetLabel().Cmp(wxT("*")+currentfile) != 0)
                StaticText_CurrentFile->SetLabel(wxT("*")+currentfile);
        }
        ischanged = true;
        wxMenu *filemenu = MenuBar_MpcAsfTool->GetMenu(0);
        filemenu->Enable(wxID_SAVE, true);
    }
    else
    {
        if(!currentfile.IsEmpty())
        {
            StaticText_CurrentFile->SetLabel(currentfile);
        }
        ischanged = false;
        wxMenu *filemenu = MenuBar_MpcAsfTool->GetMenu(0);
        filemenu->Enable(wxID_SAVE, false);
    }
}
bool MpcAsfTool::SaveFile(bool CurrentFile)
{
    if(manager.GetFrameCounts() == 0)
    {
        wxMessageBox(wxT("空文件不能保存！"), wxT("消息"), wxOK|wxICON_INFORMATION);
        return false;
    }

    if(currentfile.IsEmpty() || !CurrentFile)
    {

        wxString capital;
        if(!CurrentFile) capital = wxT("另存为");
        else capital = wxT("保存文件");

        wxFileDialog filedlg(this, capital, wxT(""), wxT(""),
                             wxT("MPC ASF(*.mpc,*.asf)|*.mpc;*.asf|MPC(*.mpc)|*.mpc|ASF(*.asf)|*.asf"),
                             wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if(filedlg.ShowModal() == wxID_OK)
        {
            wxString ext;
            ext = wxFileName::FileName(filedlg.GetPath()).GetExt();

            if(ext.CmpNoCase(wxT("asf")) == 0)
            {
                if(!manager.SaveToAsf(filedlg.GetPath()))
                {
                    wxMessageBox(wxT("文件保存失败！"), wxT("错误"), wxOK|wxICON_ERROR);
                    return false;
                }
            }
            else if(ext.CmpNoCase(wxT("mpc")) == 0)
            {
                if(!manager.SaveToMpc(filedlg.GetPath()))
                {
                    wxMessageBox(wxT("文件保存失败！"), wxT("错误"), wxOK|wxICON_ERROR);
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
                wxMessageBox(wxT("文件保存失败！"), wxT("错误"), wxOK|wxICON_ERROR);
                return false;
            }
        }
        else if(ext.CmpNoCase(wxT("mpc")) == 0)
        {
            if(!manager.SaveToMpc(currentfile))
            {
                wxMessageBox(wxT("文件保存失败！"), wxT("错误"), wxOK|wxICON_ERROR);
                return false;
            }
        }
        SetStateChange(false);
    }
    return true;
}
void MpcAsfTool::RefreshBmpShow()
{
    if(isplay && manager.GetFrameCounts() > 1)return;

    if(manager.GetFrameCounts() != 0)
    {
        SetBmpShow((unsigned long )Slider_Frame->GetValue()-1, assiline);
    }
    else
    {
        StaticBitmap_Show->SetBitmap(wxNullBitmap);
        ScrolledWindow_BmpShow->SetVirtualSize(wxSize(5, 5));
        ScrolledWindow_BmpShow->Refresh();
    }
}
void MpcAsfTool::SetBmpShow(unsigned long Index, bool AssiLine)
{
    wxImage img;
    img = manager.GetUndeletedGlobalizedImage((unsigned long )Index, AssiLine);
    if(img.IsOk())
    {
        StaticBitmap_Show->SetBitmap(wxBitmap(img));
        ScrolledWindow_BmpShow->SetVirtualSize(wxSize(img.GetWidth(), img.GetHeight()));
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
            CheckBox_NextLock->Enable();
        }
        else
        {
            if(CheckBox_NextLock->GetValue())
            {
                manager.SetFrameLock((unsigned long)index, true);
                CheckBox_LockFrame->SetValue(true);
                CheckBox_NextLock->Enable();

                manager.SetFrameSunX(index, (long)prevsunx);
                manager.SetFrameSunY(index, (long)prevsuny);
                manager.SetFrameShadowX(index, (long)prevshdx);
                manager.SetFrameShadowY(index, (long)prevshdy);
                SpinCtrl_SunX->SetValue(prevsunx);
                SpinCtrl_SunY->SetValue(prevsuny);
                SpinCtrl_ShadowX->SetValue(prevshdx);
                SpinCtrl_ShadowY->SetValue(prevshdy);
            }
            else
            {
                SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
                SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
                SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
                SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
                CheckBox_NextLock->Enable(false);
            }
        }
    }
    else
    {
        CheckBox_LockFrame->Enable(false);
        CheckBox_NextLock->SetValue(false);
        CheckBox_NextLock->Enable(false);
    }

    FRAMERGBA *temp = manager.GetUndeletedFrameData(currentframeindex - 1);
    if(temp)
    {
        CheckBox_LockPicOffset->SetValue(temp->ispicoffsetlocked);
        if(temp->ispicoffsetlocked)
        {
            SpinCtrl_PicOffX->SetValue(temp->picoffx);
            SpinCtrl_PicOffY->SetValue(temp->picoffy);
        }
        else
        {
            SpinCtrl_PicOffX->SetValue(manager.GetPicOffX());
            SpinCtrl_PicOffY->SetValue(manager.GetPicOffY());
        }
    }
}
void MpcAsfTool::InitTabSequence()
{
    tabseq.AddWindow(Slider_Frame);
    tabseq.AddWindow(SpinCtrl_Frame_Goto);
    tabseq.AddWindow(Button_AddFrames);
    tabseq.AddWindow(Button_DeleteCurrentFrame);
    tabseq.AddWindow(Button_UnDelete);
    tabseq.AddWindow(SpinCtrl_GlobalWidth);
    tabseq.AddWindow(SpinCtrl_GlobalHeight);
    tabseq.AddWindow(SpinCtrl_Direction);
    tabseq.AddWindow(SpinCtrl_Bottom);
    tabseq.AddWindow(Slider_Interval);
    tabseq.AddWindow(SpinCtrl_PicOffX);
    tabseq.AddWindow(SpinCtrl_PicOffY);
    tabseq.AddWindow(CheckBox_ShowShd, false);
    tabseq.AddWindow(SpinCtrl_Left);
    tabseq.AddWindow(RadioButton_NoShadow, false);
    tabseq.AddWindow(RadioButton_MpcShadow, false);
    tabseq.AddWindow(RadioButton_AsfShadow, false);
    tabseq.AddWindow(CheckBox_LockFrame, false);
    tabseq.AddWindow(CheckBox_NextLock, false);
    tabseq.AddWindow(SpinCtrl_SunX);
    tabseq.AddWindow(SpinCtrl_SunY);
    tabseq.AddWindow(SpinCtrl_ShadowX);
    tabseq.AddWindow(SpinCtrl_ShadowY);
    tabseq.AddWindow(SpinCtrl_ShadowAlpha);
    tabseq.AddWindow(ColourPickerCtrl_BaseColor, false);
    tabseq.AddWindow(SpinCtrl_AlphaMask);
}
void MpcAsfTool::ReNewFocus()
{
    wxWindow *focw;
    focw = wxWindow::FindFocus();
    if(focw == NULL)return;
    else
    {
        this->SetFocus();
        focw->SetFocus();
    }
}
bool MpcAsfTool::ChangeSaved()
{
    if(ischanged)
    {

        int ret;
        ret = wxMessageBox(wxT("文件已更改，是否保存？"), wxT("消息"), wxYES_NO|wxCANCEL|wxICON_QUESTION);
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

    SetLockState();

    RefreshBmpShow();

    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), Slider_Frame->GetValue()));
}

void MpcAsfTool::OnSpinCtrl_Frame_GotoChange(wxSpinEvent& event)
{
    if(event.GetPosition() == 0) return;
    if(currentframeindex == event.GetPosition()) return;
    if(manager.GetFrameCounts() < (unsigned long)event.GetPosition()) return;

    currentframeindex = event.GetPosition();

    SetLockState();

    Slider_Frame->SetValue(event.GetPosition());
    StaticText_Frame_Cur->SetLabel(wxString::Format(wxT("%ld"), event.GetPosition()));

    RefreshBmpShow();
}

void MpcAsfTool::OnButton_DeleteCurrentFrameClick(wxCommandEvent& event)
{
    if(manager.DeleteFrame((unsigned long)Slider_Frame->GetValue()-1))
    {
        if(currentframeindex > 1)currentframeindex--;
        SetLockState();
        RefreshFrameSlide();
        RefreshBmpShow();
        if(isplay)
        {
            StopAnimate();
            BeginAnimate();
        }
        SetStateChange(true);
    }
}

void MpcAsfTool::OnButton_UnDeleteClick(wxCommandEvent& event)
{
    if(manager.UnDeleteFrame())
    {
        if(currentframeindex < (int)manager.GetFrameCounts()) currentframeindex++;
        SetLockState();
        RefreshFrameSlide();
        RefreshBmpShow();
        if(isplay)
        {
            StopAnimate();
            BeginAnimate();
        }
        SetStateChange(true);
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
    if(isplay)
    {
        StopAnimate();
        BeginAnimate();
    }

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
    CheckBox_NextLock->SetValue(false);
    CheckBox_NextLock->Enable(false);
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
    CheckBox_NextLock->SetValue(false);
    if(CheckBox_LockFrame->GetValue())
    {
        CheckBox_NextLock->Enable();
    }
    else
    {
        CheckBox_NextLock->Enable(false);
    }
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
    CheckBox_NextLock->SetValue(false);
    if(CheckBox_LockFrame->GetValue())
    {
        CheckBox_NextLock->Enable();
    }
    else
    {
        CheckBox_NextLock->Enable(false);
    }
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
        manager.SetFrameSunX(index, (long)prevsunx);
        manager.SetFrameSunY(index, (long)prevsuny);
        manager.SetFrameShadowX(index, (long)prevshdx);
        manager.SetFrameShadowY(index, (long)prevshdy);
        SpinCtrl_SunX->SetValue(prevsunx);
        SpinCtrl_SunY->SetValue(prevsuny);
        SpinCtrl_ShadowX->SetValue(prevshdx);
        SpinCtrl_ShadowY->SetValue(prevshdy);
        CheckBox_NextLock->Enable();
    }
    else
    {
        SpinCtrl_SunX->SetValue((int)manager.GetGlobalSunx());
        SpinCtrl_SunY->SetValue((int)manager.GetGlobalSuny());
        SpinCtrl_ShadowX->SetValue((int)manager.GetGlobalShadowx());
        SpinCtrl_ShadowY->SetValue((int)manager.GetGlobalShadowy());
        CheckBox_NextLock->SetValue(false);
        CheckBox_NextLock->Enable(false);
    }
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_SunXChange(wxSpinEvent& event)
{
    SetStateChange(true);

    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameSunX(index, (long)event.GetPosition());
        CheckBox_NextLock->Enable();
    }
    else
    {
        manager.SetGlobalSunx((long)event.GetPosition());
        CheckBox_NextLock->Enable(false);
    }
    prevsunx = event.GetPosition();
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_SunYChange(wxSpinEvent& event)
{
    SetStateChange(true);

    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameSunY(index, (long)event.GetPosition());
        CheckBox_NextLock->Enable();
    }
    else
    {
        manager.SetGlobalSuny((long)event.GetPosition());
        CheckBox_NextLock->Enable(false);
    }
    prevsuny = event.GetPosition();
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_ShadowXChange(wxSpinEvent& event)
{
    SetStateChange(true);

    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameShadowX(index, (long)event.GetPosition());
        CheckBox_NextLock->Enable();
    }
    else
    {
        manager.SetGlobalShadowx((long)event.GetPosition());
        CheckBox_NextLock->Enable(false);
    }
    prevshdx = event.GetPosition();
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_ShadowYChange(wxSpinEvent& event)
{
    SetStateChange(true);

    unsigned long index = (unsigned long)(currentframeindex -1);

    if(CheckBox_LockFrame->GetValue())
    {
        manager.SetFrameShadowY(index, (long)event.GetPosition());
        CheckBox_NextLock->Enable();
    }
    else
    {
        manager.SetGlobalShadowy((long)event.GetPosition());
        CheckBox_NextLock->Enable(false);
    }
    prevshdy = event.GetPosition();
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_ShadowAlphaChange(wxSpinEvent& event)
{
    SetStateChange(true);

    manager.SetShadowAlpha((unsigned char)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_AlphaMaskChange(wxSpinEvent& event)
{
    SetStateChange(true);

    manager.SetAlphaMask((unsigned char)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_PicOffXChange(wxSpinEvent& event)
{
    SetStateChange(true);
    if(CheckBox_LockPicOffset->GetValue())
    {
        FRAMERGBA *temp = manager.GetUndeletedFrameData(currentframeindex - 1);
        if(temp)
        {
            temp->picoffx = event.GetPosition();
        }
    }
    else manager.SetPicOffX((long)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnSpinCtrl_PicOffYChange(wxSpinEvent& event)
{
    SetStateChange(true);
    if(CheckBox_LockPicOffset->GetValue())
    {
        FRAMERGBA *temp = manager.GetUndeletedFrameData(currentframeindex - 1);
        if(temp)
        {
            temp->picoffy = event.GetPosition();
        }
    }
    else manager.SetPicOffY((long)event.GetPosition());
    RefreshBmpShow();
}

void MpcAsfTool::OnCheckBox_AssiLineClick(wxCommandEvent& event)
{
    assiline = event.IsChecked();
    RefreshBmpShow();
}

void MpcAsfTool::OnCheckBox_KeepSetClick(wxCommandEvent& event)
{
}
void MpcAsfTool::BeginAnimate(bool ReNewIndex)
{
    if(ReNewIndex)animateindex = 0;

    isplay = true;
    if(manager.GetFrameCounts() > 1)
    {
        animatetimer.Start((int)manager.GetInterval());
    }
}
void MpcAsfTool::StopAnimate(bool ReNewIndex)
{
    if(ReNewIndex)animateindex = 0;

    isplay = false;
    animatetimer.Stop();
}
void MpcAsfTool::OnButton_AnimateClick(wxCommandEvent& event)
{
    if(isplay)
    {
        Button_Animate->SetLabel(wxT("播放"));
        StopAnimate(true);
        RefreshBmpShow();
    }
    else
    {
        Button_Animate->SetLabel(wxT("停止"));
        BeginAnimate(true);
    }
}

void MpcAsfTool::OnButton_AdjustPositionClick(wxCommandEvent& event)
{
    m_adjustPosDlg->Center();
    m_adjustPosDlg->AssignValue(SpinCtrl_Left->GetValue(),
                                SpinCtrl_Bottom->GetValue(),
                                SpinCtrl_PicOffX->GetValue(),
                                SpinCtrl_PicOffY->GetValue(),
                                CheckBox_LockPicOffset->GetValue());
    m_adjustPosDlg->SetShowImage(manager.GetUndeletedGlobalizedImage(Slider_Frame->GetValue()-1));
    if(m_adjustPosDlg->ShowModal() == wxID_OK)
    {
        SpinCtrl_Left->SetValue(m_adjustPosDlg->GetOffX());
        SpinCtrl_Bottom->SetValue(m_adjustPosDlg->GetOffY());

        FRAMERGBA *temp = manager.GetUndeletedFrameData(currentframeindex - 1);
        if(m_adjustPosDlg->IsLockCurrentFrame())
        {
            if(temp)
            {
                temp->picoffx = m_adjustPosDlg->GetPicX();
                temp->picoffy = m_adjustPosDlg->GetPicY();
                temp->ispicoffsetlocked = true;
            }
            CheckBox_LockPicOffset->SetValue(true);
        }
        else
        {
            if(temp)
            {
                temp->ispicoffsetlocked = true;
            }
            manager.SetPicOffX(m_adjustPosDlg->GetPicX());
            manager.SetPicOffY(m_adjustPosDlg->GetPicY());
            CheckBox_LockPicOffset->SetValue(false);
        }
        SpinCtrl_PicOffX->SetValue(m_adjustPosDlg->GetPicX());
        SpinCtrl_PicOffY->SetValue(m_adjustPosDlg->GetPicY());

        manager.SetLeft(m_adjustPosDlg->GetOffX());
        manager.SetBottom(m_adjustPosDlg->GetOffY());
        SetStateChange(true);
        RefreshBmpShow();
    }
}

void MpcAsfTool::OnCheckBox_LockPicOffsetClick(wxCommandEvent& event)
{
    SetStateChange(true);
    FRAMERGBA *temp = manager.GetUndeletedFrameData(currentframeindex - 1);
    if(temp)
    {
        temp->ispicoffsetlocked = event.IsChecked();
        if(event.IsChecked())
        {
            SpinCtrl_PicOffX->SetValue(temp->picoffx);
            SpinCtrl_PicOffY->SetValue(temp->picoffy);
        }
        else
        {
            SpinCtrl_PicOffX->SetValue(manager.GetPicOffX());
            SpinCtrl_PicOffY->SetValue(manager.GetPicOffY());
        }
    }
    RefreshBmpShow();
}

void FileExplorerPanel::OnFilterChange(wxCommandEvent& event)
{
	switch(event.GetSelection())
	{
	case -1:
	case 0:
		m_genericDirCtrl1->SetFilterIndex(0);
		break;
	default:
		m_genericDirCtrl1->SetFilterIndex(event.GetSelection());
		break;
	}
	wxString path = m_genericDirCtrl1->GetPath();
	m_genericDirCtrl1->ReCreateTree();
	m_genericDirCtrl1->ExpandPath(path);
}

void FileExplorerPanel::OnTreeItemActivated(wxTreeEvent& event)
{
	event.Skip();
	wxString path = m_genericDirCtrl1->GetPath();
	if(!wxFileName(path).IsDir())
	{
        m_parent->OpenFile(path);
	}
}

