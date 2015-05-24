#ifndef WORKMANAGER_HPP_INCLUDED
#define WORKMANAGER_HPP_INCLUDED

#include "wx/image.h"

#include "MAPICDATA.hpp"
#include "MpcDecode.hpp"
#include "MpctoPic.hpp"
#include "AsfDecode.hpp"
#include "AsftoPic.hpp"
#include "ShdDecode.hpp"
#include "SprDecode.hpp"

class WorkManager
{
public:
    WorkManager(){Init();}
    WorkManager(long Width, long Height, long Direction, long Bottom, long Left, unsigned long Interval, bool ShdIncluded,
                bool MakeShadow, SHD_TYPE ShdType, long Sunx, long Suny, long Shdx, long Shdy, wxColor Basecol,
                unsigned char AlphaMask, unsigned char ShadowAlpha,long PicOffX, long PicOffY)
    {
        Init(Width, Height, Direction, Bottom, Left, Interval, ShdIncluded,
             MakeShadow, ShdType, Sunx, Suny, Shdx, Shdy, Basecol, AlphaMask, ShadowAlpha, PicOffX, PicOffY);
    }
    ~WorkManager(){FreeRGBAData();}
    void Init()
    {
        globalwidth = 1; globalheight = 1; direction = 1; bottom = 0;
        left = 0; interval = 100; shdincluded = false; makeshadow = false; shdtype = SHD_MPC;
        globalsunoffx = 0; globalsunoffy = 0; globalshadowoffx = 0; globalshadowoffy = 0;
        basecolor = *wxWHITE; firstframe = NULL; currentframe = NULL;
        totalframecounts = 0;framecounts = 0;alphamask = 0; shadowalpha = 0x78;
        picoffx = 0; picoffy = 0;
    }
    void Init(long Width, long Height, long Direction, long Bottom, long Left, unsigned long Interval, bool ShdIncluded,
                bool MakeShadow, SHD_TYPE ShdType, long Sunx, long Suny, long Shdx, long Shdy,
                wxColor Basecol, unsigned char AlphaMask, unsigned char ShadowAlpha,long PicOffX, long PicOffY)
    {
        Init();
        globalwidth = Width; globalheight = Height; direction = Direction; bottom = Bottom;
        left = Left; interval = Interval; shdincluded = ShdIncluded; makeshadow = MakeShadow; shdtype = ShdType;
        globalsunoffx = Sunx; globalsunoffy = Suny; globalshadowoffx = Shdx; globalshadowoffy = Shdy;
        basecolor = Basecol; alphamask = AlphaMask; shadowalpha = ShadowAlpha; picoffx = PicOffX; picoffy = PicOffY;
    }

    //delete internal data, get a empty object
    void ReNew(){FreeRGBAData();Init();}

    //return failed file
    wxArrayString AddFiles(const wxArrayString& files);

    //open mpc asf file
    bool OpenFile(wxString InPath, int frameBegin = 0, int frameEnd = 99999999);



    bool AddFrame(FILOCRGBQUAD *frame, long width, long height, FILOCRGBQUAD *shddata = NULL,
				bool isOffsetLocked = false, int offx = 0, int offy = 0);

    //set frame local info,frame marked deleted is excluded
    bool SetUndeletedFrame(unsigned long index, bool isLock = true,
                  long Sunx = 0 , long Suny = 0, long Shdx = 0, long Shdy = 0);

    bool DeleteFrame(unsigned long index);

    //undelete last deleted frame
    bool UnDeleteFrame();

    //All frames included, include deleted frame
    FRAMERGBA* GetFrameData(unsigned long index);

    //get internal frame data, frame marked deleted is excluded, don't delete[] it
    FRAMERGBA* GetUndeletedFrameData(unsigned long index, unsigned long *RealIndex = NULL);

    bool IsUndeletedFrameLocked(unsigned long index);

    //get width height globalize data, return data must be delete[] if unneeded
    FILOCRGBQUAD* GetUndeletedGlobalizedFrameData(unsigned long index);
    FILOCRGBQUAD* GetUndeletedGlobalizedShdFrameData(unsigned long index);

    wxImage GetUndeletedGlobalizedImage(unsigned long index, bool AssiLine = false);

