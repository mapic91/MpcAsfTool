#ifndef ADJUSTPOSITIONDIALOG_H
#define ADJUSTPOSITIONDIALOG_H

#include "wx/image.h"

//(*Headers(AdjustPositionDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class AdjustPositionDialog: public wxDialog
{
	public:

		AdjustPositionDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AdjustPositionDialog();

	private:

		//(*Declarations(AdjustPositionDialog)
		wxButton* Button_Ok;
		wxRadioButton* RadioButton_yyxj;
		wxSpinCtrl* SpinCtrl_PicY;
		wxStaticText* StaticText2;
		wxSpinCtrl* SpinCtrl_OffX;
		wxRadioButton* RadioButton_j2;
		wxSpinCtrl* SpinCtrl_PicX;
		wxButton* Button_Cancle;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxPanel* Panel_Show;
		wxSpinCtrl* SpinCtrl_OffY;
		wxStaticText* StaticText4;
		//*)
		void RedrawShow(){Panel_Show->Refresh();Panel_Show->Update();}

	protected:

		//(*Identifiers(AdjustPositionDialog)
		static const long ID_PANEL1;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL4;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	public:

		//(*Handlers(AdjustPositionDialog)
		void OnRadioButton_yyxjSelect(wxCommandEvent& event);
		void OnRadioButton_j2Select(wxCommandEvent& event);
		void OnSpinCtrl_OffXChange(wxSpinEvent& event);
		void OnSpinCtrl_OffYChange(wxSpinEvent& event);
		void OnButton_OkClick(wxCommandEvent& event);
		void OnButton_CancleClick(wxCommandEvent& event);
		void OnSpinCtrl_PicXChange(wxSpinEvent& event);
		void OnSpinCtrl_PicYChange(wxSpinEvent& event);
		//*)
		void OnDraw(wxPaintEvent& event);
		void OnSize(wxSizeEvent& event)
		{
		    if(Panel_Show != NULL && this->IsShown())
            {
                Panel_Show->Refresh();
                Panel_Show->Update();
            }
		    event.Skip();
        }

		void AssignValue(int offx, int offy, int picx, int picy)
		{
		    SpinCtrl_OffX->SetValue(offx);
		    SpinCtrl_OffY->SetValue(offy);
		    SpinCtrl_PicX->SetValue(picx);
		    SpinCtrl_PicY->SetValue(picy);
		    m_PicX = picx;
		    m_PicY = picy;
		}
		void SetShowImage(wxImage img) {m_img = img;}
		int GetOffX() const {return SpinCtrl_OffX->GetValue();}
		int GetOffY() const {return SpinCtrl_OffY->GetValue();}
		int GetPicX() const {return SpinCtrl_PicX->GetValue();}
		int GetPicY() const {return SpinCtrl_PicY->GetValue();}

    private:
        wxImage m_img;
        int m_PicX, m_PicY; // m_img is alread moved

		DECLARE_EVENT_TABLE()
};

#endif
