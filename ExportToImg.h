#ifndef EXPORTTOIMG_H
#define EXPORTTOIMG_H

//(*Headers(ExportToImg)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class ExportToImg: public wxDialog
{
	public:

		ExportToImg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ExportToImg();

	private:

		//(*Declarations(ExportToImg)
		wxButton* Button1;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		wxTextCtrl* TextCtrl_FilePrefix;
		//*)

	protected:

		//(*Identifiers(ExportToImg)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_TEXTCTRL1;
		static const long ID_PANEL1;
		//*)

	public:

		//(*Handlers(ExportToImg)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)
		wxString nameprefix;
		wxString GetNamePrefix(){return nameprefix;}
		void SetNamePrix(const wxString namepre)
		{
		    TextCtrl_FilePrefix->SetValue(namepre);
		}

		DECLARE_EVENT_TABLE()
};

#endif
