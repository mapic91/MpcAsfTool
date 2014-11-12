#ifndef ASFDECODE_HPP_INCLUDED
#define ASFDECODE_HPP_INCLUDED

#include "wx/string.h"
#include "wx/image.h"

#include "mydefs.hpp"

#include "FreeImage.h"

class AsfDecode
{
public:
    enum COLOUR_MODLE{PIC_RGB,PIC_RGBA, PIC_BGRA};
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
    unsigned char* GetDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL,
                                       Palette_Colour *TransparentColor = NULL, unsigned char transmask = 0);
    unsigned char* GetGlobleDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL,
                                       Palette_Colour *TransparentColor = NULL, unsigned char transmask = 0)
    {
        return GetDecodedFrameData(index, Width, Height, mod, isTransparent, TransparentColor, transmask);
    }

    //transmask - pixel alpha value is less than transmask consider tottle transparent
    FILOCRGBQUAD* GetFIDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL,
                                       Palette_Colour *TransparentColor = NULL, unsigned char transmask = 0);
    FILOCRGBQUAD* GetGlobleFIDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL,
                                       Palette_Colour *TransparentColor = NULL, unsigned char transmask = 0)
    {
        return GetFIDecodedFrameData(index, Width, Height, mod, isTransparent, TransparentColor, transmask);
    }
    wxImage GetFrameImage(const unsigned long index, unsigned char transmask = 0);


    Palette PaletteData;
private:

    void InitTransparentColor();

    Palette_Colour TransparentColor;
    AsfFileHead FileHead;
    wxString FilePath;
    unsigned long FrameDataBegPos;
    //FrameData* FramesDataBlock;

};

#endif // ASFDECODE_HPP_INCLUDED
