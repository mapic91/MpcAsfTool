#include "AsftoPic.hpp"
#include "AsfDecode.hpp"
//#include "FreeImage_IO_CallBack.hpp"

#include "FreeImage.h"

#include "wx/log.h"
#include "wx/stream.h"
#include "wx/mstream.h"
#include "wx/filename.h"
#include <fstream>

CovAsftoPic::CovAsftoPic(const wxString inMpcFilePath, const wxString outGifFilePath)
{
    inFilePath = inMpcFilePath;
    outFilePath = outGifFilePath;
}

bool CovAsftoPic::Save(FileType type)
{
    if(inFilePath.IsEmpty() || outFilePath.IsEmpty()) return false;
    else
    {
        unsigned long framessum, width, height;
        bool res, istran;
        BYTE *strdata = NULL, transidx;
        FILOCRGBQUAD rgb;
        FIBITMAP *fibmp, *fiquat;
        FIMULTIBITMAP* gifimg;
        AsfDecode decode;

        if(!decode.ReadAsfFile(inFilePath))
        {
            wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
            return false;
        }
        framessum = decode.GetFramesCounts();

        if(type == T_GIF)
        {
            gifimg = FreeImage_OpenMultiBitmap(FIF_GIF, outFilePath.char_str(), TRUE,
                                               FALSE, TRUE, 0);
            if(!gifimg)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }
            for(unsigned long i = 0; i < framessum; i++)
            {
                strdata = decode.GetDecodedFrameData(i, (long*)&width, (long*)&height, AsfDecode::ASF_RGB, &istran);
                if(!strdata)
                {
                    wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                    return false;
                }

                fibmp = FreeImage_Allocate(width, height, 24);
                if(!fibmp)
                {
                    wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                    return false;
                }
                for(unsigned long j = 0; j < height; j++)
                {
                    for(unsigned long k = 0; k < width; k++)
                    {
                        rgb.rgbRed   = strdata[j*width*3 + k*3];
                        rgb.rgbGreen = strdata[j*width*3 + k*3 +1];
                        rgb.rgbBlue  = strdata[j*width*3 + k*3 +2];
                        res = FreeImage_SetPixelColor(fibmp,k, height-1-j, &rgb);
                        if(!res)
                        {
                            wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                            return false;
                        }
                    }

                }
                free(strdata);
                strdata = NULL;
                fiquat = FreeImage_ColorQuantize(fibmp, FIQ_NNQUANT);
                FreeImage_Unload(fibmp);
                fibmp = NULL;
                if(!fiquat)
                {
                    wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                    return false;
                }
                if(istran)
                {
                    FreeImage_GetPixelIndex(fiquat, 0, height-1, &transidx);
                    FreeImage_SetTransparentIndex(fiquat, (int)transidx);
                }

                FreeImage_AppendPage(gifimg, fiquat);
                FreeImage_Unload(fiquat);
                fiquat = NULL;
            }
            if(!FreeImage_CloseMultiBitmap(gifimg, 0))return false;
            wxMessageBox(wxT("Gif constructing ok"));
            return true;
        }
        else if(type == T_PNG)
        {
            wxString infilename = wxFileName::FileName(inFilePath).GetName();

            for(unsigned long i = 0; i < framessum; i++)
            {
                strdata = decode.GetDecodedFrameData(i, (long*)&width, (long*)&height, AsfDecode::ASF_BGRA, &istran);
                if(!strdata)
                {
                    wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                    return false;
                }
                fibmp = FreeImage_ConvertFromRawBits(strdata, width, height, (int)width*4,
                                                     32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK,
                                                     FI_RGBA_BLUE_MASK, TRUE);
                free(strdata); strdata = NULL;
                if(!fibmp)
                {
                    wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                    return false;
                }
                if(!FreeImage_SaveU(FIF_PNG, fibmp,
                                (outFilePath+wxFileName::GetPathSeparator()+
                                 infilename+wxString::Format(wxT("-%03ld"), i+1)+
                                 wxT(".png")).c_str(), 0))
                {
                    FreeImage_Unload(fibmp); fibmp = NULL;
                    return false;
                }
                FreeImage_Unload(fibmp); fibmp = NULL;
            }
            wxMessageBox(wxT("Png constructing ok"));
            return true;
        }
    }

    return false;
}
