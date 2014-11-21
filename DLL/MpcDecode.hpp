#ifndef MPCDECODE_HPP_INCLUDED
#define MPCDECODE_HPP_INCLUDED

#include "wx/string.h"

#include "mydefs.hpp"
#include "FreeImage.h"

class MpcDecode
{
public:
    enum COLOUR_MODLE{PIC_RGB,PIC_RGBA, PIC_BGRA};
    MpcDecode();
    ~MpcDecode();
    void Init();
    MpcDecode(const wxString MpcFilePath);
    void SetMpcFile(const wxString MpcFilePath);
    wxString GetFilePath();
    bool ReadMpcFile();
    bool ReadMpcFile(const wxString MpcFilePath);
    wxString GetVersionInfo();
    unsigned long GetFramesDataLengthSum();
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

    //data must be free() if won't use anymore
    Palette_Colour GetTransparentColor();
    unsigned char* GetDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL, Palette_Colour *TransparentColor = NULL);
    unsigned char* GetGlobleDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL, Palette_Colour *TransparentColor = NULL);
    FILOCRGBQUAD* GetFIDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL, Palette_Colour *TransparentColor = NULL);
    FILOCRGBQUAD* GetGlobleFIDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB,bool *isTransparent = NULL, Palette_Colour *TransparentColor = NULL);


    Palette PaletteData;
	long DecodeType;

private:

    void InitTransparentColor();

    Palette_Colour TransparentColor;
    MpcFileHead FileHead;
    wxString FilePath;
    unsigned long FrameDataBegPos;
    //FrameData* FramesDataBlock;

};

#endif // MPCDECODE_HPP_INCLUDED
