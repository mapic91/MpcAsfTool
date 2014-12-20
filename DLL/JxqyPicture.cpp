#include "WorkManager.hpp"
#include "JxqyPicture.h"

WorkManager worked = WorkManager();

bool DLL_CALLCONV JX_ReadFile(const char* filePath)
{
    worked.ReNew();
    return worked.OpenFile(wxString(filePath));
}

int DLL_CALLCONV JX_GetFrameCount()
{
    return worked.GetFrameCounts();
}

int DLL_CALLCONV JX_GetCanvasWidth()
{
    return worked.GetGlobalWidth();
}

int DLL_CALLCONV JX_GetCanvasHeight()
{
    return worked.GetGlobalHeight();
}

BYTE ApplyAlpha(BYTE color, BYTE alpha)
{
    return (BYTE)(((double)color)*((double)alpha/(double)0xFF) +
                  ((double)255)*((double)(0xFF-alpha)/(double)0xFF));
}

void DLL_CALLCONV JX_SetAlphaMask(BYTE mask)
{
    worked.SetAlphaMask(mask);
}

enum ColorType {RGBA, BGRA, RGB, BGR};
PBYTE DLL_CALLCONV GetFrameData(int index, ColorType type)
{
    FILOCRGBQUAD *frame = worked.GetUndeletedGlobalizedFrameData((unsigned long)index);
    PBYTE data = NULL;
    long width = worked.GetGlobalWidth();
    long height = worked.GetGlobalHeight();
    int pixelSize = 4;
    if(type == RGB || type == BGR) pixelSize = 3;
    long size = width*height*pixelSize;
    if(frame && size > 0)
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
                case BGR:
                    alpha = frame[index].rgbReserved;
                    data[i++] = ApplyAlpha(frame[index].rgbBlue, alpha);
                    data[i++] = ApplyAlpha(frame[index].rgbGreen, alpha);
                    data[i++] = ApplyAlpha(frame[index].rgbRed, alpha);
                    break;
                }
                index++;
            }
        }
    }
    if(frame) delete[] frame;
    return data;
}

PBYTE DLL_CALLCONV JX_GetFrameDataRGBA(int index)
{
    return GetFrameData(index, RGBA);
}

PBYTE DLL_CALLCONV JX_GetFrameDataBGRA(int index)
{
    return GetFrameData(index, BGRA);
}

PBYTE DLL_CALLCONV JX_GetFrameDataRGB(int index)
{
    return GetFrameData(index, RGB);
}

PBYTE DLL_CALLCONV JX_GetFrameDataBGR(int index)
{
    return GetFrameData(index, BGR);
}

PBYTE DLL_CALLCONV GetFrameData_R(int index, ColorType type)
{
    FILOCRGBQUAD *frame = worked.GetUndeletedGlobalizedFrameData((unsigned long)index);
    PBYTE data = NULL;
    long width = worked.GetGlobalWidth();
    long height = worked.GetGlobalHeight();
    int pixelSize = 4;
    if(type == RGB || type == BGR) pixelSize = 3;
    long size = width*height*pixelSize;
    if(frame && size > 0)
    {
        data = (PBYTE)malloc(size);
        if(data)
        {
            int i = 0;
            BYTE alpha;
            for(int h = height -1; h >= 0; h--)
            {
                for(int w = 0; w < width; w++)
                {
                	int index = height*width + w;
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
                    case BGR:
                        alpha = frame[index].rgbReserved;
                        data[i++] = ApplyAlpha(frame[index].rgbBlue, alpha);
                        data[i++] = ApplyAlpha(frame[index].rgbGreen, alpha);
                        data[i++] = ApplyAlpha(frame[index].rgbRed, alpha);
                        break;
                    }
                }
            }
        }
    }
    if(frame) delete[] frame;
    return data;
}

JXQYPICTURE_DLL PBYTE DLL_CALLCONV JX_GetFrameDataRGBA_R(int index)
{
	return GetFrameData_R(index, RGBA);
}

JXQYPICTURE_DLL PBYTE DLL_CALLCONV JX_GetFrameDataBGRA_R(int index)
{
	return GetFrameData_R(index, BGRA);
}
JXQYPICTURE_DLL PBYTE DLL_CALLCONV JX_GetFrameDataRGB_R(int index)
{
	return GetFrameData_R(index, RGB);
}
JXQYPICTURE_DLL PBYTE DLL_CALLCONV JX_GetFrameDataBGR_R(int index)
{
	return GetFrameData_R(index, BGR);
}
