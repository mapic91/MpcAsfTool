#include "MpcDecode.hpp"
#include "ShdDecode.hpp"
#include "wx/image.h"
#include "wx/msgdlg.h"
#include "wx/filename.h"

#include <cstring>
#include <fstream>

MpcDecode::MpcDecode()
{
    Init();
}
MpcDecode::~MpcDecode()
{

}
MpcDecode::MpcDecode(const wxString MpcFilePath)
{
    Init();
    FilePath = MpcFilePath;
}
void MpcDecode::Init()
{
    memset(&FileHead,0, sizeof(MpcFileHead));
    memset(&PaletteData, 0, sizeof(PaletteData));
}
void MpcDecode::SetMpcFile(const wxString MpcFilePath)
{
    FilePath = MpcFilePath;
}
wxString MpcDecode::GetFilePath()
{
    return FilePath;
}
bool MpcDecode::ReadMpcFile()
{
    if(FilePath.IsEmpty()) return false;
    else
    {
        unsigned char temp4b[4],temp;
        unsigned long tempul =0;
        std::ifstream mpcfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        if(!mpcfile.is_open()) return false;

        //Read head
        mpcfile.read(FileHead.VersionInfo, 64);
        if(mpcfile.fail() ||
           strncmp(FileHead.VersionInfo,
                   "MPC File Ver",
                   sizeof("MPC File Ver")-1) != 0)
        {
            return false;
        }
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.FramesDataLengthSum = tempul;
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        if(tempul > 0x7FFFFFFF) tempul = (unsigned long)(-(long)tempul);
        FileHead.GlobleWidth = (long)(0x0 | tempul);
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        if(tempul > 0x7FFFFFFF) tempul = (unsigned long)(-(long)tempul);
        FileHead.GlobleHeight = (long)(0x0 | tempul);
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.FrameCounts = tempul;
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Direction = (long)(0x0 | tempul);
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.ColourCounts = tempul;
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Interval = (long)(0x0 | tempul);
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Bottom = (long)(0x0 | tempul);
		mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        DecodeType = (long)(0x0 | tempul);
        mpcfile.read(FileHead.Reserved, 28);

        PaletteData.Size = FileHead.ColourCounts;

        for(unsigned long i = 0; i < FileHead.ColourCounts; i++)
        {
            mpcfile.read((char*)&temp, 1);
            PaletteData.Data[i].Blue = temp;
            mpcfile.read((char*)&temp, 1);
            PaletteData.Data[i].Green = temp;
            mpcfile.read((char*)&temp, 1);
            PaletteData.Data[i].Red = temp;
            mpcfile.read((char*)&temp, 1);
            PaletteData.Data[i].Alpha = temp;
        }

        FrameDataBegPos = mpcfile.tellg();
        if(!mpcfile.good())return false;
        mpcfile.close();
    }

    InitTransparentColor();
    return true;
}
bool MpcDecode::ReadMpcFile(const wxString MpcFilePath)
{
    FilePath = MpcFilePath;
    return ReadMpcFile();
}
wxString MpcDecode::GetVersionInfo()
{
    return wxString(FileHead.VersionInfo, wxConvLibc);
}
unsigned long MpcDecode::GetFramesDataLengthSum()
{
    return FileHead.FramesDataLengthSum;
}
unsigned long MpcDecode::GetFramesCounts()
{
    return FileHead.FrameCounts;
}
long MpcDecode::GetGlobleWidth()
{
    return FileHead.GlobleWidth;
}
long MpcDecode::GetGlobleHeight()
{
    return FileHead.GlobleHeight;
}
long MpcDecode::GetDirection()
{
    return FileHead.Direction;
}
unsigned long MpcDecode::GetColourCounts()
{
    return FileHead.ColourCounts;
}
unsigned long MpcDecode::GetInterval()
{
    return FileHead.Interval;
}
long MpcDecode::GetBottom()
{
    return FileHead.Bottom;
}
Palette_Colour MpcDecode::GetTransparentColor()
{
    return TransparentColor;
}
void MpcDecode::InitTransparentColor()
{
    unsigned long PalRGB[256] = {0};
    unsigned long tempi1, tempi2, tempi3, tempc;
    bool same = false;
    for(unsigned long pi = 0; pi < PaletteData.Size; pi++)
    {
        PalRGB[pi] |= ((unsigned long)0xFF  & (unsigned long)PaletteData.Data[pi].Red);
        PalRGB[pi] |= (((unsigned long)0xFF & (unsigned long)PaletteData.Data[pi].Green) << 8);
        PalRGB[pi] |= (((unsigned long)0xFF & (unsigned long)PaletteData.Data[pi].Blue) << 16);
        //PalRGB[pi] |= (((unsigned long)0xFF|(unsigned long)PaletteData.Data[pi].Alpha) << 24);
    }
    for(unsigned long trans = 0x5; trans < 0x00FFFFFF; trans++)
    {
        same = false;
        tempi1 = trans%PaletteData.Size;
        tempi2 = (trans+0x20)%PaletteData.Size;
        tempi3 = (trans+0x40)%PaletteData.Size;
        tempc = (unsigned long)0x00FFFFFF & ( (PalRGB[tempi1]*2 + PalRGB[tempi2]*8 + PalRGB[tempi3]*16)/26 + 0x00112233 );
        for(unsigned long fpi = 0; fpi < PaletteData.Size; fpi++)
        {
            if(tempc == PalRGB[fpi])
            {
                same = true;
                break;
            }
        }
        if(!same)
        {
            TransparentColor.Red   = (unsigned char) ((unsigned long)0xFF & tempc);
            TransparentColor.Green = (unsigned char) (((unsigned long)0xFF00 & tempc) >> 8);
            TransparentColor.Blue  = (unsigned char) (((unsigned long)0xFF0000 & tempc) >> 16);
            break;
        }
    }
}
unsigned char* MpcDecode::GetDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod, bool *isTransparent, Palette_Colour *TransparentColor)
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
        Palette_Colour transcol = GetTransparentColor();
        if(TransparentColor != NULL)
        {
            TransparentColor->Red = transcol.Red;
            TransparentColor->Green = transcol.Green;
            TransparentColor->Blue = transcol.Blue;
        }

        unsigned long temppos = 0, datalength, width = FileHead.GlobleWidth,
                      height = FileHead.GlobleHeight, curdecposition = 0;
        unsigned char temp[8];
        std::ifstream mpcfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        long decdatalen;
        unsigned char* decdata;
        if(!mpcfile.is_open())
        {
            return NULL;
        }
        mpcfile.seekg(FrameDataBegPos+index*4);
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        mpcfile.seekg(FrameDataBegPos + FileHead.FrameCounts*4 + temppos);
        if(mpcfile.eof())
        {
            mpcfile.close();
            return NULL;
        }

        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        datalength = temppos;
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        width = temppos;
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        height = temppos;
        mpcfile.seekg(8, std::ios_base::cur);
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
            mpcfile.close();
            return NULL;
        }

        switch(mod)
        {
        case PIC_RGB:
            for(long datidx = 0; datidx < (long)decdatalen;)//inital
            {
                decdata[datidx++] = transcol.Red;
                decdata[datidx++] = transcol.Green;
                decdata[datidx++] = transcol.Blue;
            }
            break;
        case PIC_RGBA:
            for(long datidx = 0; datidx < (long)decdatalen;)//inital
            {
                decdata[datidx++] = transcol.Red;
                decdata[datidx++] = transcol.Green;
                decdata[datidx++] = transcol.Blue;
                decdata[datidx++] = 0x00;
            }
            break;
        case PIC_BGRA:
            for(long datidx = 0; datidx < (long)decdatalen;)//inital
            {
                decdata[datidx++] = transcol.Blue;
                decdata[datidx++] = transcol.Green;
                decdata[datidx++] = transcol.Red;
                decdata[datidx++] = 0x00;
            }
            break;
        default:
            break;
        }

        if(isTransparent != NULL)
        {
            *isTransparent = true;//always transparent
        }
        mpcfile.read((char*)temp,1);

        for(unsigned long i = 0; i < datalength - 20;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                free(decdata);
                mpcfile.close();
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
                        decdata[curdecposition++] = transcol.Red;
                        decdata[curdecposition++] = transcol.Green;
                        decdata[curdecposition++] = transcol.Blue;
                        break;
                    case PIC_RGBA:
                        decdata[curdecposition++] = transcol.Red;
                        decdata[curdecposition++] = transcol.Green;
                        decdata[curdecposition++] = transcol.Blue;
                        decdata[curdecposition++] = 0x0;
                        break;
                    case PIC_BGRA:
                        decdata[curdecposition++] = transcol.Blue;
                        decdata[curdecposition++] = transcol.Green;
                        decdata[curdecposition++] = transcol.Red;
                        decdata[curdecposition++] = 0x0;
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
                    if(mpcfile.fail())
                    {
                        mpcfile.close();
                        free(decdata);
                        return NULL;
                    }
                    mpcfile.read((char*)temp,1);
                    i++;
                    switch(mod)
                    {
                    case PIC_RGB:
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                        break;
                    case PIC_RGBA:
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition++] = 0xFF;
                        break;
                    case PIC_BGRA:
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition++] = 0xFF;
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            mpcfile.read((char*)temp,1);
            i++;
        }

        mpcfile.close();
        return decdata;
    }
    else return NULL;
}
unsigned char* MpcDecode::GetGlobleDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod, bool *isTransparent, Palette_Colour *TransparentColor)
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
        Palette_Colour transcol = GetTransparentColor();
        if(TransparentColor != NULL)
        {
            TransparentColor->Red = transcol.Red;
            TransparentColor->Green = transcol.Green;
            TransparentColor->Blue = transcol.Blue;
        }
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

        if(isTransparent != NULL)
        {
            *isTransparent = true;//always transparent
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
FILOCRGBQUAD* MpcDecode::GetFIDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod, bool *isTransparent, Palette_Colour *TransparentColor)
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
        if(TransparentColor != NULL)
        {
            transcol.Red = TransparentColor->Red;
            transcol.Green = TransparentColor->Green;
            transcol.Blue = TransparentColor->Blue;
            transcol.Alpha =  TransparentColor->Alpha;
        }

        unsigned long temppos = 0, datalength, width = FileHead.GlobleWidth,
                      height = FileHead.GlobleHeight, curdecposition = 0;
        unsigned char temp[8];
        std::ifstream mpcfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        long decdatalen;
        FILOCRGBQUAD* decdata;
        if(!mpcfile.is_open())
        {
            return NULL;
        }
        mpcfile.seekg(FrameDataBegPos+index*4);
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        mpcfile.seekg(FrameDataBegPos + FileHead.FrameCounts*4 + temppos);
        if(mpcfile.eof())
        {
            mpcfile.close();
            return NULL;
        }

        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        datalength = temppos;
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        width = temppos;
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        height = temppos;
        mpcfile.seekg(8, std::ios_base::cur);
        if(Width != NULL)*Width = width;
        if(Height != NULL)*Height = height;

        decdatalen = width * height;
        decdata = new FILOCRGBQUAD[decdatalen];
        if(decdata == NULL)return NULL;

        for(long datidx = 0; datidx < decdatalen;)
        {
            decdata[datidx].rgbRed = transcol.Red;
            decdata[datidx].rgbGreen = transcol.Green;
            decdata[datidx].rgbBlue = transcol.Blue;
            decdata[datidx].rgbReserved = 0x00;
            datidx++;
        }

        if(isTransparent != NULL)
        {
            *isTransparent = true;//always transparent
        }
        mpcfile.read((char*)temp,1);

        for(unsigned long i = 0; i < datalength - 20;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                delete[] decdata;
                mpcfile.close();
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
                        decdata[curdecposition].rgbRed = transcol.Red;
                        decdata[curdecposition].rgbGreen = transcol.Green;
                        decdata[curdecposition].rgbBlue = transcol.Blue;
                        decdata[curdecposition].rgbReserved = 0x0;
                        curdecposition++;
                        break;
                    case PIC_RGBA:
                    case PIC_BGRA:
                        decdata[curdecposition].rgbRed = transcol.Red;
                        decdata[curdecposition].rgbGreen = transcol.Green;
                        decdata[curdecposition].rgbBlue = transcol.Blue;
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
                    if(mpcfile.fail())
                    {
                        mpcfile.close();
                        delete[] decdata;
                        return NULL;
                    }
                    mpcfile.read((char*)temp,1);
                    i++;
                    switch(mod)
                    {
                    case PIC_RGB:
                        decdata[curdecposition].rgbRed = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition].rgbGreen = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition].rgbBlue = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition].rgbReserved = 0xFF;
                        curdecposition++;
                        break;
                    case PIC_RGBA:
                    case PIC_BGRA:
                        decdata[curdecposition].rgbRed = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition].rgbGreen = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition].rgbBlue = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition].rgbReserved = 0xFF;
                        curdecposition++;
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            mpcfile.read((char*)temp,1);
            i++;
        }

        mpcfile.close();
        return decdata;
    }
    else return NULL;
}
FILOCRGBQUAD* MpcDecode::GetGlobleFIDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod, bool *isTransparent, Palette_Colour *TransparentColor)
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
        Palette_Colour transcol = GetTransparentColor();
        if(TransparentColor != NULL)
        {
            TransparentColor->Red = transcol.Red;
            TransparentColor->Green = transcol.Green;
            TransparentColor->Blue = transcol.Blue;
        }
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

        if(isTransparent != NULL)
        {
            *isTransparent = true;//always transparent
        }

        //assign
        switch(mod)
        {
        case PIC_RGB:case PIC_RGBA:case PIC_BGRA:
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
wxImage MpcDecode::GetFrameImage(const unsigned long index, bool ShdIncluded)
{
    if(index < FileHead.FrameCounts)
    {
        long width, height, shdcurpos, colpos, imgpos;
        ShdDecode shddecode;
        bool shdicl = false;
        unsigned char *shddata = NULL,*decdata = NULL, *imgdata = NULL;
        wxString shdpath;

        imgdata = (unsigned char*)malloc((size_t)GetGlobleWidth()*GetGlobleHeight()*3);
        if(!imgdata) return wxNullImage;

        if(ShdIncluded)
        {
            shdpath = wxFileName::FileName(FilePath).GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);
            shdpath += wxFileName::FileName(FilePath).GetName();
            shdpath += wxT(".shd");
            if(wxFileName::FileExists(shdpath))
            {
                if(shddecode.ReadShdFile(shdpath))
                {
                    if(shddecode.GetGlobleWidth() == GetGlobleWidth() &&
                            shddecode.GetGlobleHeight() == GetGlobleHeight())
                    {
                        shddata = shddecode.GetGlobleDecodedFrameData(index);
                        if(shddata)shdicl = true;
                    }
                }
            }
        }


        decdata = GetGlobleDecodedFrameData(index, &width, &height, PIC_RGBA);
        if(decdata == NULL)
        {
            if(imgdata)
            {
                free(imgdata);
                imgdata = NULL;
            }
            return wxNullImage;
        }


        if(shdicl)
        {
            shdcurpos = 0;
            colpos = 0;
            imgpos = 0;
            for(long int sidx = 0; sidx < GetGlobleWidth()*GetGlobleHeight(); sidx++)
            {
                if(shddata[shdcurpos] == 0xFF)//fill transparent color
                {
                    imgdata[imgpos] = TransparentColor.Red;
                    imgdata[imgpos+1] = TransparentColor.Green;
                    imgdata[imgpos+2] = TransparentColor.Blue;
                }
                else
                {
                    imgdata[imgpos] = shddata[shdcurpos];
                    imgdata[imgpos+1] = shddata[shdcurpos+1];
                    imgdata[imgpos+2] = shddata[shdcurpos+2];
                }

                if(decdata[colpos+3] != 0)//fill color
                {
                    imgdata[imgpos] = decdata[colpos];
                    imgdata[imgpos+1] = decdata[colpos+1];
                    imgdata[imgpos+2] = decdata[colpos+2];
                }
                shdcurpos += 3;
                colpos += 4;
                imgpos += 3;
            }
            free(decdata);
            free(shddata);
        }
        else
        {
            colpos = 0;
            imgpos = 0;
            for(long int sidx = 0; sidx < GetGlobleWidth()*GetGlobleHeight(); sidx++)
            {
                if(decdata[colpos+3] == 0)//fill transparent color
                {
                    imgdata[imgpos] = TransparentColor.Red;
                    imgdata[imgpos+1] = TransparentColor.Green;
                    imgdata[imgpos+2] = TransparentColor.Blue;
                }
                else//fill color
                {
                    imgdata[imgpos] = decdata[colpos];
                    imgdata[imgpos+1] = decdata[colpos+1];
                    imgdata[imgpos+2] = decdata[colpos+2];
                }
                imgpos += 3;
                colpos += 4;
            }
            free(decdata);
        }

#ifdef DODEBUG
        free(imgdata);
        imgdata = GetGlobleDecodedFrameData(index);
#endif // define

        wxImage img(GetGlobleWidth(),GetGlobleHeight(),imgdata);
        return img;
    }
    else return  wxNullImage;
}
