/***************************************************************
 * Name:      wxWidgets_templateMain.h
 * Purpose:   Defines Application Frame
 * Author:    jxmp (mapic91@163.com)
 * Created:   2013-03-07
 * Copyright: jxmp (mapicweb)
 * License:
 **************************************************************/

#ifndef WXWIDGETS_TEMPLATEMAIN_H
#define WXWIDGETS_TEMPLATEMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "App.h"

class wxWidgets_templateFrame: public wxFrame
{
    public:
        wxWidgets_templateFrame(wxFrame *frame, const wxString& title);
        ~wxWidgets_templateFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WXWIDGETS_TEMPLATEMAIN_H
