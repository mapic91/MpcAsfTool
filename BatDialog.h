#ifndef BATDIALOG_H
#define BATDIALOG_H

//(*Headers(BatDialog)
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/clrpicker.h>
//*)

class BatDialog: public wxDialog
{
	public:

		BatDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~BatDialog();

	private:

		//(*Declarations(BatDialog)
		wxCheckBox* CheckBox_isShd;
		wxSpinCtrl* SpinCtrl_FrameEnd;
		wxButton* Button_Ok;
		wxRadioButton* RadioButton_Gif;
		wxStaticText* StaticText2;
		wxSpinCtrl* SpinCtrl_FrameBegin;
		wxStaticText* StaticText6;
		wxRichTextCtrl* RichTextCtrl_List;
		wxRadioButton* RadioButton_Asf;
		wxRadioButton* RadioButton_Mpc;
		wxButton* Button_Cancle;
		wxStaticText* StaticText1;
		wxButton* Button_Empty;
		wxStaticText* StaticText3;
		wxColourPickerCtrl* ColourPickerCtrl_BaseColor;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxSpinCtrl* SpinCtrl_Scale;
		wxSpinCtrl* SpinCtrl_AlphaMask;
		wxButton* Button_Add;
		wxStaticText* StaticText4;
		wxRadioButton* RadioButton_Png;
		//*)

	protected:

		//(*Identifiers(BatDialog)
		static const long ID_RICHTEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_COLOURPICKERCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL1;
		static const long ID_SPINCTRL2;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_RADIOBUTTON3;
		static const long ID_RADIOBUTTON4;
		static const long ID_SPINCTRL4;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		//*)

	public:

		//(*Handlers(BatDialog)
		void OnButton_AddClick(wxCommandEvent& event);
		void OnButton_EmptyClick(wxCommandEvent& event);
		void OnButton_OkClick(wxCommandEvent& event);
		void OnButton_CancleClick(wxCommandEvent& event);
		void OnRadioButton_GifSelect(wxCommandEvent& event);
		void OnRadioButton_PngSelect(wxCommandEvent& event);
		//*)

    public:
        wxRichTextCtrl *GetListTextCtrl(){return RichTextCtrl_List;}
        wxColour GetBaseColor(){return ColourPickerCtrl_BaseColor->GetColour();}
        unsigned char GetAlphaMask(){return (unsigned char)SpinCtrl_AlphaMask->GetValue();}
        int GetFrameBegin(){return (SpinCtrl_FrameBegin->GetValue() - 1);}
        int GetFrameEnd(){return (SpinCtrl_FrameEnd->GetValue() - 1);}
        bool isGif(){return RadioButton_Gif->GetValue();}
        bool isPng(){return RadioButton_Png->GetValue();}
        bool isMpc(){return RadioButton_Mpc->GetValue();}
        bool isAsf(){return RadioButton_Asf->GetValue();}
        float getScaleRatio(){return (float)SpinCtrl_Scale->GetValue()/(float)100;}
        bool isShd(){return CheckBox_isShd->IsChecked();}
		DECLARE_EVENT_TABLE()
};

#endif
