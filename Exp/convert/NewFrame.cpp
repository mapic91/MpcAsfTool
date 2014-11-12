#include <cstdio>

#include "NewFrame.h"
#include "MpctoGif.hpp"
#include "AsftoPic.hpp"
#include "FreeImage.h"
#include "GifData.hpp"


#include "wx/msgdlg.h"
#include "wx/image.h"
#include "wx/bitmap.h"
#include "wx/mstream.h"
#include "wx/wx.h"
#include "wx/filename.h"

//(*InternalHeaders(NewFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)



//(*IdInit(NewFrame)
const long NewFrame::ID_STATICTEXT2 = wxNewId();
const long NewFrame::ID_SPINCTRL1 = wxNewId();
const long NewFrame::ID_STATICTEXT1 = wxNewId();
const long NewFrame::ID_SPINCTRL2 = wxNewId();
const long NewFrame::ID_STATICTEXT3 = wxNewId();
const long NewFrame::ID_SPINCTRL3 = wxNewId();
const long NewFrame::ID_STATICTEXT4 = wxNewId();
const long NewFrame::ID_SPINCTRL4 = wxNewId();
const long NewFrame::ID_STATICTEXT5 = wxNewId();
const long NewFrame::ID_SPINCTRL5 = wxNewId();
const long NewFrame::ID_STATICTEXT6 = wxNewId();
const long NewFrame::ID_SPINCTRL6 = wxNewId();
const long NewFrame::ID_STATICTEXT7 = wxNewId();
const long NewFrame::ID_SPINCTRL7 = wxNewId();
const long NewFrame::ID_STATICTEXT8 = wxNewId();
const long NewFrame::ID_SPINCTRL8 = wxNewId();
const long NewFrame::ID_STATICTEXT9 = wxNewId();
const long NewFrame::ID_SPINCTRL9 = wxNewId();
const long NewFrame::ID_BUTTON1 = wxNewId();
const long NewFrame::ID_BUTTON3 = wxNewId();
const long NewFrame::ID_BUTTON4 = wxNewId();
const long NewFrame::ID_BUTTON2 = wxNewId();
const long NewFrame::ID_BUTTON5 = wxNewId();
const long NewFrame::ID_BUTTON7 = wxNewId();
const long NewFrame::ID_BUTTON8 = wxNewId();
const long NewFrame::ID_BUTTON6 = wxNewId();
const long NewFrame::ID_CHECKBOX1 = wxNewId();
const long NewFrame::ID_CHECKBOX2 = wxNewId();
const long NewFrame::ID_COLOURPICKERCTRL1 = wxNewId();
const long NewFrame::ID_STATICBITMAP1 = wxNewId();
const long NewFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewFrame,wxFrame)
    //(*EventTable(NewFrame)
    //*)
END_EVENT_TABLE()

