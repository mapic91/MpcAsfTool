#ifndef SPRDECODE_HPP_INCLUDED
#define SPRDECODE_HPP_INCLUDED

#include "wx/string.h"
#include "wx/image.h"

#include "mydefs.hpp"

#include "FreeImage.h"

class SprDecode
{
public:
    enum COLOUR_MODLE{PIC_RGB,PIC_RGBA, PIC_BGRA};
    SprDecode();
    ~SprDecode();
    void Init();
    SprDecode(const wxString SprFilePath);
    void SetSprFile(const wxString SprFilePath);
    wxString GetFilePath();
    bool ReadSprFile();
    bool ReadSprFile(const wxString SprFilePath);
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
    unsigned char* GetDecodedFrameData(const unsigned long index, int* Width = NULL, int* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL,
                                       Palette_Colour *TransparentColor = NULL, unsigned char transmask = 0,
                                       int *offX = NULL, int *offY = NULL);

    //transmask - pixel alpha value is less than transmask consider tottle transparent
    FILOCRGBQUAD* GetFIDecodedFrameData(const unsigned long index, int &width, int &height, int &offX, int &offY);
    wxImage GetFrameImage(const unsigned long index, unsigned char transmask = 0);


    Palette PaletteData;
private:

    void InitTransparentColor();

    Palette_Colour TransparentColor;
    SprFileHead FileHead;
    wxString FilePath;
    unsigned long FrameDataBegPos;
    //FrameData* FramesDataBlock;

};

#endif // SPRDECODE_HPP_INCLUDED
