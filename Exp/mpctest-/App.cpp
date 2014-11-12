/***************************************************************
 * Name:      wxWidgets_templateApp.cpp
 * Purpose:   Code for Application Class
 * Author:    jxmp (mapic91@163.com)
 * Created:   2013-03-07
 * Copyright: jxmp (mapicweb)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "App.h"
#include "Main.h"

IMPLEMENT_APP(wxWidgets_templateApp);

bool wxWidgets_templateApp::OnInit()
{
    wxWidgets_templateFrame* frame = new wxWidgets_templateFrame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
