#ifndef MAPICDATA_HPP_INCLUDED
#define MAPICDATA_HPP_INCLUDED

#include "wx/string.h"
#include "wx/colour.h"
#include "wx/gdicmn.h"

#include "FreeImage.h"

enum SHD_TYPE{SHD_MPC, SHD_ASF};

struct FRAMERGBA
{
    long width;
    long height;
    bool islocked;
    long sunoffx;
    long sunoffy;
    long shadowoffx;
    long shadowoffy;
    bool isdeleted;
    FILOCRGBQUAD *data;
    FILOCRGBQUAD *shddata;
    FRAMERGBA *next;
};

class MAPICDATA
{
public:
    MAPICDATA(){Init();}
    MAPICDATA(const long width, const long height){Init();globalwidth = width;globalheight = height;}
    ~MAPICDATA();
    void Init(const long width,const  long height){Init();globalwidth = width; globalheight = height;}
    //frame must be global width height
    void AddFrame(FILOCRGBQUAD *frame);
    FRAMERGBA *GetFrameData(unsigned long index);
    bool Quantize(const int palettesize = 255, bool keepalpha = false);
    BYTE* GetPixIndexData();
    //SaveToPng's path parameter not contain file extation, others contain
    bool SaveToPng(const wxString path);
    bool SaveToGif(const wxString path);
    bool SaveToMpc(const wxString path, long direction, long interval, long bottom, bool makeshow = false);
    bool SaveToAsf(const wxString path, long direction, long interval, long bottom, long left,
                   bool makeshow = false, long offsetsunx = 0, long offsetsuny = 0,long offsetposx = 0, long offsetposy = 0);
    bool SaveToShd(const wxString path, long direction, long interval, long bottom);

    //if outshd is not NULL, internal data is unchanged. outshd must be deleted, if not needed any more
    bool MakeShadow(SHD_TYPE type, MAPICDATA **outshd = NULL, long offsetsunx = 0, long offsetsuny = 0,
                    long offsetposx = 0, long offsetposy = 0, unsigned char shadowalpha = 0xB9);
    //outshd must be delete[], if not needed any more
    //if orgincluded is true shadow including frame data
    FILOCRGBQUAD* MakeShadow(SHD_TYPE type, unsigned long index, bool orgincluded, long offsetsunx = 0, long offsetsuny = 0,
                    long offsetposx = 0, long offsetposy = 0, unsigned char shadowalpha = 0xB9);
    //alpha less than transmask consider transparent
    void MakeTransMask(unsigned char transmask = 0);
    void AddBaseColor(FILOCRGBQUAD basecolor);
    //retrun data must free()
    unsigned char* GetFrameRGB(unsigned long index, wxColor transcolor = *wxWHITE);

    void ReNew(){FreeRGBAData(); Init();}

    FILOCRGBQUAD palette[256];
protected:
private:
    void FreeRGBAData();
    void Init();

    //returned value must free(), outsize is the returned buffer size
    unsigned char* MpcRunLenEncode(const unsigned char* maskline, const unsigned char* coliline, unsigned long *outsize);
    unsigned char* AsfRunLenEncode(const unsigned char* maskline, const unsigned char* coliline, unsigned long *outsize);
    unsigned char* ShdRunLenEncode(const unsigned char* maskline, unsigned long *outsize);



    long globalwidth, globalheight;
    FRAMERGBA *firstframe, *currentframe;
    //opaque pixels indexes
    BYTE *pixindex;
    unsigned long framecounts, quatwidth;
    //platte size
    int pltsize;
    bool isquantized;
};


#endif // MAPICDATA_HPP_INCLUDED
