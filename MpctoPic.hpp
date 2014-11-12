#ifndef MPCTOGIF_HPP_INCLUDED
#define MPCTOGIF_HPP_INCLUDED

#include "wx/wx.h"

class CovMpctoPic
{
public:
    enum FileType{T_GIF, T_PNG, T_MPC, T_ASF};
    CovMpctoPic();
    CovMpctoPic(const wxString inMpcFilePath, const wxString outGifFilePath);
    ~CovMpctoPic(){}
    void Init(){}
    void SetInFilePath(const wxString MpcFilePath){inFilePath = MpcFilePath;}
    void SetOutFilePath(const wxString GifFilePath){outFilePath = GifFilePath;}
    bool Save(FileType type = T_GIF, bool ShdIncluded = false, long direction = 8,
              long interval = 100, long bottom = 0, long left = 0, bool makeshadow = false,
              long offsetsunx = 0, long offsetsuny = 0,long offsetposx = 0, long offsetposy = 0);
    bool Save(const wxString GifFilePath, FileType type = T_GIF, bool ShdIncluded = false,
              long direction = 8, long interval = 100, long bottom = 0, long left =0, bool makeshadow = false,
              long offsetsunx = 0, long offsetsuny = 0,long offsetposx = 0, long offsetposy = 0)
    {
        outFilePath = GifFilePath;
        return Save(type, ShdIncluded, direction, interval, bottom, left, makeshadow,
                    offsetsunx, offsetsuny, offsetposx, offsetposy);
    }
private:
    wxString inFilePath, outFilePath;
};

#endif // MPCTOGIF_HPP_INCLUDED
