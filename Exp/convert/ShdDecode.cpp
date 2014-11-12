#include "ShdDecode.hpp"

#include "wx/msgdlg.h"

#include <cstring>
#include <fstream>

ShdDecode::ShdDecode()
{
    Init();
}
ShdDecode::~ShdDecode()
{

}
ShdDecode::ShdDecode(const wxString ShdFilePath)
{
    Init();
    FilePath = ShdFilePath;
}
void ShdDecode::Init()
{
    memset(&FileHead,0, sizeof(ShdFileHead));
}
void ShdDecode::SetShdFile(const wxString ShdFilePath)
{
    FilePath = ShdFilePath;
}
wxString ShdDecode::GetFilePath()
{
    return FilePath;
}
bool ShdDecode::ReadShdFile()
{
    if(FilePath.IsEmpty()) return false;
    else
    {
        unsigned char temp4b[4];
        unsigned long tempul =0;
        std::ifstream shdfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        if(!shdfile.is_open()) return false;

        //Read head
        shdfile.read(FileHead.VersionInfo, 64);//info
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.FramesDataLengthSum = tempul;
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        if(tempul > 0x7FFFFFFF) tempul = (unsigned long)(-(long)tempul);
        FileHead.GlobleWidth = (long)(0x0 | tempul);
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        if(tempul > 0x7FFFFFFF) tempul = (unsigned long)(-(long)tempul);
        FileHead.GlobleHeight = (long)(0x0 | tempul);
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.FrameCounts = tempul;
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Direction = (long)(0x0 | tempul);
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.ColourCounts = tempul;
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Interval = (long)(0x0 | tempul);
        shdfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Bottom = (long)(0x0 | tempul);
        shdfile.read(FileHead.Reserved, 32);

        FrameDataBegPos = shdfile.tellg();
        if(!shdfile.good())return false;
        shdfile.close();
    }
    return true;
}
bool ShdDecode::ReadShdFile(const wxString ShdFilePath)
{
    FilePath = ShdFilePath;
    return ReadShdFile();
}
wxString ShdDecode::GetVersionInfo()
{
    return wxString(FileHead.VersionInfo, wxConvLibc);
}
unsigned long ShdDecode::GetFramesDataLengthSum()
{
    return FileHead.FramesDataLengthSum;
}
unsigned long ShdDecode::GetFramesCounts()
{
    return FileHead.FrameCounts;
}
long ShdDecode::GetGlobleWidth()
{
    return FileHead.GlobleWidth;
}
long ShdDecode::GetGlobleHeight()
{
    return FileHead.GlobleHeight;
}
long ShdDecode::GetDirection()
{
    return FileHead.Direction;
}
unsigned long ShdDecode::GetColourCounts()
{
    return FileHead.ColourCounts;
}
unsigned long ShdDecode::GetInterval()
{
    return FileHead.Interval;
}
long ShdDecode::GetBottom()
{
    return FileHead.Bottom;
}
unsigned char* ShdDecode::GetDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod)
{
    switch(mod)
    {
    case PIC_RGB:
    case PIC_BGRA:
    case PIC_RGBA:
        break;
    default:
        return NULL;
    }
    if(index < FileHead.FrameCounts)
    {
        unsigned long temppos = 0, datalength, width = FileHead.GlobleWidth,
                      height = FileHead.GlobleHeight, curdecposition = 0;
        unsigned char temp[8];
        std::ifstream shdfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        long decdatalen;
        unsigned char* decdata;
        if(!shdfile.is_open())
        {
            wxMessageBox(wxT("Shd File Open Failed!"));
            return NULL;
        }
        shdfile.seekg(FrameDataBegPos+index*4);
        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        shdfile.seekg(FrameDataBegPos + FileHead.FrameCounts*4 + temppos);
        if(shdfile.eof())
        {
            wxMessageBox(wxT("Shd File Read Error!"));
            shdfile.close();
            return NULL;
        }

        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        datalength = temppos;
        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        width = temppos;
        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        height = temppos;
        shdfile.seekg(8, std::ios_base::cur);
        if(Width != NULL)*Width = width;
        if(Height != NULL)*Height = height;
        switch(mod)
        {
        case PIC_RGB:
            decdatalen = width * height * 3;
            break;
        case PIC_RGBA:
        case PIC_BGRA:
            decdatalen = width * height * 4;
            break;
        default:
            return NULL;
        }
        decdata = (unsigned char*)malloc((size_t)decdatalen);
        if(decdata == NULL)
        {
            shdfile.close();
            wxMessageBox(wxT("malloc failed!"));
            return NULL;
        }

        for(long datidx = 0; datidx < decdatalen;)
        {
            decdata[datidx++] = 0xFF;
            decdata[datidx++] = 0xFF;
            decdata[datidx++] = 0xFF;
            switch(mod)
            {
            case PIC_RGBA:
            case PIC_BGRA:
                decdata[datidx++] = 0x00;
                break;
            default:
                break;
            }
        }

        shdfile.read((char*)temp,1);
        for(unsigned long i = 0; i < datalength - 20;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                wxMessageBox(wxT("Out of Range"));
                free(decdata);
                shdfile.close();
                return NULL;
            }
            if(temp[0] > (unsigned char)0x80)
            {
                temppos = temp[0] - (unsigned char)0x80;
                for(unsigned char j = 0; j < temppos; j++)
                {
                    switch(mod)
                    {
                    case PIC_RGB:
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0xFF;
                        break;
                    case PIC_RGBA:
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0x00;
                        break;
                    case PIC_BGRA:
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0xFF;
                        decdata[curdecposition++] = 0x00;
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            else
            {
                temppos = temp[0];
                for(unsigned char m = 0; m < temppos; m++)
                {
                    if(shdfile.fail())
                    {
                        wxMessageBox(wxT("Shd File Read out of end."));
                        shdfile.close();
                        free(decdata);
                        return NULL;
                    }
                    switch(mod)
                    {
                    case PIC_RGB:
                        decdata[curdecposition++] = 0x64;
                        decdata[curdecposition++] = 0x64;
                        decdata[curdecposition++] = 0x64;
                        break;
                    case PIC_RGBA:
                        decdata[curdecposition++] = 0x00;
                        decdata[curdecposition++] = 0x00;
                        decdata[curdecposition++] = 0x00;
                        decdata[curdecposition++] = (0xFF-0x64);
                        break;
                    case PIC_BGRA:
                        decdata[curdecposition++] = 0x00;
                        decdata[curdecposition++] = 0x00;
                        decdata[curdecposition++] = 0x00;
                        decdata[curdecposition++] = (0xFF-0x64);
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            shdfile.read((char*)temp,1);
            i++;
        }

        shdfile.close();
        return decdata;
    }
    else return NULL;
}
unsigned char* ShdDecode::GetGlobleDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod)
{
    switch(mod)
    {
    case PIC_RGB:
    case PIC_BGRA:
    case PIC_RGBA:
        break;
    default:
        return NULL;
    }
    if(index < FileHead.FrameCounts)
    {
        Palette_Colour transcol;
        transcol.Red = 0xFF;
        transcol.Green = 0xFF;
        transcol.Blue = 0xFF;
        transcol.Alpha = 0x00;
        if(Width != NULL) *Width = GetGlobleWidth();
        if(Height != NULL) *Height = GetGlobleHeight();

        unsigned long glbdatalen, width = FileHead.GlobleWidth,
                                  height = FileHead.GlobleHeight;
        unsigned char *decdata, *glbdata;
        switch(mod)
        {
        case PIC_RGB:
            decdata = GetDecodedFrameData(index, (long*)&width, (long*)&height, PIC_RGB);
            glbdatalen = (unsigned long)GetGlobleWidth()*GetGlobleHeight()*3;
            break;
        case PIC_RGBA:
            decdata = GetDecodedFrameData(index, (long*)&width, (long*)&height, PIC_RGBA);
            glbdatalen = (unsigned long)GetGlobleWidth()*GetGlobleHeight()*4;
            break;
        case PIC_BGRA:
            decdata = GetDecodedFrameData(index, (long*)&width, (long*)&height, PIC_BGRA);
            glbdatalen = (unsigned long)GetGlobleWidth()*GetGlobleHeight()*4;
            break;
        default:
            return NULL;
        }
        if(!decdata) return NULL;
        glbdata = (unsigned char*)malloc((size_t)glbdatalen);
        if(!glbdata)
        {
            free(decdata);
            return NULL;
        }

        //assign
        switch(mod)
        {
        case PIC_RGB:
            for(long datidx = 0; datidx < (long)glbdatalen;)//inital
            {
                glbdata[datidx++] = transcol.Red;
                glbdata[datidx++] = transcol.Green;
                glbdata[datidx++] = transcol.Blue;
            }
            for(long hi = 0; hi < GetGlobleHeight(); hi++)
            {
                for(long wi = 0; wi < GetGlobleWidth()*3; wi += 3)
                {
                    if(hi < (long)height && wi < (long)width*3)
                    {
                        glbdata[hi*GetGlobleWidth()*3+wi] = decdata[hi*width*3+wi];
                        glbdata[hi*GetGlobleWidth()*3+wi+1] = decdata[hi*width*3+wi+1];
                        glbdata[hi*GetGlobleWidth()*3+wi+2] = decdata[hi*width*3+wi+2];
                    }
                }
            }
            break;
        case PIC_RGBA:
            for(long datidx = 0; datidx < (long)glbdatalen;)//inital
            {
                glbdata[datidx++] = transcol.Red;
                glbdata[datidx++] = transcol.Green;
                glbdata[datidx++] = transcol.Blue;
                glbdata[datidx++] = 0x00;
            }
            for(long hi = 0; hi < GetGlobleHeight(); hi++)
            {
                for(long wi = 0; wi < GetGlobleWidth()*4; wi += 4)
                {
                    if(hi < (long)height && wi < (long)width*4)
                    {
                        glbdata[hi*GetGlobleWidth()*4+wi] = decdata[hi*width*4+wi];
                        glbdata[hi*GetGlobleWidth()*4+wi+1] = decdata[hi*width*4+wi+1];
                        glbdata[hi*GetGlobleWidth()*4+wi+2] = decdata[hi*width*4+wi+2];
                        glbdata[hi*GetGlobleWidth()*4+wi+3] = decdata[hi*width*4+wi+3];
                    }
                }
            }
            break;
        case PIC_BGRA:
            for(long datidx = 0; datidx < (long)glbdatalen;)//inital
            {
                glbdata[datidx++] = transcol.Blue;
                glbdata[datidx++] = transcol.Green;
                glbdata[datidx++] = transcol.Red;
                glbdata[datidx++] = 0x00;
            }
            for(long hi = 0; hi < GetGlobleHeight(); hi++)
            {
                for(long wi = 0; wi < GetGlobleWidth()*4; wi += 4)
                {
                    if(hi < (long)height && wi < (long)width*4)
                    {
                        glbdata[hi*GetGlobleWidth()*4+wi] = decdata[hi*width*4+wi];
                        glbdata[hi*GetGlobleWidth()*4+wi+1] = decdata[hi*width*4+wi+1];
                        glbdata[hi*GetGlobleWidth()*4+wi+2] = decdata[hi*width*4+wi+2];
                        glbdata[hi*GetGlobleWidth()*4+wi+3] = decdata[hi*width*4+wi+3];
                    }
                }
            }
            break;
        default:
            break;
        }

        free(decdata);
        return glbdata;
    }
    else return NULL;
}
FILOCRGBQUAD* ShdDecode::GetFIDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod)
{
    switch(mod)
    {
    case PIC_RGB:
    case PIC_BGRA:
    case PIC_RGBA:
        break;
    default:
        return NULL;
    }

    if(index < FileHead.FrameCounts)
    {
        unsigned long temppos = 0, datalength, width = FileHead.GlobleWidth,
                      height = FileHead.GlobleHeight, curdecposition = 0;
        unsigned char temp[8];
        std::ifstream shdfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        long decdatalen;
        FILOCRGBQUAD* decdata;
        if(!shdfile.is_open())
        {
            wxMessageBox(wxT("Shd File Open Failed!"));
            return NULL;
        }
        shdfile.seekg(FrameDataBegPos+index*4);
        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        shdfile.seekg(FrameDataBegPos + FileHead.FrameCounts*4 + temppos);
        if(shdfile.eof())
        {
            wxMessageBox(wxT("Shd File Read Error!"));
            shdfile.close();
            return NULL;
        }

        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        datalength = temppos;
        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        width = temppos;
        shdfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        height = temppos;
        shdfile.seekg(8, std::ios_base::cur);
        if(Width != NULL)*Width = width;
        if(Height != NULL)*Height = height;

        decdatalen = width * height;
        decdata = new FILOCRGBQUAD[decdatalen];
        if(decdata == NULL)return NULL;

        for(long datidx = 0; datidx < decdatalen;)
        {
            decdata[datidx].rgbRed = 0xFF;
            decdata[datidx].rgbGreen = 0xFF;
            decdata[datidx].rgbBlue = 0xFF;
            decdata[datidx].rgbReserved = 0x00;
            datidx++;
        }

        shdfile.read((char*)temp,1);
        for(unsigned long i = 0; i < datalength - 20;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                wxMessageBox(wxT("Out of Range"));
                free(decdata);
                shdfile.close();
                return NULL;
            }
            if(temp[0] > (unsigned char)0x80)
            {
                temppos = temp[0] - (unsigned char)0x80;
                for(unsigned char j = 0; j < temppos; j++)
                {
                    switch(mod)
                    {
                    case PIC_RGB:
                        decdata[curdecposition].rgbRed = 0xFF;
                        decdata[curdecposition].rgbGreen = 0xFF;
                        decdata[curdecposition].rgbBlue = 0xFF;
                        decdata[curdecposition].rgbReserved = 0x0;
                        curdecposition++;
                        break;
                    case PIC_RGBA:
                    case PIC_BGRA:
                        decdata[curdecposition].rgbRed = 0xFF;
                        decdata[curdecposition].rgbGreen = 0xFF;
                        decdata[curdecposition].rgbBlue = 0xFF;
                        decdata[curdecposition].rgbReserved = 0x0;
                        curdecposition++;
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            else
            {
                temppos = temp[0];
                for(unsigned char m = 0; m < temppos; m++)
                {
                    if(shdfile.fail())
                    {
                        wxMessageBox(wxT("Shd File Read out of end."));
                        shdfile.close();
                        free(decdata);
                        return NULL;
                    }
                    switch(mod)
                    {
                    case PIC_RGB:
                        decdata[curdecposition].rgbRed = 0x64;
                        decdata[curdecposition].rgbGreen = 0x64;
                        decdata[curdecposition].rgbBlue = 0x64;
                        decdata[curdecposition].rgbReserved = 0xFF;
                        curdecposition++;
                        break;
                    case PIC_RGBA:
                    case PIC_BGRA:
                        decdata[curdecposition].rgbRed = 0x00;
                        decdata[curdecposition].rgbGreen = 0x00;
                        decdata[curdecposition].rgbBlue = 0x00;
                        decdata[curdecposition].rgbReserved = (0xFF-0x64);
                        curdecposition++;
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            shdfile.read((char*)temp,1);
            i++;
        }

        shdfile.close();
        return decdata;
    }
    else return NULL;
}
FILOCRGBQUAD* ShdDecode::GetGlobleFIDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod)
{
    switch(mod)
    {
    case PIC_RGB:
    case PIC_BGRA:
    case PIC_RGBA:
        break;
    default:
        return NULL;
    }
    if(index < FileHead.FrameCounts)
    {
        Palette_Colour transcol;
        transcol.Red = 0xFF;
        transcol.Green = 0xFF;
        transcol.Blue = 0xFF;
        transcol.Alpha = 0x00;
        if(Width != NULL) *Width = GetGlobleWidth();
        if(Height != NULL) *Height = GetGlobleHeight();

        unsigned long glbdatalen, width = FileHead.GlobleWidth,
                                  height = FileHead.GlobleHeight;
        FILOCRGBQUAD *decdata, *glbdata;
        switch(mod)
        {
        case PIC_RGB:
            decdata = GetFIDecodedFrameData(index, (long*)&width, (long*)&height, PIC_RGB);
            glbdatalen = (unsigned long)GetGlobleWidth()*GetGlobleHeight();
            break;
        case PIC_RGBA:
            decdata = GetFIDecodedFrameData(index, (long*)&width, (long*)&height, PIC_RGBA);
            glbdatalen = (unsigned long)GetGlobleWidth()*GetGlobleHeight();
            break;
        case PIC_BGRA:
            decdata = GetFIDecodedFrameData(index, (long*)&width, (long*)&height, PIC_BGRA);
            glbdatalen = (unsigned long)GetGlobleWidth()*GetGlobleHeight();
            break;
        default:
            return NULL;
        }
        if(!decdata) return NULL;
        glbdata = new FILOCRGBQUAD[(size_t)glbdatalen];
        if(!glbdata)
        {
            delete[] decdata;
            return NULL;
        }

        //assign
        switch(mod)
        {
        case PIC_RGB:
        case PIC_RGBA:
        case PIC_BGRA:
            for(long datidx = 0; datidx < (long)glbdatalen; datidx++)//inital
            {
                glbdata[datidx].rgbRed = transcol.Red;
                glbdata[datidx].rgbGreen = transcol.Green;
                glbdata[datidx].rgbBlue = transcol.Blue;
                glbdata[datidx].rgbReserved = 0x00;
            }
            for(long hi = 0; hi < GetGlobleHeight(); hi++)
            {
                for(long wi = 0; wi < GetGlobleWidth(); wi++)
                {
                    if(hi < (long)height && wi < (long)width)
                    {
                        glbdata[hi*GetGlobleWidth()+wi].rgbRed = decdata[hi*width+wi].rgbRed;
                        glbdata[hi*GetGlobleWidth()+wi].rgbGreen = decdata[hi*width+wi].rgbGreen;
                        glbdata[hi*GetGlobleWidth()+wi].rgbBlue = decdata[hi*width+wi].rgbBlue;
                        glbdata[hi*GetGlobleWidth()+wi].rgbReserved = decdata[hi*width+wi].rgbReserved;
                    }
                }
            }
            break;
        default:
            break;
        }
        delete[] decdata;
        return glbdata;
    }
    else return NULL;
}
wxImage ShdDecode::GetFrameImage(const unsigned long index)
{
    if(index < FileHead.FrameCounts)
    {
        long width, height;
        unsigned char *decdata = GetDecodedFrameData(index, &width, &height);
        if(decdata == NULL)
        {
            wxMessageBox(wxString::Format(wxT("Frame %ld read error!"), index+1),
                         wxT("Message"), wxOK|wxICON_ERROR);
            return wxNullImage;
        }
        wxImage img(width,height,decdata);
        return img;
    }
    else return  wxNullImage;
}
