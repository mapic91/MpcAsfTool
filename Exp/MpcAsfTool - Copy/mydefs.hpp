#ifndef MYDEFS_HPP_INCLUDED
#define MYDEFS_HPP_INCLUDED

const unsigned long FrameDataHeadLength = 14;

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
struct ShdFileHead
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

struct AsfFileHead
{
    char VersionInfo[16];//"Asf File Verx.xx"
    long GlobleWidth;
    long GlobleHeight;
    unsigned long FrameCounts;
    long Direction;
    unsigned long ColourCounts;
    long Interval;
    long Bottom;
    long Left;
    char Reserved[16];//Must be 0
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
    char Reserved[8];//Must be 0
    unsigned char* Data;
};

#endif // MYDEFS_HPP_INCLUDED
