#include "wx/log.h"
#include "wx/stream.h"
#include "wx/mstream.h"
#include "wx/filename.h"
#include <fstream>

#include "MpctoPic.hpp"
#include "MpcDecode.hpp"
#include "ShdDecode.hpp"
#include "MAPICDATA.hpp"

//#include "FreeImage_IO_CallBack.hpp"


CovMpctoPic::CovMpctoPic(const wxString inMpcFilePath, const wxString outGifFilePath)
{
    inFilePath = inMpcFilePath;
    outFilePath = outGifFilePath;
}

bool CovMpctoPic::Save(FileType type, bool ShdIncluded, long direction, long interval,
                       long bottom, long left, bool makeshadow,
                       long offsetsunx, long offsetsuny,long offsetposx, long offsetposy)
{
    if(inFilePath.IsEmpty() || outFilePath.IsEmpty()) return false;
    else
    {
        unsigned long framessum, width, height;
        FILOCRGBQUAD *strdata = NULL, *shddata;
        MpcDecode decode;
        ShdDecode shddecode;
        MAPICDATA data;
        wxString shdpath;
        bool shdicl = false;

        if(!decode.ReadMpcFile(inFilePath)) return false;
        framessum = decode.GetFramesCounts();
        width = decode.GetGlobleWidth();
        height = decode.GetGlobleHeight();
        data.Init((long)width, (long)height);

        if(ShdIncluded)
        {
            shdpath = wxFileName::FileName(inFilePath).GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);
            shdpath += wxFileName::FileName(inFilePath).GetName();
            shdpath += wxT(".shd");
            if(wxFileName::FileExists(shdpath))
            {
                if(shddecode.ReadShdFile(shdpath))
                {
                    if(shddecode.GetGlobleWidth() == (long)width &&
                       shddecode.GetGlobleHeight() == (long)height)
                    {
                        shdicl = true;
                    }
                }
            }
        }

        for(unsigned long i = 0; i < framessum; i++)
        {
            strdata = decode.GetGlobleFIDecodedFrameData(i, NULL, NULL, MpcDecode::PIC_RGBA);
            if(!strdata)
            {
                return false;
            }

            if(shdicl)
            {
                shddata = shddecode.GetGlobleFIDecodedFrameData(i, NULL, NULL, ShdDecode::PIC_RGBA);
                if(shddata)
                {
                for(unsigned long sidx = 0; sidx < width*height; sidx++)
                {
                    if(strdata[sidx].rgbReserved != 0)
                    {
                        shddata[sidx].rgbBlue = strdata[sidx].rgbBlue;
                        shddata[sidx].rgbGreen = strdata[sidx].rgbGreen;
                        shddata[sidx].rgbRed = strdata[sidx].rgbRed;
                        shddata[sidx].rgbReserved = strdata[sidx].rgbReserved;
                    }
                }
                delete[] strdata;
                strdata = shddata;
                }
            }
            data.AddFrame(strdata);
        }

        if(type == T_GIF)
        {
            if(!data.SaveToGif(outFilePath)) return false;
            wxMessageBox(_("GIF文件已保存"));
            return true;
        }
        else if(type == T_PNG)
        {
            wxString infilename = wxFileName::FileName(inFilePath).GetName();
            if(!data.SaveToPng(outFilePath+wxFileName::GetPathSeparator()+infilename)) return false;
            wxMessageBox(_("PNG文件已保存"));
            return true;
        }
        else if(type == T_MPC)
        {
            if(!data.SaveToMpc(outFilePath, direction, interval, bottom, makeshadow)) return false;
            wxMessageBox(_("MPC文件已保存"));
            return true;
        }
        else if(type == T_ASF)
        {
            if(!data.SaveToAsf(outFilePath, direction, interval, bottom, left, makeshadow,
                               offsetsunx, offsetsuny, offsetposx, offsetposy)) return false;
            wxMessageBox(_("ASF文件已保存"));
            return true;
        }
    }

    return true;
}
