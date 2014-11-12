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

//(*AppHeaders
#include "NewFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxWidgets_templateApp);

bool wxWidgets_templateApp::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
		NewFrame* Frame = new NewFrame(0);
		Frame->Show();
		SetTopWindow(Frame);
	}
	//*)
	return wxsOK;
}
