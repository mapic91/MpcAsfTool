#include "AsftoPic.hpp"
#include "AsfDecode.hpp"
#include "MAPICDATA.hpp"
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

bool CovAsftoPic::Save(FileType type, Palette_Colour *backcolor, unsigned char transmask,
                       long direction, long interval, long bottom, long left, bool makeshadow,
                       long offsetsunx, long offsetsuny,long offsetposx, long offsetposy)
{
    if(inFilePath.IsEmpty() || outFilePath.IsEmpty()) return false;
    else
    {
        unsigned long framessum, width, height;
        //bool res, istran;
        //BYTE *strdata = NULL, transidx;
        FILOCRGBQUAD *strdata = NULL;
        AsfDecode decode;
        MAPICDATA data;

        if(!decode.ReadAsfFile(inFilePath))return false;
        framessum = decode.GetFramesCounts();
        width = decode.GetGlobleWidth();
        height = decode.GetGlobleHeight();
        data.Init((long)width, (long)height);

        if(type == T_GIF)
        {
            for(unsigned long i = 0; i < framessum; i++)
            {
                strdata = decode.GetFIDecodedFrameData(i, NULL, NULL, AsfDecode::PIC_RGB, NULL, backcolor, transmask);
                if(!strdata)return false;
                data.AddFrame(strdata);
            }
            if(!data.SaveToGif(outFilePath)) return false;
            wxMessageBox(_("GIF文件已保存"));
            return true;
        }
        else if(type == T_PNG)
        {
            for(unsigned long i = 0; i < framessum; i++)
            {
                strdata = decode.GetFIDecodedFrameData(i, NULL, NULL, AsfDecode::PIC_RGBA, NULL, backcolor);
                if(!strdata)return false;
                data.AddFrame(strdata);
            }
            wxString infilename = wxFileName::FileName(inFilePath).GetName();
            if(!data.SaveToPng(outFilePath+wxFileName::GetPathSeparator()+infilename)) return false;
            wxMessageBox(_("PNG文件已保存"));
            return true;
        }
        else if(type == T_MPC)
        {
            for(unsigned long i = 0; i < framessum; i++)
            {
                strdata = decode.GetFIDecodedFrameData(i, NULL, NULL, AsfDecode::PIC_RGB, NULL, backcolor, transmask);
                if(!strdata)return false;
                data.AddFrame(strdata);
            }
            if(!data.SaveToMpc(outFilePath, direction, interval, bottom, makeshadow)) return false;
            wxMessageBox(_("MPC文件已保存"));
            return true;
        }
        else if(type == T_ASF)
        {
            for(unsigned long i = 0; i < framessum; i++)
            {
                strdata = decode.GetFIDecodedFrameData(i, NULL, NULL, AsfDecode::PIC_RGBA, NULL, backcolor);
                if(!strdata)return false;
                data.AddFrame(strdata);
            }
            if(!data.SaveToAsf(outFilePath, direction, interval, bottom, left, makeshadow,
                               offsetsunx, offsetsuny, offsetposx, offsetposy)) return false;
            wxMessageBox(_("ASF文件已保存"));
            return true;
        }
    }

    return true;
}
