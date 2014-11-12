#include "MpcDecode.hpp"
#include "Little_Big_Endian_Convert.hpp"
#include "wx/image.h"
#include "wx/msgdlg.h"

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
        FileHead.GlobleWidth = (long)(0x0 | tempul);
        mpcfile.read((char*)temp4b, 4);
        tempul = 0;
        tempul |= ( ((unsigned long)temp4b[0] & (unsigned long)0xFF) );
        tempul |= ( ((unsigned long)temp4b[1] & (unsigned long)0xFF) << 8 );
        tempul |= ( ((unsigned long)temp4b[2] & (unsigned long)0xFF) << 16 );
        tempul |= ( ((unsigned long)temp4b[3] & (unsigned long)0xFF) << 24 );
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
        mpcfile.read(FileHead.Reserved, 32);

        PaletteData.Size = LittoLocUL(FileHead.ColourCounts);

        for(unsigned long i = 0; i < LittoLocUL(FileHead.ColourCounts); i++)
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
        mpcfile.close();
    }
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
    return LittoLocUL(FileHead.FramesDataLengthSum);
}
unsigned long MpcDecode::GetFramesCounts()
{
    return LittoLocUL(FileHead.FrameCounts);
}
long MpcDecode::GetGlobleWidth()
{
    return LittoLocL(FileHead.GlobleWidth);
}
long MpcDecode::GetGlobleHeight()
{
    return LittoLocL(FileHead.GlobleHeight);
}
long MpcDecode::GetDirection()
{
    return LittoLocL(FileHead.Direction);
}
unsigned long MpcDecode::GetColourCounts()
{
    return LittoLocUL(FileHead.ColourCounts);
}
unsigned long MpcDecode::GetInterval()
{
    return LittoLocUL(FileHead.Interval);
}
long MpcDecode::GetBottom()
{
    return LittoLocL(FileHead.Bottom);
}
unsigned char* MpcDecode::GetDecodedFrameData(const unsigned long index, long* Width, long* Height)
{
    if(index < LittoLocUL(FileHead.FrameCounts))
    {
        unsigned long temppos = 0, datalength, width, height, curdecposition = 0;
        unsigned char temp[4];
        std::ifstream mpcfile(FilePath.char_str(), std::ios_base::binary|std::ios_base::in);
        if(!mpcfile.is_open())
        {
            wxMessageBox(wxT("Mpc File Open Failed!"));
            return NULL;
        }
        mpcfile.seekg(FrameDataBegPos+index*4);
        mpcfile.read((char*)temp, 4);
        temppos = 0;
        temppos |= ( ((unsigned long)temp[0] & (unsigned long)0xFF) );
        temppos |= ( ((unsigned long)temp[1] & (unsigned long)0xFF) << 8 );
        temppos |= ( ((unsigned long)temp[2] & (unsigned long)0xFF) << 16 );
        temppos |= ( ((unsigned long)temp[3] & (unsigned long)0xFF) << 24 );
        mpcfile.seekg(FrameDataBegPos + LittoLocUL(FileHead.FrameCounts)*4 + temppos);
        if(mpcfile.eof())
        {
            wxMessageBox(wxT("Mpc File Read Error!"));
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
        *Width = width;
        *Height = height;

        long decdatalen = width * height * 3;
        unsigned char* decdata = (unsigned char*)malloc((size_t)decdatalen);
        if(decdata == NULL)
        {
            mpcfile.close();
            wxMessageBox(wxT("malloc failed!"));
            return NULL;
        }

        for(unsigned long i = 0; i < datalength - 20;)
        {
            if(curdecposition > (unsigned long)decdatalen)
            {
                wxMessageBox(wxT("Out of Range"));
                free(decdata);
                mpcfile.close();
                return NULL;
            }
            mpcfile.read((char*)temp,1);
            i++;
            if(temp[0] > (unsigned char)0x80)
            {
                temppos = temp[0] - (unsigned char)0x80;
                for(unsigned char j = 0; j < temppos; j++)
                {
                    decdata[curdecposition++] = 0xFF;
                    decdata[curdecposition++] = 0xFF;
                    decdata[curdecposition++] = 0xFF;
                }
            }
            else
            {
                temppos = temp[0];
                for(unsigned char m = 0; m < temppos; m++)
                {
                    if(mpcfile.fail())
                    {
                        wxMessageBox(wxT("Mpc File Read out of end."));
                        mpcfile.close();
                        free(decdata);
                        return NULL;
                    }
                    mpcfile.read((char*)temp,1);
                    i++;
                    decdata[curdecposition++] = PaletteData.Data[temp[0]].Red;
                    decdata[curdecposition++] = PaletteData.Data[temp[0]].Green;
                    decdata[curdecposition++] = PaletteData.Data[temp[0]].Blue;
                }
            }
        }

        mpcfile.close();
        return decdata;
    }
    else return NULL;
}
wxImage MpcDecode::GetFrameImage(const unsigned long index)
{
    if(index < LittoLocUL(FileHead.FrameCounts))
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
