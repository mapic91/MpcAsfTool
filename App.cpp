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
#include "MpcAsfTool.h"

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxWidgets_templateApp);

bool wxWidgets_templateApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    //*)

    MpcAsfTool* Frame = new MpcAsfTool(0);
    Frame->Show();
    SetTopWindow(Frame);
    //Frame->Maximize();
    Frame->Center();
    Frame->Refresh();

    if(argc > 1) Frame->OpenFile(argv[1]);

    return wxsOK;
}
