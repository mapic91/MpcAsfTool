#include "SprDecode.hpp"
#include "wx/image.h"
#include "wx/msgdlg.h"
#include "Utils.hpp"

#include <cstring>
#include <fstream>

unsigned short toUShort(char *in)
{
	unsigned short tmp = 0;
	tmp |= (( (unsigned short)in[0] ) & (unsigned short)0xFF);
	tmp |= (( (unsigned short)in[1] ) & (unsigned short)0xFF) << 8;
	return tmp;
}

SprDecode::SprDecode()
{
    Init();
}
SprDecode::~SprDecode()
{

}
SprDecode::SprDecode(const wxString SprFilePath)
{
    Init();
    FilePath = SprFilePath;
}
void SprDecode::Init()
{
    memset(&FileHead,0, sizeof(SprFileHead));
    memset(&PaletteData, 0, sizeof(PaletteData));
}
void SprDecode::SetSprFile(const wxString SprFilePath)
{
    FilePath = SprFilePath;
}
wxString SprDecode::GetFilePath()
{
    return FilePath;
}
bool SprDecode::ReadSprFile()
{
    if(FilePath.IsEmpty()) return false;
    else
    {
        unsigned char temp;
        std::ifstream infile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        if(!infile.is_open()) return false;

        //Read head
        infile.read(FileHead.VersionInfo, 4);
        if(infile.fail() ||
           strncmp(FileHead.VersionInfo, "SPR", sizeof("SPR")-1) != 0)
        {
            return false;
        }
        char temp28[28];
        infile.read(temp28, 28);
        FileHead.GlobleWidth = toUShort(temp28);
        FileHead.GlobleHeight = toUShort(temp28 + 2);
        FileHead.OffX  = toUShort(temp28 + 4);
        FileHead.OffY  = toUShort(temp28 + 6);
        FileHead.FrameCounts  = toUShort(temp28 + 8);
        FileHead.ColourCounts  = toUShort(temp28 + 10);
        FileHead.DirectionCount = toUShort(temp28 + 12);
        FileHead.Interval = toUShort(temp28 + 14);

        PaletteData.Size = FileHead.ColourCounts;

        for(unsigned long i = 0; i < FileHead.ColourCounts; i++)
        {
            infile.read((char*)&temp, 1);
            PaletteData.Data[i].Red = temp;
            infile.read((char*)&temp, 1);
            PaletteData.Data[i].Green = temp;
            infile.read((char*)&temp, 1);
            PaletteData.Data[i].Blue = temp;
        }

        FrameDataBegPos = infile.tellg();
        if(!infile.good())return false;
        infile.close();
    }

    //InitTransparentColor();
    return true;
}
bool SprDecode::ReadSprFile(const wxString SprFilePath)
{
    FilePath = SprFilePath;
    return ReadSprFile();
}
wxString SprDecode::GetVersionInfo()
{
    return wxString(FileHead.VersionInfo, wxConvLibc);
}
unsigned long SprDecode::GetFramesCounts()
{
    return FileHead.FrameCounts;
}
long SprDecode::GetGlobleWidth()
{
    return FileHead.GlobleWidth;
}
long SprDecode::GetGlobleHeight()
{
    return FileHead.GlobleHeight;
}
long SprDecode::GetDirection()
{
    return FileHead.DirectionCount;
}
unsigned long SprDecode::GetColourCounts()
{
    return FileHead.ColourCounts;
}
unsigned long SprDecode::GetInterval()
{
    return FileHead.Interval;
}
long SprDecode::GetBottom()
{
   return FileHead.OffY;
}
long SprDecode::GetLeft()
{
   return FileHead.OffX;
}
Palette_Colour SprDecode::GetTransparentColor()
{
    return TransparentColor;
}
void SprDecode::InitTransparentColor()
{
    TransparentColor.Red = 0x00;
    TransparentColor.Green = 0x00;
    TransparentColor.Blue = 0x00;
    TransparentColor.Alpha = 0x00;
}
unsigned char* SprDecode::GetDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod, bool *isTransparent, Palette_Colour *TransparentColor, unsigned char transmask,
        int *offX, int *offY)
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
            transcol.Red = TransparentColor->Red;
            transcol.Green = TransparentColor->Green;
            transcol.Blue = TransparentColor->Blue;
            //transcol.Alpha =  TransparentColor->Alpha;
        }

        unsigned long temppos = 0, datalength, width = FileHead.GlobleWidth,
                      height = FileHead.GlobleHeight, curdecposition = 0;
        unsigned char temp[8], alpha;
        std::ifstream file(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        long decdatalen;
        unsigned char* decdata;
        if(!file.is_open())
        {
            return NULL;
        }
        file.seekg(FrameDataBegPos+index*8);
        file.read((char*)temp, 8);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        temppos += FrameDataBegPos + 8 * FileHead.FrameCounts;
        file.seekg(temppos);
        if(file.eof())
        {
            file.close();
            return NULL;
        }
        temppos = 0;
        temppos |= ( ((unsigned long)temp[4] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[5] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[6] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[7] & (unsigned long)0xFF) << 24 );
        datalength = temppos;


		file.read((char*)temp, 8);
		width = toUShort((char*)temp);
		height = toUShort((char*)temp+2);
        if(Width != NULL)*Width = width;
        if(Height != NULL)*Height = height;
        if(offX != NULL)*offX = toUShort((char*)temp+4);
        if(offY != NULL)*offY = toUShort((char*)temp+6);
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
            file.close();
            return NULL;
        }

        for(long datidx = 0; datidx < decdatalen;)
        {
            switch(mod)
            {
            case PIC_RGB:
                decdata[datidx++] = transcol.Red;
                decdata[datidx++] = transcol.Green;
                decdata[datidx++] = transcol.Blue;
                break;
            case PIC_RGBA:
                decdata[datidx++] = transcol.Red;
                decdata[datidx++] = transcol.Green;
                decdata[datidx++] = transcol.Blue;
                decdata[datidx++] = 0x00;
                break;
            case PIC_BGRA:
                decdata[datidx++] = transcol.Blue;
                decdata[datidx++] = transcol.Green;
                decdata[datidx++] = transcol.Red;
                decdata[datidx++] = 0x00;
                break;
            default:
                break;
            }
        }


        if(isTransparent != NULL)
        {
            *isTransparent = true;//always transparent
        }
        file.read((char*)temp,2);
        for(unsigned long i = 0; i < datalength - 8;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                free(decdata);
                file.close();
                return NULL;
            }
            if(temp[1] == (unsigned char)0x00)
            {
                temppos = temp[0];
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
                alpha = temp[1];
                for(unsigned char m = 0; m < temppos; m++)
                {
                    if(file.fail())
                    {
                        file.close();
                        free(decdata);
                        return NULL;
                    }
                    file.read((char*)temp,1);
                    i++;
                    switch(mod)
                    {
                    case PIC_RGB:
                        if(alpha < transmask)
                        {
                             decdata[curdecposition++] = transcol.Red;
                             decdata[curdecposition++] = transcol.Green;
                             decdata[curdecposition++] = transcol.Blue;
                        }
                        else
                        {
                            decdata[curdecposition++] = (unsigned char)(((double)PaletteData.Data[temp[0]].Red)*((double)alpha/(double)0xFF) +
                            ((double)transcol.Red)*((double)(0xFF-alpha)/(double)0xFF));
                            decdata[curdecposition++] = (unsigned char)(((double)PaletteData.Data[temp[0]].Green)*((double)alpha/(double)0xFF) +
                            ((double)transcol.Green)*((double)(0xFF-alpha)/(double)0xFF));
                            decdata[curdecposition++] = (unsigned char)(((double)PaletteData.Data[temp[0]].Blue)*((double)alpha/(double)0xFF) +
                            ((double)transcol.Blue)*((double)(0xFF-alpha)/(double)0xFF));
                        }
                        break;
                    case PIC_RGBA:
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition++] = alpha;
                        break;
                    case PIC_BGRA:
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition++] = alpha;
                        break;
                    default:
                        //can't be here
                        return NULL;
                    }
                }
            }
            file.read((char*)temp,2);
            i += 2;
        }

        file.close();
        return decdata;
    }
    else return NULL;
}
FILOCRGBQUAD* SprDecode::GetFIDecodedFrameData(const unsigned long index)
{
	int offx, offy;
	long width, height;
    unsigned char* data = GetDecodedFrameData(index, &width, &height, PIC_RGBA,
											NULL,
											NULL,
											0,
											&offx,
											&offy);

	if(data == NULL) return NULL;
	long globalWidth = GetGlobleWidth(), globalHeight = GetGlobleHeight();
//	wxMessageBox(wxString::Format("gw:%d,gh:%d,w:%d,h:%d,ox:%d, oy:%d", globalWidth,
//								globalHeight,width,height,offx,offy));
	return RGBAtoFIRGBA(data, width, height, globalWidth, globalHeight, offx, offy);
}
wxImage SprDecode::GetFrameImage(const unsigned long index, unsigned char transmask)
{
    if(index < FileHead.FrameCounts)
    {
        long width, height;
        unsigned char *decdata = GetDecodedFrameData(index, &width, &height, PIC_RGB, NULL, NULL, transmask);
        if(decdata == NULL)
        {
            return wxNullImage;
        }
        wxImage img(width,height,decdata);
        return img;
    }
    else return  wxNullImage;
}
