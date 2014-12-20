#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include "wx/string.h"
//(*Headers(ProgressDlg)
#include <wx/stattext.h>
#include <wx/dialog.h>
//*)

class ProgressDlg: public wxDialog
{
	public:

		ProgressDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ProgressDlg();

	private:

		//(*Declarations(ProgressDlg)
		wxStaticText* StaticText_Progress;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(ProgressDlg)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		//*)

	public:

		//(*Handlers(ProgressDlg)
		//*)
		void SetText(const wxString text){StaticText_Progress->SetLabel(text);}

		DECLARE_EVENT_TABLE()
};

#endif
