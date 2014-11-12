#ifndef MAPICDATA_HPP_INCLUDED
#define MAPICDATA_HPP_INCLUDED

#include "wx/string.h"

#include "FreeImage.h"

struct FRAMERGBA
{
    long width;
    long height;
    FILOCRGBQUAD *data;
    FRAMERGBA *next;
};

class MAPICDATA
{
public:
    enum SHD_TYPE{SHD_MPC, SHD_ASF};
    MAPICDATA(){Init();}
    MAPICDATA(const long width, const long height){Init();globalwidth = width;globalheight = height;}
    ~MAPICDATA();
    void Init(const long width,const  long height){Init();globalwidth = width; globalheight = height;}
    void AddFrame(FILOCRGBQUAD *frame, long width = 0, long height = 0);
    bool Quantize(const int palettesize = 255, bool keepalpha = false);
    BYTE* GetPixIndexData();
    //SaveToPng's path parameter not contain file extation, others contain
    bool SaveToPng(const wxString path);
    bool SaveToGif(const wxString path);
    bool SaveToMpc(const wxString path, long direction, long interval, long bottom, bool makeshow = false);
    bool SaveToAsf(const wxString path, long direction, long interval, long bottom, long left,
                   bool makeshow = false, long offsetsunx = 0, long offsetsuny = 0,long offsetposx = 0, long offsetposy = 0);
    bool SaveToShd(const wxString path, long direction, long interval, long bottom);

    //outshd must be deleted, if not needed any more
    bool MakeShadow(SHD_TYPE type, MAPICDATA **outshd = NULL, long offsetsunx = 0, long offsetsuny = 0,
                    long offsetposx = 0, long offsetposy = 0);

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
