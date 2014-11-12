#ifndef MPCDECODE_HPP_INCLUDED
#define MPCDECODE_HPP_INCLUDED

#include "wx/string.h"
#include "wx/image.h"

const unsigned long FrameDataHeadLength = 14;

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

/*
struct FrameData
{
    unsigned long DataLength;
    long Width;
    long Height;
    char Reserved[8];//Must be 0
    unsigned char* Data;
};
*/

class AsfDecode
{
public:
    enum COLOUR_MODLE{ASF_RGB,ASF_RGBA, ASF_BGRA};
    AsfDecode();
    ~AsfDecode();
    void Init();
    AsfDecode(const wxString AsfFilePath);
    void SetAsfFile(const wxString AsfFilePath);
    wxString GetFilePath();
    bool ReadAsfFile();
    bool ReadAsfFile(const wxString AsfFilePath);
    wxString GetVersionInfo();
    unsigned long GetFramesCounts();
    //unsigned long GetFrameDataLength(const unsigned long index);
    long GetGlobleWidth();
    long GetGlobleHeight();
    //long GetFrameWidth(const unsigned long index);
    //long GetFrameHeight(const unsigned long index);
    long GetDirection();
    unsigned long GetColourCounts();
    unsigned long GetInterval();
    long GetBottom();
    long GetLeft();

    //data must be free() if won't use anymore
    Palette_Colour GetTransparentColor();
    unsigned char* GetDecodedFrameData(const unsigned long index, long* Width, long* Height,
                                       COLOUR_MODLE mod = ASF_RGB,bool *isTransparent = NULL, Palette_Colour *TransparentColor = NULL);

    wxImage GetFrameImage(const unsigned long index);


    Palette PaletteData;


private:

    void InitTransparentColor();

    Palette_Colour TransparentColor;
    AsfFileHead FileHead;
    wxString FilePath;
    unsigned long FrameDataBegPos;
    //FrameData* FramesDataBlock;

};

#endif // MPCDECODE_HPP_INCLUDED
