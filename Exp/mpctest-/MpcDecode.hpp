#ifndef MPCDECODE_HPP_INCLUDED
#define MPCDECODE_HPP_INCLUDED

#include "wx/string.h"
#include "wx/image.h"

struct MpcFileHead
{
    char VersionInfo[64];//"MPC File Ver2.0"
    unsigned long FramesDataLengthSum;
    long GlobleWidth;
    long GlobleHeight;
    unsigned long FrameCounts;
    long Direction;
    unsigned long ColourCounts;
    long Interval;
    long Bottom;
    char Reserved[32];//Must be 0
};

struct Palette_Colour
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Alpha;
};

struct Palette
{
    unsigned long Size;//Palette_Colour counts, must less than 257
    Palette_Colour Data[256];
};

struct FrameData
{
    unsigned long DataLength;
    long Width;
    long Height;
    char Reserved[2];//Must be 0
    unsigned char* Data;
};

class MpcDecode
{
public:
    MpcDecode(){}
    MpcDecode(const wxString MpcFilePath);
    void SetMpcFile(const wxString MpcFilePath);
    bool ReadMpcFile();
    bool ReadMpcFile(const wxString MpcFilePath);
    wxString GetVersionInfo();
    unsigned long GetFramesDataLengthSum();
    unsigned long GetFramesCounts();
    unsigned long GetFrameDataLength(const unsigned long index);
    long GetGlobleWidth();
    long GetGlobleHeight();
    long GetFrameWidth(const unsigned long index);
    long GetFrameHeight(const unsigned long index);
    long GetDirection();
    unsigned long GetColourCounts();
    unsigned long GetInterval();
    long GetBottom();
    Palette* GetPalette();
    FrameData* GetFrameData(const unsigned long index);
    wxImage GetFrameImage(const unsigned long index);

private:
    Palette* palette;
    wxString FilePath,VersionInfo;
    unsigned long FramesDataLengthSum,FramesCounts,FrameDataLength,
        GlobleWidth,GlobleHeight,Direction,ColourCounts,Interval,Bottom;
    FrameData* FramesData;

};

#endif // MPCDECODE_HPP_INCLUDED
