#ifndef ABOUT_H
#define ABOUT_H

//(*Headers(About)
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/hyperlink.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class About: public wxDialog
{
	public:

		About(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~About();

	private:

		//(*Declarations(About)
		wxHyperlinkCtrl* HyperlinkCtrl2;
		wxHyperlinkCtrl* HyperlinkCtrl3;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxStaticBitmap* StaticBitmap1;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxHyperlinkCtrl* HyperlinkCtrl1;
		wxHyperlinkCtrl* HyperlinkCtrl_MyWebPage;
		wxStaticText* StaticText5;
		wxButton* Button_OK;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(About)
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT6;
		static const long ID_HYPERLINKCTRL1;
		static const long ID_HYPERLINKCTRL2;
		static const long ID_HYPERLINKCTRL3;
		static const long ID_HYPERLINKCTRL4;
		static const long ID_PANEL1;
		//*)

	public:

		//(*Handlers(About)
		void OnButton_OKClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
