#include "JxqyPicture.h"
#include "WorkManager.hpp"

WorkManager *worked;

bool DLL_CALLCONV ReadFile(const char* filePath)
{
    if(worked == NULL)
    {
        worked = new WorkManager();
    }
    worked->ReNew();
    return worked->OpenFile(wxString(filePath));
}

int DLL_CALLCONV GetFrameCount()
{
    return worked->GetFrameCounts();
}

int DLL_CALLCONV GetCanvasWidth()
{
    return worked->GetGlobalWidth();
}

int DLL_CALLCONV GetCanvasHeight()
{
    return worked->GetGlobalHeight();
}

BYTE ApplyAlpha(BYTE color, BYTE alpha)
{
	return (BYTE)(((double)color)*((double)alpha/(double)0xFF) +
                            ((double)255)*((double)(0xFF-alpha)/(double)0xFF));
}

enum ColorType {RGBA, BGRA, RGB};
PBYTE DLL_CALLCONV GetFrameData(int index, ColorType type)
{
    FILOCRGBQUAD *frame = worked->GetUndeletedGlobalizedFrameData((unsigned long)index);
    PBYTE data = NULL;
    long width = worked->GetGlobalWidth();
    long height = worked->GetGlobalHeight();
    int pixelSize = 4;
    if(type == RGB) pixelSize = 3;
    long size = width*height*pixelSize;
    if(frame && size != 0)
    {
        data = (PBYTE)malloc(size);
        if(data)
        {
            int index = 0;
            BYTE alpha;
            for(int i = 0; i < size; )
            {
                switch(type)
                {
                case RGBA:
                    data[i++] = frame[index].rgbRed;
                    data[i++] = frame[index].rgbGreen;
                    data[i++] = frame[index].rgbBlue;
                    data[i++] = frame[index].rgbReserved;
                    break;
                case BGRA:
                    data[i++] = frame[index].rgbBlue;
                    data[i++] = frame[index].rgbGreen;
                    data[i++] = frame[index].rgbRed;
                    data[i++] = frame[index].rgbReserved;
                    break;
                case RGB:
                	alpha = frame[index].rgbReserved;
					data[i++] = ApplyAlpha(frame[index].rgbRed, alpha);
                    data[i++] = ApplyAlpha(frame[index].rgbGreen, alpha);
                    data[i++] = ApplyAlpha(frame[index].rgbBlue, alpha);
                    break;
                }
                index++;
            }
        }
    }
    if(frame) delete[] frame;
    return data;
}

PBYTE DLL_CALLCONV GetFrameDataRGBA(int index)
{
	return GetFrameData(index, RGBA);
}

PBYTE DLL_CALLCONV GetFrameDataBGRA(int index)
{
	return GetFrameData(index, BGRA);
}

PBYTE DLL_CALLCONV GetFrameDataRGB(int index)
{
	return GetFrameData(index, RGB);
}

void DLL_CALLCONV FreeResource()
{
    if(worked) delete worked;
}
