#include "About.h"
#include "ICO/about.hpp"

//(*InternalHeaders(About)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(About)
const long About::ID_STATICBITMAP1 = wxNewId();
const long About::ID_STATICTEXT2 = wxNewId();
const long About::ID_STATICTEXT1 = wxNewId();
const long About::ID_STATICTEXT3 = wxNewId();
const long About::ID_STATICTEXT4 = wxNewId();
const long About::ID_STATICTEXT5 = wxNewId();
const long About::ID_BUTTON1 = wxNewId();
const long About::ID_STATICTEXT6 = wxNewId();
const long About::ID_HYPERLINKCTRL1 = wxNewId();
const long About::ID_HYPERLINKCTRL2 = wxNewId();
const long About::ID_HYPERLINKCTRL3 = wxNewId();
const long About::ID_HYPERLINKCTRL4 = wxNewId();
const long About::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(About,wxDialog)
	//(*EventTable(About)
	//*)
END_EVENT_TABLE()

About::About(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxImage showbmp(jxqynys_xpm);
    showbmp.SetMaskColour(0xFC, 0xFE, 0xFC);
    showbmp.SetMask(true);
    wxBitmap showbitmap(showbmp);

	//(*Initialize(About)
	Create(parent, wxID_ANY, _T("关于"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(394,197));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(0,0), wxSize(400,200), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Panel1->SetBackgroundColour(wxColour(202,209,247));
	StaticBitmap1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, showbitmap, wxPoint(250,50), wxSize(96,96), wxNO_BORDER, _T("ID_STATICBITMAP1"));
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _T("MPC ASF 编辑器 V1.6.5"), wxPoint(130,24), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _T("GUI Framework："), wxPoint(55,60), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _T("图片解码库："), wxPoint(55,85), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _T("程序："), wxPoint(55,110), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _T("感谢："), wxPoint(55,135), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	Button_OK = new wxButton(Panel1, ID_BUTTON1, _T("不忍直视"), wxPoint(265,165), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _T("2014.11.19"), wxPoint(136,160), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	HyperlinkCtrl_MyWebPage = new wxHyperlinkCtrl(Panel1, ID_HYPERLINKCTRL1, _T("小试刀剑"), _T("http://hi.baidu.com/qndryqnqbmbbceq"), wxPoint(100,109), wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL1"));
	HyperlinkCtrl1 = new wxHyperlinkCtrl(Panel1, ID_HYPERLINKCTRL2, _T("Upwinded"), _T("http://tieba.baidu.com/p/2279039886"), wxPoint(100,134), wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL2"));
	HyperlinkCtrl2 = new wxHyperlinkCtrl(Panel1, ID_HYPERLINKCTRL3, _T("FreeImage"), _T("http://sourceforge.net/projects/freeimage/"), wxPoint(138,84), wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL3"));
	HyperlinkCtrl3 = new wxHyperlinkCtrl(Panel1, ID_HYPERLINKCTRL4, _T("wxWidgets"), _T("http://www.wxwidgets.org/"), wxPoint(150,59), wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL4"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&About::OnButton_OKClick);
	//*)
	this->Center();
}

About::~About()
{
	//(*Destroy(About)
	//*)
}


void About::OnButton_OKClick(wxCommandEvent& event)
{
    EndModal(wxID_OK);
}
