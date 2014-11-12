#ifndef ASFTOPIC_HPP_INCLUDED
#define ASFTOPIC_HPP_INCLUDED

#include "wx/wx.h"

#include "mydefs.hpp"

class CovAsftoPic
{
public:
    enum FileType{T_GIF, T_PNG, T_MPC, T_ASF};
    CovAsftoPic();
    CovAsftoPic(const wxString inMpcFilePath, const wxString outGifFilePath);
    ~CovAsftoPic(){}
    void Init(){}
    void SetInFilePath(const wxString MpcFilePath){inFilePath = MpcFilePath;}
    void SetOutFilePath(const wxString GifFilePath){outFilePath = GifFilePath;}
    bool Save(FileType type = T_GIF, Palette_Colour *backcolor = NULL, unsigned char transmask = 0,
              long direction = 8, long interval = 100, long bottom = 0, long left =0, bool makeshadow = 0,
              long offsetsunx = 0, long offsetsuny = 0,long offsetposx = 0, long offsetposy = 0);
    bool Save(const wxString OutFilePath, FileType type = T_GIF, Palette_Colour *backcolor = NULL,
              unsigned char transmask = 0, long direction = 8, long interval = 100, long bottom = 0,
              long left =0, bool makeshadow = 0, long offsetsunx = 0, long offsetsuny = 0,long offsetposx = 0, long offsetposy = 0)
        {outFilePath = OutFilePath; return Save(type, backcolor, transmask, direction, interval, bottom, left, makeshadow,
                                                offsetsunx, offsetsuny, offsetposx, offsetposy);}
private:
    wxString inFilePath, outFilePath;
};

#endif // ASFTOGIF_HPP_INCLUDED
