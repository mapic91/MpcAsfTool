#ifndef GIFDATA_HPP_INCLUDED
#define GIFDATA_HPP_INCLUDED

#include "FreeImage.h"

#include "wx/string.h"

struct GifFrameData
{
    size_t datasize;
    BYTE *data;
};

struct GifFrame
{
    size_t datasize;
    BYTE *data;
    GifFrame* next;
};



class GifData
{
public:

    GifData(){Init();}
    GifData(int width, int height, int interval = 100, bool istransparent = true);
    ~GifData();
    void Init();
    void SetWidth(int width){Width = width;}
    void SetHeight(int height){Height = height;}
    void SetInterval(int interval){Interval = (interval+9)/10;}
    void SetTransparent(bool istransparent){isTrans = istransparent;}
    void SetOutPath(const wxString path){OutPath = path;}
    int GetWidth(){return Width;}
    int GetHeight(){return Height;}
    int GetInterval(){return Interval;}
    bool isTransparent(){return isTrans;}
    wxString GetOutPath(){return OutPath;}
    void AddPage(GifFrameData* page);
    bool Save();
    bool Save(const wxString path){OutPath = path; return Save();}
    //Convert Local Palette to Globle Palette, each Local Palette Must be same
    //Palette Size must be 256,the 256th is the transparent color
    FIMEMORY *FIPaletteLoctoGlb(FIMEMORY *instream);
    static bool FilePaletteLoctoGlb(const wxString infilepath, long Interval = 100);

private:
    int Width,Height,Interval;
    bool isTrans;
    FILOCRGBQUAD Palette[256];
    GifFrame *FirstPage, *LastPage;
    int FrameCounts;
    wxString OutPath;
};

#endif // GIFDATA_HPP_INCLUDED
