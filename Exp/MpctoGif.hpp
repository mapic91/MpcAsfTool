#ifndef MPCTOGIF_HPP_INCLUDED
#define MPCTOGIF_HPP_INCLUDED

#include "wx/wx.h"

class CovMpctoGif
{
public:
    enum FileType{T_GIF, T_PNG};
    CovMpctoGif();
    CovMpctoGif(const wxString inMpcFilePath, const wxString outGifFilePath);
    ~CovMpctoGif(){}
    void Init(){}
    void SetInFilePath(const wxString MpcFilePath){inFilePath = MpcFilePath;}
    void SetOutFilePath(const wxString GifFilePath){outFilePath = GifFilePath;}
    bool Save(FileType type = T_GIF);
    bool Save(const wxString GifFilePath, FileType type = T_GIF){outFilePath = GifFilePath; return Save(type);}
private:
    wxString inFilePath, outFilePath;
};

#endif // MPCTOGIF_HPP_INCLUDED