    void SetGlobalWidth(long width){globalwidth = width;}
    void SetGlobalHeight(long height){globalheight = height;}
    void SetDirection(long Direction){direction = Direction;}
    void SetBottom(long Bottom){bottom = Bottom;}
    void SetLeft(long Left){left = Left;}
    void SetInterval(unsigned long Interval){interval = Interval;}
    void SetPicOffX(long PicOffX){picoffx = PicOffX;}
    void SetPicOffY(long PicOffY){picoffy = PicOffY;}
    void SetShdIncluded(bool ShdIncluded){shdincluded = ShdIncluded;}
    void SetMakeShadow(bool IsMake, SHD_TYPE type = SHD_MPC){makeshadow = IsMake; shdtype = type;}
    void SetGlobalSunx(long Sunx){globalsunoffx = Sunx;}
    void SetGlobalSuny(long Suny){globalsunoffy = Suny;}
    void SetGlobalShadowx(long Shdx){globalshadowoffx = Shdx;}
    void SetGlobalShadowy(long Shdy){globalshadowoffy = Shdy;}
    void SetBaseColor(wxColor Base){basecolor = Base;}
    void SetAlphaMask(unsigned char AlphaMask){alphamask = AlphaMask;}
    void SetShadowAlpha(unsigned char ShadowAlpha){shadowalpha = ShadowAlpha;}
    bool SetFrameLock(unsigned long index, bool locked = true);
    bool SetFrameSunX(unsigned long index, long Sunx);
    bool SetFrameSunY(unsigned long index, long Suny);
    bool SetFrameShadowX(unsigned long index, long ShadowX);
    bool SetFrameShadowY(unsigned long index, long ShadowY);

    long GetGlobalWidth(){return globalwidth;}
    long GetGlobalHeight(){return globalheight;}
    long GetDirection(){return direction;}
    long GetBottom(){return bottom;}
    long GetLeft(){return left;}
    unsigned long GetInterval(){return interval;}
    long GetPicOffX(){return picoffx;}
    long GetPicOffY(){return picoffy;}
    bool IsShdIncluded(){return shdincluded;}
    bool IsMakeShadow(){return makeshadow;}
    SHD_TYPE GetShadowType(){return shdtype;}
    long GetGlobalSunx(){return globalsunoffx;}
    long GetGlobalSuny(){return globalsunoffy;}
    long GetGlobalShadowx(){return globalshadowoffx;}
    long GetGlobalShadowy(){return globalshadowoffy;}
    wxColor GetBaseColor(){return basecolor;}
    unsigned char GetAlphaMask(){return alphamask;}
    unsigned char GetShadowAlpha(){return shadowalpha;}
    unsigned long GetFrameCounts(){return framecounts;}
    bool IsFrameLocked(unsigned long index);
    long GetFrameSunX(unsigned long index);
    long GetFrameSunY(unsigned long index);
    long GetFrameShadowX(unsigned long index);
    long GetFrameShadowY(unsigned long index);

	bool SaveToMpc(const wxString outpath);
    bool SaveToMpc(const wxString outpath, int decodeType);
    bool SaveToAsf(const wxString outpath);
    bool SaveToGif(const wxString outpath);
    bool SaveToPng(const wxString outpath);

protected:
private:
    void FreeRGBAData();

    void AddBaseColor(FILOCRGBQUAD *inout, long width, long heigh);


    MpcDecode mpcdecode;
    AsfDecode asfdecode;
    ShdDecode shddecode;
    SprDecode sprdecode;

    FRAMERGBA *firstframe, *currentframe;
    unsigned long framecounts;//not included deleted
    unsigned long totalframecounts;//included deleted
    wxArrayLong deletedframe;

    long globalwidth;
    long globalheight;
    long direction;
    long bottom;
    long left;
    unsigned long interval;
    long picoffx;
    long picoffy;

    bool shdincluded;
    bool makeshadow;
    SHD_TYPE shdtype;
    long globalsunoffx;
    long globalsunoffy;
    long globalshadowoffx;
    long globalshadowoffy;

    unsigned char alphamask;
    unsigned char shadowalpha;

    wxColor basecolor;
};


#endif // WORKMANAGER_HPP_INCLUDED
