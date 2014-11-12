#ifndef NEWFRAME_H
#define NEWFRAME_H

//(*Headers(NewFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/clrpicker.h>
//*)

#include "AsfDecode.hpp"
#include "MpcDecode.hpp"

class NewFrame: public wxFrame
{
	public:

		NewFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewFrame();

	private:

		//(*Declarations(NewFrame)
		wxStaticText* StaticText9;
		wxButton* Button_SaveGif;
		wxSpinCtrl* SpinCtrl_PosX;
		wxCheckBox* CheckBox_MakeShow;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxButton* Button_SaveMpc;
		wxButton* Button_SaveAsf;
		wxButton* Button_SavePng;
		wxSpinCtrl* SpinCtrl_SunX;
		wxStaticText* StaticText8;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* Button_Open;
		wxButton* Button_Next;
		wxSpinCtrl* SpinCtrl_transmask;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxSpinCtrl* SpinCtrl_SunY;
		wxButton* Button_Previous;
		wxButton* Button_test;
		wxColourPickerCtrl* ColPic_BacCol;
		wxSpinCtrl* SpinCtrl_Buttom;
		wxSpinCtrl* SpinCtrl_PosY;
		wxStaticText* StaticText4;
		wxSpinCtrl* SpinCtrl_Left;
		wxCheckBox* CheckBox_SHD;
		wxSpinCtrl* SpinCtrl_Interval;
		wxStaticBitmap* StaticBitmap_show;
		wxSpinCtrl* SpinCtrl_Direction;
		//*)

	protected:

		//(*Identifiers(NewFrame)
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL4;
		static const long ID_STATICTEXT5;
		static const long ID_SPINCTRL5;
		static const long ID_STATICTEXT6;
		static const long ID_SPINCTRL6;
		static const long ID_STATICTEXT7;
		static const long ID_SPINCTRL7;
		static const long ID_STATICTEXT8;
		static const long ID_SPINCTRL8;
		static const long ID_STATICTEXT9;
		static const long ID_SPINCTRL9;
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON5;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BUTTON6;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_COLOURPICKERCTRL1;
		static const long ID_STATICBITMAP1;
		static const long ID_PANEL1;
		//*)

	public:

		//(*Handlers(NewFrame)
		void OnButton_OpenClick(wxCommandEvent& event);
		void OnButton_SaveGifClick(wxCommandEvent& event);
		void OnButton_PreviousClick(wxCommandEvent& event);
		void OnButton_NextClick(wxCommandEvent& event);
		void OnButton_SavePngClick(wxCommandEvent& event);
		void OnButton_testClick(wxCommandEvent& event);
		void OnSpinCtrl_transmaskChange(wxSpinEvent& event);
		void OnCheckBox_SHDClick(wxCommandEvent& event);
		void OnButton_SaveMpcClick(wxCommandEvent& event);
		void OnButton_SaveAsfClick(wxCommandEvent& event);
		//*)

    private:
        enum File_Type{ASF, MPC};
        File_Type filetype;
        wxString FilePath;
        unsigned long currentframe, framecounts;
        AsfDecode asfdecode;
        MpcDecode mpcdecode;



		DECLARE_EVENT_TABLE()
};

#endif
