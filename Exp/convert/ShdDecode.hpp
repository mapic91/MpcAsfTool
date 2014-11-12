#ifndef SHDDECODE_HPP_INCLUDED
#define SHDDECODE_HPP_INCLUDED

#include "wx/string.h"
#include "wx/image.h"

#include "mydefs.hpp"
#include "FreeImage.h"

class ShdDecode
{
public:
    enum COLOUR_MODLE{PIC_RGB,PIC_RGBA, PIC_BGRA};
    ShdDecode();
    ~ShdDecode();
    void Init();
    ShdDecode(const wxString ShdFilePath);
    void SetShdFile(const wxString ShdFilePath);
    wxString GetFilePath();
    bool ReadShdFile();
    bool ReadShdFile(const wxString ShdFilePath);
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
    unsigned char* GetDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB);
    unsigned char* GetGlobleDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB);
    //data must be delete[] if won't use anymore
    FILOCRGBQUAD* GetFIDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB);
    FILOCRGBQUAD* GetGlobleFIDecodedFrameData(const unsigned long index, long* Width = NULL, long* Height = NULL,
                                       COLOUR_MODLE mod = PIC_RGB);
    wxImage GetFrameImage(const unsigned long index);



private:

    ShdFileHead FileHead;
    wxString FilePath;
    unsigned long FrameDataBegPos;
    //FrameData* FramesDataBlock;

};

#endif // SHDDECODE_HPP_INCLUDED
