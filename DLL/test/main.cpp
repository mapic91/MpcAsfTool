#include "wx/image.h"
#include "JxqyPicture.h"

int main(int argc, char** argv)
{
	wxInitAllImageHandlers();
	wxImage image;
	PBYTE data;
	if(ReadFile("2.spr"))
	{
		int width = GetCanvasWidth();
		int height = GetCanvasHeight();
		int count = GetFrameCount();
		for(int i = 0 ; i < count; i++)
		{
			data = GetFrameDataRGB(i);
			image.Create(width, height, data, true);
			image.SaveFile(wxString::Format("0ut-%d.png", i), wxBITMAP_TYPE_PNG);
		}
	}
	FreeResource();
    return 0;
}
