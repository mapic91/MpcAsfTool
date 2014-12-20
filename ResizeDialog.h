#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

//(*Headers(ResizeDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class ResizeDialog: public wxDialog
{
	public:

		ResizeDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ResizeDialog();

	private:

		void SizeChange();
		void PercentChange();

		//(*Declarations(ResizeDialog)
		wxSpinCtrl* msc_Height;
		wxButton* mb_Ok;
		wxSpinCtrl* msc_Width;
		wxStaticText* StaticText2;
		wxCheckBox* mcb_KeepRatio;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxSpinCtrl* msc_Percent;
		wxButton* mb_Cancle;
		wxStaticText* StaticText4;
		//*)
		int m_CurrentWidth;
		int m_CurrentHeight;

	protected:

		//(*Identifiers(ResizeDialog)
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_CHECKBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	public:

		//(*Handlers(ResizeDialog)
		void Onmb_OkClick(wxCommandEvent& event);
		void Onmb_CancleClick(wxCommandEvent& event);
		void Onmsc_PercentChange(wxSpinEvent& event);
		void Onmsc_WidthChange(wxSpinEvent& event);
		void Onmsc_HeightChange(wxSpinEvent& event);
		void Onmcb_KeepRatioClick(wxCommandEvent& event);
		//*)

		void SetCurrentWidth(int width)
		{
			m_CurrentWidth = width;
			msc_Width->SetValue(width);
		}
		void SetCurrentHeight(int height)
		{
			m_CurrentHeight = height;
			msc_Height->SetValue(height);
		}
		int GetWidth(){return msc_Width->GetValue();}
		int GetHeight(){return msc_Height->GetValue();}

		DECLARE_EVENT_TABLE()
};

#endif
