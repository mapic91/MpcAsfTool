#ifndef NEWFRAME_H
#define NEWFRAME_H

//(*Headers(NewFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

class NewFrame: public wxFrame
{
	public:

		NewFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewFrame();

	private:

		//(*Declarations(NewFrame)
		wxButton* Button_mpcfile;
		wxStaticBitmap* bitmap_view;
		wxButton* Button_next;
		wxStaticText* StaticText_current_pic;
		wxPanel* Panel1;
		wxButton* Button_previous;
		//*)

	protected:

		//(*Identifiers(NewFrame)
		static const long ID_STATICBITMAP1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT1;
		static const long ID_PANEL1;
		//*)

	public:

		//(*Handlers(NewFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