NewFrame::NewFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(NewFrame)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(962,475));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(232,216), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("TransparentMask:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer4->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_transmask = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 255, 0, _T("ID_SPINCTRL1"));
    SpinCtrl_transmask->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl_transmask, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Direction:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer4->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Direction = new wxSpinCtrl(Panel1, ID_SPINCTRL2, _T("8"), wxDefaultPosition, wxDefaultSize, 0, 0, 1073741823, 8, _T("ID_SPINCTRL2"));
    SpinCtrl_Direction->SetValue(_T("8"));
    BoxSizer4->Add(SpinCtrl_Direction, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Interval:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer4->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Interval = new wxSpinCtrl(Panel1, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL3"));
    SpinCtrl_Interval->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl_Interval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Bottom:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer4->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Buttom = new wxSpinCtrl(Panel1, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -1073741823, 1073741823, 0, _T("ID_SPINCTRL4"));
    SpinCtrl_Buttom->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl_Buttom, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Left:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer4->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Left = new wxSpinCtrl(Panel1, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -1073741823, 1073741823, 0, _T("ID_SPINCTRL5"));
    SpinCtrl_Left->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl_Left, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("SunX:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer5->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_SunX = new wxSpinCtrl(Panel1, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL6"));
    SpinCtrl_SunX->SetValue(_T("0"));
    BoxSizer5->Add(SpinCtrl_SunX, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(Panel1, ID_STATICTEXT7, _("SunY:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer5->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_SunY = new wxSpinCtrl(Panel1, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL7"));
    SpinCtrl_SunY->SetValue(_T("0"));
    BoxSizer5->Add(SpinCtrl_SunY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(Panel1, ID_STATICTEXT8, _("PosX:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer5->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_PosX = new wxSpinCtrl(Panel1, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL8"));
    SpinCtrl_PosX->SetValue(_T("0"));
    BoxSizer5->Add(SpinCtrl_PosX, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel1, ID_STATICTEXT9, _("PoxY:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer5->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_PosY = new wxSpinCtrl(Panel1, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, -2147483646, 2147483646, 0, _T("ID_SPINCTRL9"));
    SpinCtrl_PosY->SetValue(_T("0"));
    BoxSizer5->Add(SpinCtrl_PosY, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Button_Open = new wxButton(Panel1, ID_BUTTON1, _("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button_Open, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Previous = new wxButton(Panel1, ID_BUTTON3, _("Previous"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer3->Add(Button_Previous, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Next = new wxButton(Panel1, ID_BUTTON4, _("Next"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer3->Add(Button_Next, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_SaveGif = new wxButton(Panel1, ID_BUTTON2, _("SaveAsGif..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(Button_SaveGif, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_SavePng = new wxButton(Panel1, ID_BUTTON5, _("SaveAsPng..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer3->Add(Button_SavePng, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_SaveMpc = new wxButton(Panel1, ID_BUTTON7, _("SaveAsMpc..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer3->Add(Button_SaveMpc, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_SaveAsf = new wxButton(Panel1, ID_BUTTON8, _("SaveAsAsf..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer3->Add(Button_SaveAsf, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_test = new wxButton(Panel1, ID_BUTTON6, _("Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Button_test->Disable();
    BoxSizer3->Add(Button_test, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_SHD = new wxCheckBox(Panel1, ID_CHECKBOX1, _("SHD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox_SHD->SetValue(false);
    BoxSizer3->Add(CheckBox_SHD, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_MakeShow = new wxCheckBox(Panel1, ID_CHECKBOX2, _("MakeShodow"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox_MakeShow->SetValue(false);
    BoxSizer3->Add(CheckBox_MakeShow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ColPic_BacCol = new wxColourPickerCtrl(Panel1, ID_COLOURPICKERCTRL1, wxColour(255,255,255), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    BoxSizer3->Add(ColPic_BacCol, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBitmap_show = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_MISSING_IMAGE")),wxART_MAKE_CLIENT_ID_FROM_STR(wxString(_T("wxART_MESSAGE_BOX")))), wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFULL_REPAINT_ON_RESIZE, _T("ID_STATICBITMAP1"));
    BoxSizer2->Add(StaticBitmap_show, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);

    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&NewFrame::OnSpinCtrl_transmaskChange);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_OpenClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_PreviousClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_NextClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_SaveGifClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_SavePngClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_SaveMpcClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_SaveAsfClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewFrame::OnButton_testClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&NewFrame::OnCheckBox_SHDClick);
    //*)

    this->Refresh();

    currentframe = 0;
}

NewFrame::~NewFrame()
{
    //(*Destroy(NewFrame)
    //*)
}


void NewFrame::OnButton_OpenClick(wxCommandEvent& event)
{
    wxFileDialog filedlg(this, wxT("Select a MPC File"), wxT(""),
                         wxT(""), wxT("asf mpc file(*.mpc,*.asf)|*.mpc;*.asf"),
                         wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(filedlg.ShowModal() == wxID_OK)
    {
        FilePath = filedlg.GetPath();
        if(wxFileName::FileName(FilePath).GetExt().CmpNoCase(wxT("mpc")) == 0)
        {
            filetype = MPC;
            mpcdecode.ReadMpcFile(FilePath);
            framecounts = mpcdecode.GetFramesCounts();
            wxImage img = mpcdecode.GetFrameImage(0, CheckBox_SHD->IsChecked());
            //img.SaveFile(wxT("E:\\temp\\wxpage1.bmp"));
            StaticBitmap_show->SetBitmap(wxBitmap(img));
            currentframe = 0;
            this->SetTitle(wxString::Format(wxT("Frames:%ld, Current: %ld width-%d, height-%d"),
                                            framecounts, currentframe,
                                            img.GetWidth(), img.GetHeight()));
            SpinCtrl_Direction->SetValue((int)mpcdecode.GetDirection());
            SpinCtrl_Buttom->SetValue((int)mpcdecode.GetBottom());
            SpinCtrl_Interval->SetValue((int)mpcdecode.GetInterval());
            SpinCtrl_Left->Disable();
        }
        else if((wxFileName::FileName(FilePath).GetExt().CmpNoCase(wxT("asf")) == 0))
        {
            filetype = ASF;
            asfdecode.ReadAsfFile(FilePath);
            framecounts = asfdecode.GetFramesCounts();
            wxImage img = asfdecode.GetFrameImage(0, (unsigned char)SpinCtrl_transmask->GetValue());
            //img.SaveFile(wxT("E:\\temp\\wxpage1.bmp"));
            StaticBitmap_show->SetBitmap(wxBitmap(img));
            currentframe = 0;
            this->SetTitle(wxString::Format(wxT("Frames:%ld, Current: %ld width-%d, height-%d"),
                                            framecounts, currentframe,
                                            img.GetWidth(), img.GetHeight()));
            SpinCtrl_Direction->SetValue((int)asfdecode.GetDirection());
            SpinCtrl_Buttom->SetValue((int)asfdecode.GetBottom());
            SpinCtrl_Interval->SetValue((int)asfdecode.GetInterval());
            SpinCtrl_Left->SetValue((int)asfdecode.GetLeft());
            SpinCtrl_Left->Enable();
        }
        wxPoint bmppos = StaticBitmap_show->GetPosition();
        wxSize frmsize = this->GetSize();
        this->RefreshRect(wxRect(bmppos.x-5,bmppos.y-5,frmsize.GetWidth(), frmsize.GetHeight()));
    }
}


void NewFrame::OnButton_PreviousClick(wxCommandEvent& event)
{
    if(!FilePath.IsEmpty() && currentframe != 0)
    {
        currentframe--;
        wxImage img;
        if(filetype == MPC)img = mpcdecode.GetFrameImage(currentframe, CheckBox_SHD->IsChecked());
        else if(filetype == ASF)img = asfdecode.GetFrameImage(currentframe, (unsigned char)SpinCtrl_transmask->GetValue());
        StaticBitmap_show->SetBitmap(wxBitmap(img));
        this->SetTitle(wxString::Format(wxT("Frames:%ld, Current: %ld width-%d, height-%d"),
                                        framecounts, currentframe+1,
                                        img.GetWidth(), img.GetHeight()));
    }
    wxPoint bmppos = StaticBitmap_show->GetPosition();
    wxSize frmsize = this->GetSize();
    this->RefreshRect(wxRect(bmppos.x-5,bmppos.y-5,frmsize.GetWidth(), frmsize.GetHeight()));
}

void NewFrame::OnButton_NextClick(wxCommandEvent& event)
{
    if(!FilePath.IsEmpty() && currentframe+1 != framecounts)
    {
        currentframe++;
        wxImage img;
        if(filetype == MPC)img = mpcdecode.GetFrameImage(currentframe, CheckBox_SHD->IsChecked());
        else if(filetype == ASF)img = asfdecode.GetFrameImage(currentframe, (unsigned char)SpinCtrl_transmask->GetValue());
        StaticBitmap_show->SetBitmap(wxBitmap(img));
        this->SetTitle(wxString::Format(wxT("Frames:%ld, Current: %ld width-%d, height-%d"),
                                        framecounts, currentframe+1,
                                        img.GetWidth(), img.GetHeight()));
    }
    wxPoint bmppos = StaticBitmap_show->GetPosition();
    wxSize frmsize = this->GetSize();
    this->RefreshRect(wxRect(bmppos.x-5,bmppos.y-5,frmsize.GetWidth(), frmsize.GetHeight()));
}

void NewFrame::OnButton_SaveGifClick(wxCommandEvent& event)
{
    if(FilePath.IsEmpty()) return;

    wxFileDialog filedlg(this, wxT("Select a MPC File"), wxT(""),
                         wxT(""), wxT("gif file(*.gif)|*.gif"),
                         wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    long interval = 100;
    if(filedlg.ShowModal() == wxID_OK)
    {
        if(filetype == MPC)
        {
            interval = mpcdecode.GetInterval();

            bool shdinclude = CheckBox_SHD->IsChecked();
            CovMpctoPic covt(FilePath, filedlg.GetPath());
            covt.Save(CovMpctoPic::T_GIF, shdinclude);
        }
        else if(filetype == ASF)
        {
            interval = asfdecode.GetInterval();

            Palette_Colour backgroundcolor;
            backgroundcolor.Red = ColPic_BacCol->GetColour().Red();
            backgroundcolor.Green = ColPic_BacCol->GetColour().Green();
            backgroundcolor.Blue = ColPic_BacCol->GetColour().Blue();
            backgroundcolor.Alpha = 0x00;

            CovAsftoPic covt(FilePath, filedlg.GetPath());
            covt.Save(CovAsftoPic::T_GIF, &backgroundcolor, (unsigned char)SpinCtrl_transmask->GetValue());
        }
        GifData::FilePaletteLoctoGlb(filedlg.GetPath(), interval);
    }

}

void NewFrame::OnButton_SavePngClick(wxCommandEvent& event)
{
    if(FilePath.IsEmpty()) return;
    wxDirDialog pathdlg(this, wxT("Choose a directy"), wxT(""));
    if(pathdlg.ShowModal() == wxID_OK)
    {

        if(filetype == MPC)
        {
            bool shdinclude = CheckBox_SHD->IsChecked();
            CovMpctoPic covt(FilePath, pathdlg.GetPath());
            covt.Save(CovMpctoPic::T_PNG, shdinclude);
        }
        else if(filetype == ASF)
        {
            CovAsftoPic covt(FilePath, pathdlg.GetPath());
            covt.Save(CovAsftoPic::T_PNG);
        }
    }
}

void NewFrame::OnButton_testClick(wxCommandEvent& event)
{
    if(FilePath.IsEmpty()) return;

    wxFileDialog filedlg(this, wxT("Select a MPC File"), wxT(""),
                         wxT(""), wxT("gif file(*.gif)|*.gif"),
                         wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(filedlg.ShowModal() == wxID_OK)
    {
        unsigned long framessum, width, height,bufpos = 0;
        //bool res, istran;
        //BYTE *strdata = NULL, transidx;
        FILOCRGBQUAD *strdata = NULL;
        AsfDecode decode;
        BYTE* buffer;
        FIBITMAP *bmp, *bmp24, *bmp8;

        if(!decode.ReadAsfFile(FilePath)) return;
        framessum = decode.GetFramesCounts();
        width = decode.GetGlobleWidth();
        height = decode.GetGlobleHeight();

        strdata = decode.GetFIDecodedFrameData(0, NULL, NULL, AsfDecode::PIC_RGB);
        if(!strdata)return;

        buffer = (BYTE*)malloc(width*height*4);
        for(unsigned long i = 0; i < width*height; i++)
        {
            if(strdata[i].rgbReserved == 0)
            {
                buffer[bufpos++] = 0xFF;
                buffer[bufpos++] = 0xFF;
                buffer[bufpos++] = 0xFF;
                buffer[bufpos++] = 0xFF;
            }
            else
            {
                buffer[bufpos++] = 0x00;
                buffer[bufpos++] = 0x00;
                buffer[bufpos++] = 0x00;
                buffer[bufpos++] = 0x00;
            }
        }
        bmp = FreeImage_ConvertFromRawBits(buffer, width, height, width*4, 32,FI_RGBA_RED_MASK,
                                           FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);

        if(!bmp)return;

        bmp24 = FreeImage_ConvertTo24Bits(bmp);
        if(!bmp24) return;

        bmp8 = FreeImage_ColorQuantize(bmp24, FIQ_WUQUANT);
        if(!bmp8)return;

        FreeImage_SaveU(FIF_GIF, bmp8, filedlg.GetPath());
    }
}

void NewFrame::OnSpinCtrl_transmaskChange(wxSpinEvent& event)
{
    if(!FilePath.IsEmpty())
    {
        wxImage img;
        if(filetype == MPC)img = mpcdecode.GetFrameImage(currentframe, CheckBox_SHD->IsChecked());
        else if(filetype == ASF)img = asfdecode.GetFrameImage(currentframe, (unsigned char)SpinCtrl_transmask->GetValue());
        StaticBitmap_show->SetBitmap(wxBitmap(img));
        this->SetTitle(wxString::Format(wxT("Frames:%ld, Current: %ld width-%d, height-%d"),
                                        framecounts, currentframe+1,
                                        img.GetWidth(), img.GetHeight()));
    }
    wxPoint bmppos = StaticBitmap_show->GetPosition();
    wxSize frmsize = this->GetSize();
    this->RefreshRect(wxRect(bmppos.x-5,bmppos.y-5,frmsize.GetWidth(), frmsize.GetHeight()));
}

void NewFrame::OnCheckBox_SHDClick(wxCommandEvent& event)
{
    if(!FilePath.IsEmpty())
    {
        wxImage img;
        if(filetype == MPC)img = mpcdecode.GetFrameImage(currentframe, CheckBox_SHD->IsChecked());
        else if(filetype == ASF)img = asfdecode.GetFrameImage(currentframe, (unsigned char)SpinCtrl_transmask->GetValue());
        StaticBitmap_show->SetBitmap(wxBitmap(img));
        this->SetTitle(wxString::Format(wxT("Frames:%ld, Current: %ld width-%d, height-%d"),
                                        framecounts, currentframe+1,
                                        img.GetWidth(), img.GetHeight()));
    }
    wxPoint bmppos = StaticBitmap_show->GetPosition();
    wxSize frmsize = this->GetSize();
    this->RefreshRect(wxRect(bmppos.x-5,bmppos.y-5,frmsize.GetWidth(), frmsize.GetHeight()));
}

void NewFrame::OnButton_SaveMpcClick(wxCommandEvent& event)
{
    if(FilePath.IsEmpty()) return;

    wxFileDialog filedlg(this, wxT("Save a MPC File"), wxT(""),
                         wxT(""), wxT("mpc file(*.mpc)|*.mpc"),
                         wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(filedlg.ShowModal() == wxID_OK)
    {
        if(filetype == ASF)
        {
            Palette_Colour backgroundcolor;
            backgroundcolor.Red = ColPic_BacCol->GetColour().Red();
            backgroundcolor.Green = ColPic_BacCol->GetColour().Green();
            backgroundcolor.Blue = ColPic_BacCol->GetColour().Blue();
            backgroundcolor.Alpha = 0x00;

            CovAsftoPic covt(FilePath, filedlg.GetPath());
            covt.Save(CovAsftoPic::T_MPC, &backgroundcolor, (unsigned char)SpinCtrl_transmask->GetValue(),
                      (long)SpinCtrl_Direction->GetValue(), (long)SpinCtrl_Interval->GetValue(),
                      (long)SpinCtrl_Buttom->GetValue(), 0, CheckBox_MakeShow->IsChecked());
        }
        else if(filetype == MPC)
        {
            CovMpctoPic covt(FilePath, filedlg.GetPath());
            covt.Save(CovMpctoPic::T_MPC, CheckBox_SHD->IsChecked(),(long)SpinCtrl_Direction->GetValue(),
                      (long)SpinCtrl_Interval->GetValue(),(long)SpinCtrl_Buttom->GetValue(), 0, CheckBox_MakeShow->IsChecked());
        }
    }
}

void NewFrame::OnButton_SaveAsfClick(wxCommandEvent& event)
{
    if(FilePath.IsEmpty()) return;

    wxFileDialog filedlg(this, wxT("Save a ASF File"), wxT(""),
                         wxT(""), wxT("asf file(*.asf)|*.asf"),
                         wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(filedlg.ShowModal() == wxID_OK)
    {
        if(filetype == ASF)
        {
            CovAsftoPic covt(FilePath, filedlg.GetPath());
            covt.Save(CovAsftoPic::T_ASF, NULL, 0,
                      (long)SpinCtrl_Direction->GetValue(), (long)SpinCtrl_Interval->GetValue(),
                      (long)SpinCtrl_Buttom->GetValue(), (long)SpinCtrl_Left->GetValue(), CheckBox_MakeShow->IsChecked(),
                      (long)SpinCtrl_SunX->GetValue(), (long)SpinCtrl_SunY->GetValue(), (long)SpinCtrl_PosX->GetValue(),
                      (long)SpinCtrl_PosY->GetValue());
        }
        else if(filetype == MPC)
        {
            CovMpctoPic covt(FilePath, filedlg.GetPath());
            covt.Save(CovMpctoPic::T_ASF, CheckBox_SHD->IsChecked(),(long)SpinCtrl_Direction->GetValue(),
                      (long)SpinCtrl_Interval->GetValue(),(long)SpinCtrl_Buttom->GetValue(),
                      (long)SpinCtrl_Left->GetValue(), CheckBox_MakeShow->IsChecked(),
                      (long)SpinCtrl_SunX->GetValue(), (long)SpinCtrl_SunY->GetValue(), (long)SpinCtrl_PosX->GetValue(),
                      (long)SpinCtrl_PosY->GetValue());
        }
    }
}
