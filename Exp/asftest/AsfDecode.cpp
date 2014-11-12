#include "AsfDecode.hpp"
#include "wx/image.h"
#include "wx/msgdlg.h"

#include <cstring>
#include <fstream>

AsfDecode::AsfDecode()
{
    Init();
}
AsfDecode::~AsfDecode()
{

}
AsfDecode::AsfDecode(const wxString AsfFilePath)
{
    Init();
    FilePath = AsfFilePath;
}
void AsfDecode::Init()
{
    memset(&FileHead,0, sizeof(AsfFileHead));
    memset(&PaletteData, 0, sizeof(PaletteData));
}
void AsfDecode::SetAsfFile(const wxString AsfFilePath)
{
    FilePath = AsfFilePath;
}
wxString AsfDecode::GetFilePath()
{
    return FilePath;
}
bool AsfDecode::ReadAsfFile()
{
    if(FilePath.IsEmpty()) return false;
    else
    {
        unsigned char temp4b[4],temp;
        unsigned long tempul =0;
        std::ifstream asffile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        if(!asffile.is_open()) return false;

        //Read head
        asffile.read(FileHead.VersionInfo, 16);
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.GlobleWidth = (long)(0x0 | tempul);
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.GlobleHeight = (long)(0x0 | tempul);
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.FrameCounts = tempul;
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Direction = (long)(0x0 | tempul);
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.ColourCounts = tempul;
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Interval = (long)(0x0 | tempul);
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Bottom = (long)(0x0 | tempul);
        asffile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
        FileHead.Left = (long)(0x0 | tempul);
        asffile.read(FileHead.Reserved, 16);

        PaletteData.Size = FileHead.ColourCounts;

        for(unsigned long i = 0; i < FileHead.ColourCounts; i++)
        {
            asffile.read((char*)&temp, 1);
            PaletteData.Data[i].Blue = temp;
            asffile.read((char*)&temp, 1);
            PaletteData.Data[i].Green = temp;
            asffile.read((char*)&temp, 1);
            PaletteData.Data[i].Red = temp;
            asffile.read((char*)&temp, 1);
            PaletteData.Data[i].Alpha = temp;
        }

        FrameDataBegPos = asffile.tellg();
        if(!asffile.good())return false;
        asffile.close();
    }

    InitTransparentColor();
    return true;
}
bool AsfDecode::ReadAsfFile(const wxString AsfFilePath)
{
    FilePath = AsfFilePath;
    return ReadAsfFile();
}
wxString AsfDecode::GetVersionInfo()
{
    return wxString(FileHead.VersionInfo, wxConvLibc);
}
unsigned long AsfDecode::GetFramesCounts()
{
    return FileHead.FrameCounts;
}
long AsfDecode::GetGlobleWidth()
{
    return FileHead.GlobleWidth;
}
long AsfDecode::GetGlobleHeight()
{
    return FileHead.GlobleHeight;
}
long AsfDecode::GetDirection()
{
    return FileHead.Direction;
}
unsigned long AsfDecode::GetColourCounts()
{
    return FileHead.ColourCounts;
}
unsigned long AsfDecode::GetInterval()
{
    return FileHead.Interval;
}
long AsfDecode::GetBottom()
{
    return FileHead.Bottom;
}
long AsfDecode::GetLeft()
{
    return FileHead.Left;
}
Palette_Colour AsfDecode::GetTransparentColor()
{
    return TransparentColor;
}
void AsfDecode::InitTransparentColor()
{
    unsigned long PalRGB[256] = {0};
    unsigned long tempi1, tempi2, tempi3, teasf;
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
        teasf = (unsigned long)0x00FFFFFF & ( (PalRGB[tempi1]*2 + PalRGB[tempi2]*8 + PalRGB[tempi3]*16)/26 + 0x00112233 );
        for(unsigned long fpi = 0; fpi < PaletteData.Size; fpi++)
        {
            if(teasf == PalRGB[fpi])
            {
                same = true;
                break;
            }
        }
        if(!same)
        {
            TransparentColor.Red   = (unsigned char) ((unsigned long)0xFF & teasf);
            TransparentColor.Green = (unsigned char) (((unsigned long)0xFF00 & teasf) >> 8);
            TransparentColor.Blue  = (unsigned char) (((unsigned long)0xFF0000 & teasf) >> 16);
            break;
        }
    }
}
unsigned char* AsfDecode::GetDecodedFrameData(const unsigned long index, long* Width, long* Height,
        COLOUR_MODLE mod, bool *isTransparent, Palette_Colour *TransparentColor)
{
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
        unsigned char temp[8], alpha;
        std::ifstream asffile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        long decdatalen;
        unsigned char* decdata;
        if(!asffile.is_open())
        {
            wxMessageBox(wxT("Asf File Open Failed!"));
            return NULL;
        }
        asffile.seekg(FrameDataBegPos+index*8);
        asffile.read((char*)temp, 8);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        asffile.seekg(temppos);
        if(asffile.eof())
        {
            wxMessageBox(wxT("Asf File Read Error!"));
            asffile.close();
            return NULL;
        }
        temppos = 0;
        temppos |= ( ((unsigned long)temp[4] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[5] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[6] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[7] & (unsigned long)0xFF) << 24 );
        datalength = temppos;

        *Width = width;
        *Height = height;
        switch(mod)
        {
        case ASF_RGB:
            decdatalen = width * height * 3;
            break;
        case ASF_RGBA:
        case ASF_BGRA:
            decdatalen = width * height * 4;
            break;
        default:
            return NULL;
        }
        decdata = (unsigned char*)malloc((size_t)decdatalen);
        if(decdata == NULL)
        {
            asffile.close();
            wxMessageBox(wxT("malloc failed!"));
            return NULL;
        }

        for(long datidx = 0; datidx < decdatalen;)
        {
            decdata[datidx++] = transcol.Red;
            decdata[datidx++] = transcol.Green;
            decdata[datidx++] = transcol.Blue;
            switch(mod)
            {
            case ASF_RGBA: case ASF_BGRA:
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
        asffile.read((char*)temp,2);
        for(unsigned long i = 0; i < datalength - 20;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                wxMessageBox(wxT("Out of Range"));
                free(decdata);
                asffile.close();
                return NULL;
            }
            if(temp[1] == (unsigned char)0x00)
            {
                temppos = temp[0];
                for(unsigned char j = 0; j < temppos; j++)
                {
                    switch(mod)
                    {
                    case ASF_RGB:
                        decdata[curdecposition++] = transcol.Red;
                        decdata[curdecposition++] = transcol.Green;
                        decdata[curdecposition++] = transcol.Blue;
                        break;
                    case ASF_RGBA:
                        decdata[curdecposition++] = transcol.Red;
                        decdata[curdecposition++] = transcol.Green;
                        decdata[curdecposition++] = transcol.Blue;
                        decdata[curdecposition++] = 0x0;
                        break;
                    case ASF_BGRA:
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
                    if(asffile.fail())
                    {
                        wxMessageBox(wxT("Asf File Read out of end."));
                        asffile.close();
                        free(decdata);
                        return NULL;
                    }
                    asffile.read((char*)temp,1);
                    i++;
                    switch(mod)
                    {
                    case ASF_RGB:
                        decdata[curdecposition++] = (unsigned char)(((double)PaletteData.Data[temp[0]].Red)*((double)alpha/(double)0xFF) +
                                                                    ((double)transcol.Red)*((double)(0xFF-alpha)/(double)0xFF));
                        decdata[curdecposition++] = (unsigned char)(((double)PaletteData.Data[temp[0]].Green)*((double)alpha/(double)0xFF) +
                                                                    ((double)transcol.Green)*((double)(0xFF-alpha)/(double)0xFF));
                        decdata[curdecposition++] = (unsigned char)(((double)PaletteData.Data[temp[0]].Blue)*((double)alpha/(double)0xFF) +
                                                                    ((double)transcol.Blue)*((double)(0xFF-alpha)/(double)0xFF));
                        break;
                    case ASF_RGBA:
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                        decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                        decdata[curdecposition++] = alpha;
                        break;
                    case ASF_BGRA:
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
            asffile.read((char*)temp,2);
            i += 2;
        }

        asffile.close();
        return decdata;
    }
    else return NULL;
}
wxImage AsfDecode::GetFrameImage(const unsigned long index)
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
