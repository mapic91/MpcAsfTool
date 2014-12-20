#ifndef DLGADDFRAMES_H
#define DLGADDFRAMES_H

#include "wx/arrstr.h"

//(*Headers(DlgAddFrames)
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class DlgAddFrames: public wxDialog
{
	public:

		DlgAddFrames(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DlgAddFrames();

	private:

		//(*Declarations(DlgAddFrames)
		wxButton* Button_UP;
		wxButton* Button1;
		wxButton* Button_Del;
		wxButton* Button_OK;
		wxListCtrl* ListCtrl_Files;
		wxButton* Button_Down;
		//*)
		long itemsel;

	protected:

		//(*Identifiers(DlgAddFrames)
		static const long ID_LISTCTRL1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	public:

		//(*Handlers(DlgAddFrames)
		void OnButton_UPClick(wxCommandEvent& event);
		void OnButton_DownClick(wxCommandEvent& event);
		void OnButton_DelClick(wxCommandEvent& event);
		void OnButton_OKClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		//*)
		void OnListSelected(wxListEvent &event);
		void InitListCtrl(const wxArrayString &infiles);
		wxArrayString GetArrangedFiles();

		DECLARE_EVENT_TABLE()
};

#endif
