#include "WorkManager.hpp"
#include "GifData.hpp"
#include "wx/filename.h"
#include "RpcDecode.hpp"

///////////////
//public
//////////////
wxArrayString WorkManager::AddFiles(const wxArrayString& files)
{
    if(files.IsEmpty())return wxArrayString();

    wxArrayString failedfiles;
    FREE_IMAGE_FORMAT filetype = FIF_UNKNOWN;
    FIMULTIBITMAP *multipic = NULL;
    FIBITMAP *singlepic = NULL, *bmp32;
    unsigned tempwidth, tempheight;
    unsigned long temppos;
    FILOCRGBQUAD *buffer = NULL;
    BYTE *data;

    for(size_t i = 0; i < files.GetCount(); i++)
    {
        filetype = FreeImage_GetFileType(files[i].char_str(), 0);
        if(filetype == FIF_UNKNOWN)
        {
            filetype = FreeImage_GetFIFFromFilename(files[i].char_str());
        }

        if(filetype != FIF_UNKNOWN && FreeImage_FIFSupportsReading(filetype))
        {
            if(filetype == FIF_ICO || filetype == FIF_TIFF ||filetype == FIF_GIF)//multi-page
            {
                multipic = FreeImage_OpenMultiBitmap(filetype, files[i].char_str(), FALSE, TRUE, FALSE, 0);
                if(multipic)
                {
                    for(int mlti = 0; mlti < FreeImage_GetPageCount(multipic); mlti++)
                    {
                        singlepic = FreeImage_LockPage(multipic, mlti);
                        if(singlepic)
                        {
                            bmp32 = FreeImage_ConvertTo32Bits(singlepic);
                            if(bmp32)
                            {
                                tempwidth = FreeImage_GetWidth(bmp32);
                                tempheight = FreeImage_GetHeight(bmp32);
                                buffer = new FILOCRGBQUAD[tempwidth*tempheight];
                                data = (BYTE*)malloc(tempwidth*tempheight*4);

//                                if(totalframecounts == 0)
//                                {
//                                    SetGlobalWidth((long)tempwidth);
//                                    SetGlobalHeight((long)tempheight);
//                                }

                                if(buffer != NULL && data != NULL)
                                {
                                    FreeImage_ConvertToRawBits(data, bmp32, tempwidth*4, 32, FI_RGBA_RED_MASK,
                                                               FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,TRUE);

                                    temppos = 0;
                                    for(unsigned long pixi = 0; pixi < tempwidth*tempheight; pixi++)
                                    {
                                        buffer[pixi].rgbBlue = data[temppos++];
                                        buffer[pixi].rgbGreen = data[temppos++];
                                        buffer[pixi].rgbRed = data[temppos++];
                                        buffer[pixi].rgbReserved = data[temppos++];
                                    }
                                    AddFrame(buffer, tempwidth, tempheight);
                                }
                                else
                                {
                                    failedfiles.Add(files[i]);
                                    FreeImage_Unload(bmp32);
                                    FreeImage_UnlockPage(multipic, singlepic, FALSE);
                                    if(buffer) delete[] buffer;
                                    if(data) free(data);
                                    break;
                                }

                                FreeImage_Unload(bmp32);
                            }
                            else
                            {
                                failedfiles.Add(files[i]);
                                FreeImage_UnlockPage(multipic, singlepic, FALSE);
                                break;
                            }
                        }
                        else
                        {
                            failedfiles.Add(files[i]);
                            break;
                        }
                    }

                    FreeImage_CloseMultiBitmap(multipic, 0);
                    multipic = NULL;
                }
                else
                {
                    failedfiles.Add(files[i]);
                }
            }
            else //single-page
            {
                singlepic = FreeImage_LoadU(filetype, files[i], 0);
                if(singlepic)
                {
                    bmp32 = FreeImage_ConvertTo32Bits(singlepic);
                    FreeImage_Unload(singlepic);

                    if(bmp32)
                    {
                        tempwidth = FreeImage_GetWidth(bmp32);
                        tempheight = FreeImage_GetHeight(bmp32);
                        buffer = new FILOCRGBQUAD[tempwidth*tempheight];
                        data = (BYTE*)malloc(tempwidth*tempheight*4);

//                        if(totalframecounts == 0)
//                        {
//                            SetGlobalWidth((long)tempwidth);
//                            SetGlobalHeight((long)tempheight);
//                        }

                        if(buffer != NULL && data != NULL)
                        {
                            FreeImage_ConvertToRawBits(data, bmp32, tempwidth*4, 32, FI_RGBA_RED_MASK,
                                                       FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,TRUE);

                            temppos = 0;
                            for(unsigned long pixi = 0; pixi < tempwidth*tempheight; pixi++)
                            {
                                buffer[pixi].rgbBlue = data[temppos++];
                                buffer[pixi].rgbGreen = data[temppos++];
                                buffer[pixi].rgbRed = data[temppos++];
                                buffer[pixi].rgbReserved = data[temppos++];
                            }
                            AddFrame(buffer, tempwidth, tempheight);
                        }
                        else
                        {
                            failedfiles.Add(files[i]);
                            if(buffer) delete[] buffer;
                            if(data) free(data);
                        }

                        FreeImage_Unload(bmp32);
                    }
                    else
                    {
                        failedfiles.Add(files[i]);
                    }

                }
                else
                {
                    failedfiles.Add(files[i]);
                }
            }
        }
        else
        {
            if(sprdecode.ReadSprFile(files[i]))
            {
            	tempwidth = sprdecode.GetGlobleWidth();
            	tempheight = sprdecode.GetGlobleHeight();
            	int width, height,offx, offy;
                for(unsigned long i = 0; i < sprdecode.GetFramesCounts(); i++)
                {
                    buffer = sprdecode.GetFIDecodedFrameData(i, width, height, offx, offy);
                    if(buffer)
                    {
                        if(totalframecounts == 0)
                        {
                            SetGlobalWidth((long)width);
                            SetGlobalHeight((long)height);
                        }

                        AddFrame(buffer, width, height, NULL, true, offx, offy);
                    }
                    else
                    {
                        failedfiles.Add(files[i]);
                        break;
                    }
                }
            }
            else failedfiles.Add(files[i]);
        }
    }

    return failedfiles;
}
bool WorkManager::OpenFile(wxString InPath, int frameBegin, int frameEnd )
{
    if(InPath.IsEmpty()) return false;
    wxString ext;
    long tempwidth, tempheight;
    FILOCRGBQUAD *tempdata, *tempshddata;

    ext = wxFileName::FileName(InPath).GetExt();

    if(ext.CmpNoCase(wxT("mpc")) == 0)
    {
        wxString shdpath;
        bool hasshd = false;

        if(!mpcdecode.ReadMpcFile(InPath)) return false;

        shdpath = wxFileName::FileName(InPath).GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
        shdpath += wxFileName::FileName(InPath).GetName();
        shdpath += wxT(".shd");

        tempwidth = mpcdecode.GetGlobleWidth();
        tempheight = mpcdecode.GetGlobleHeight();
        SetGlobalWidth(tempwidth);
        SetGlobalHeight(tempheight);
        SetDirection(mpcdecode.GetDirection());
        SetBottom(mpcdecode.GetBottom());
        SetInterval(mpcdecode.GetInterval());

        if(wxFileName::FileExists(shdpath))
        {
            if(shddecode.ReadShdFile(shdpath))
            {
                if(shddecode.GetGlobleWidth() == tempwidth &&
                        shddecode.GetGlobleHeight() == tempheight)
                {
                    hasshd = true;
                }
            }
        }

        tempshddata = NULL;
        for(unsigned long conti = frameBegin; conti < mpcdecode.GetFramesCounts() && ((int)conti) <= frameEnd; conti++)
        {
            tempdata = mpcdecode.GetGlobleFIDecodedFrameData(conti, NULL, NULL, MpcDecode::PIC_BGRA);
            if(!tempdata) return false;
            if(hasshd)
            {
                tempshddata = shddecode.GetGlobleFIDecodedFrameData(conti, NULL, NULL, ShdDecode::PIC_BGRA);
            }
            AddFrame(tempdata, tempwidth, tempheight, tempshddata);
        }
    }
    else if(ext.CmpNoCase(wxT("asf")) == 0)
    {
        asfdecode.ReadAsfFile(InPath);

        if(!asfdecode.ReadAsfFile(InPath)) return false;

        tempwidth = asfdecode.GetGlobleWidth();
        tempheight  = asfdecode.GetGlobleHeight();
        SetGlobalWidth(tempwidth);
        SetGlobalHeight(tempheight);
        SetDirection(asfdecode.GetDirection());
        SetBottom(asfdecode.GetBottom());
        SetInterval(asfdecode.GetInterval());
        SetLeft(asfdecode.GetLeft());

        for(unsigned long conti = frameBegin; conti < asfdecode.GetFramesCounts() && ((int)conti) <= frameEnd; conti++)
        {
            tempdata = asfdecode.GetGlobleFIDecodedFrameData(conti, NULL, NULL, AsfDecode::PIC_BGRA);
            if(!tempdata) return false;
            AddFrame(tempdata, tempwidth, tempheight);
        }
    }
    else if(ext.CmpNoCase(wxT("rpc")) == 0)
    {
        RpcDecode decode;
        if(decode.ReadFile(InPath))
        {
            tempwidth = decode.GetGlobleWidth();
            tempheight = decode.GetGlobleHeight();
            SetGlobalWidth(tempwidth);
            SetGlobalHeight(tempheight);
            SetDirection(decode.GetDirection());
            SetBottom(decode.GetBottom());
            SetInterval(decode.GetInterval());

            for(unsigned long conti = frameBegin; conti < decode.GetFramesCounts() && ((int)conti) <= frameEnd; conti++)
            {
                tempdata = decode.GetFIDecodedFrameData(conti);
                if(!tempdata) return false;
                AddFrame(tempdata, tempwidth, tempheight);
            }
        }
        else return false;
    }
    else if(ext.CmpNoCase(wxT("spr")) == 0)
    {
        if(sprdecode.ReadSprFile(InPath))
        {
            tempwidth = sprdecode.GetGlobleWidth();
            tempheight  = sprdecode.GetGlobleHeight();
            SetGlobalWidth(tempwidth);
            SetGlobalHeight(tempheight);
            SetDirection(sprdecode.GetDirection());
            SetInterval(sprdecode.GetInterval());
            SetBottom(sprdecode.GetBottom());
            SetLeft(sprdecode.GetLeft());

			int width, height,offx, offy;
            for(unsigned long conti = frameBegin; conti < sprdecode.GetFramesCounts() && ((int)conti) <= frameEnd; conti++)
            {
                tempdata = sprdecode.GetFIDecodedFrameData(conti, width, height, offx, offy);
                if(!tempdata) return false;
                AddFrame(tempdata, width, height, NULL, true, offx, offy);
            }
        }
        else
            return false;
    }
    else
	{
		return false;
	}

    return true;
}
bool WorkManager::AddFrame(FILOCRGBQUAD *frame, long width, long height, FILOCRGBQUAD *shddata,
				bool isOffsetLocked, int offx, int offy)
{
    if(frame == NULL || width < 1 || height < 1) return false;

    if(totalframecounts == 0)
    {
        firstframe = new FRAMERGBA();
        currentframe = firstframe;
    }
    else
    {
        currentframe->next = new FRAMERGBA();
        currentframe = currentframe->next;
    }

    if(currentframe)
	{
		currentframe->data = frame;
        currentframe->shddata = shddata;
        currentframe->next = NULL;
        currentframe->width = width;
        currentframe->height = height;
        currentframe->islocked = false;
        currentframe->isdeleted = false;
        if(isOffsetLocked)
		{
			currentframe->ispicoffsetlocked = true;
			currentframe->picoffx = offx;
			currentframe->picoffy = offy;
		}
	}

    totalframecounts++;
    framecounts++;

    return true;
}
//set frame local info
bool WorkManager::SetUndeletedFrame(unsigned long index, bool isLock, long Sunx, long Suny, long Shdx, long Shdy)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL) return false;

    temp->islocked = isLock;
    temp->sunoffx = Sunx;
    temp->sunoffy = Suny;
    temp->shadowoffx = Shdx;
    temp->shadowoffy = Shdy;

    return true;
}
bool WorkManager::DeleteFrame(unsigned long index)
{
    FRAMERGBA *temp;
    unsigned long relpos;

    temp = GetUndeletedFrameData(index, &relpos);
    if(temp == NULL) return false;

    temp->isdeleted = true;

    framecounts--;
    deletedframe.Add(relpos);

    return true;
}

//undelete last deleted frame
bool WorkManager::UnDeleteFrame()
{
    if(deletedframe.IsEmpty()) return false;

    FRAMERGBA *temp;

    temp = GetFrameData(deletedframe[deletedframe.GetCount()-1]);
    if(temp == NULL) return false;

    temp->isdeleted = false;

    framecounts++;
    deletedframe.RemoveAt(deletedframe.GetCount()-1);

    return true;
}

//All frames included, include deleted frame
FRAMERGBA* WorkManager::GetFrameData(unsigned long index)
{
    if(index >= totalframecounts) return NULL;

    FRAMERGBA *temp;

    temp = firstframe;

    for(unsigned long i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

//get internal frame data, frame marked deleted is excluded, don't delete[] it
FRAMERGBA* WorkManager::GetUndeletedFrameData(unsigned long index, unsigned long *RealIndex)
{
    if(index >= framecounts) return NULL;

    FRAMERGBA *temp;
    unsigned long relpos = 0;

    temp = firstframe;

    //get first undeleted frame
    for(unsigned long ui = 0; ui < totalframecounts; ui++)
    {
        if(temp->isdeleted)
        {
            temp = temp->next;
            relpos++;
        }
        else break;
    }

    for(unsigned long gi = 0; gi != index; )
    {
        if(temp->isdeleted)
        {
            temp = temp->next;
            relpos++;
        }
        else
        {
            temp = temp->next;
            relpos++;
            gi++;
        }
    }

    //last one may deleted
    for(unsigned long ui = 0; ui < totalframecounts; ui++)
    {
        if(temp->isdeleted)
        {
            temp = temp->next;
            relpos++;
        }
        else break;
    }

    if(RealIndex != NULL) *RealIndex = relpos;

    return temp;
}
bool WorkManager::IsUndeletedFrameLocked(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL) return false;

    return temp->islocked;
}
//get width height globalize data, return data must be delete[] if unneeded
FILOCRGBQUAD* WorkManager::GetUndeletedGlobalizedFrameData(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL) return NULL;


    unsigned long glbdatalen;
    long width,height,offwidth,offheight;
    FILOCRGBQUAD *decdata, *glbdata;

    width = temp->width;
    height = temp->height;
    decdata = temp->data;
    glbdatalen = (unsigned long)GetGlobalWidth()*GetGlobalHeight();
    glbdata = new FILOCRGBQUAD[(size_t)glbdatalen];
    long offx = GetPicOffX();
    long offy = GetPicOffY();
    if(temp->ispicoffsetlocked)
	{
		offx = temp->picoffx;
		offy = temp->picoffy;
	}

    if(!glbdata)
    {
        return NULL;
    }

    //inital
    for(long datidx = 0; datidx < (long)glbdatalen; datidx++)
    {
        glbdata[datidx].rgbRed = 0xFF;
        glbdata[datidx].rgbGreen = 0xFF;
        glbdata[datidx].rgbBlue = 0xFF;
        glbdata[datidx].rgbReserved = 0x00;
    }
    //assign
    for(long hi = 0; hi < GetGlobalHeight(); hi++)
    {
        for(long wi = 0; wi < GetGlobalWidth(); wi++)
        {
            offwidth = wi + offx;
            offheight = hi + offy;
            if(hi < height && wi < width &&
                    offwidth >= 0 && offwidth < GetGlobalWidth() &&
                    offheight >= 0 && offheight < GetGlobalHeight())
            {
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbRed = decdata[hi*width+wi].rgbRed;
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbGreen = decdata[hi*width+wi].rgbGreen;
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbBlue = decdata[hi*width+wi].rgbBlue;
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbReserved = decdata[hi*width+wi].rgbReserved;
            }
        }
    }

    return glbdata;
}
FILOCRGBQUAD* WorkManager::GetUndeletedGlobalizedShdFrameData(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL) return NULL;
    if(temp->shddata == NULL) return NULL;


    unsigned long glbdatalen;
    long width,height,offwidth,offheight;
    FILOCRGBQUAD *decdata, *glbdata;

    width = temp->width;
    height = temp->height;
    decdata = temp->shddata;
    glbdatalen = (unsigned long)GetGlobalWidth()*GetGlobalHeight();
    glbdata = new FILOCRGBQUAD[(size_t)glbdatalen];
    long offx = GetPicOffX();
    long offy = GetPicOffY();
    if(temp->ispicoffsetlocked)
	{
		offx = temp->picoffx;
		offy = temp->picoffy;
	}

    if(!glbdata)
    {
        return NULL;
    }

    //inital
    for(long datidx = 0; datidx < (long)glbdatalen; datidx++)
    {
        glbdata[datidx].rgbRed = 0xFF;
        glbdata[datidx].rgbGreen = 0xFF;
        glbdata[datidx].rgbBlue = 0xFF;
        glbdata[datidx].rgbReserved = 0x00;
    }
    //assign
    for(long hi = 0; hi < GetGlobalHeight(); hi++)
    {
        for(long wi = 0; wi < GetGlobalWidth(); wi++)
        {
            offwidth = wi + offx;
            offheight = hi + offy;
            if(hi < height && wi < width &&
                    offwidth >= 0 && offwidth < GetGlobalWidth() &&
                    offheight >= 0 && offheight < GetGlobalHeight())
            {
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbRed = decdata[hi*width+wi].rgbRed;
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbGreen = decdata[hi*width+wi].rgbGreen;
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbBlue = decdata[hi*width+wi].rgbBlue;
                glbdata[offheight*GetGlobalWidth()+offwidth].rgbReserved = decdata[hi*width+wi].rgbReserved;
            }
        }
    }

    return glbdata;
}
wxImage WorkManager::GetUndeletedGlobalizedImage(unsigned long index, bool AssiLine)
{
    MAPICDATA proc(GetGlobalWidth(), GetGlobalHeight());
    FILOCRGBQUAD *frame, *shdframe;
    FRAMERGBA *tempframe;
    unsigned char *rgbdata;
    long tsunx, tsuny, tshdx, tshdy;

    frame = GetUndeletedGlobalizedFrameData(index);
    if(frame == NULL) return wxNullImage;

    if(alphamask != 0)
    {
        MAPICDATA::MakeTransMask(frame, GetGlobalWidth(), GetGlobalHeight(), alphamask);
    }

    if(shdincluded && !makeshadow)
    {
        shdframe = GetUndeletedGlobalizedShdFrameData(index);
        if(shdframe != NULL)
        {
            for(long pixi = 0; pixi < GetGlobalWidth()*GetGlobalHeight(); pixi++)
            {
                if(frame[pixi].rgbReserved != 0)
                {
                    shdframe[pixi].rgbBlue = frame[pixi].rgbBlue;
                    shdframe[pixi].rgbGreen = frame[pixi].rgbGreen;
                    shdframe[pixi].rgbRed = frame[pixi].rgbRed;
                    shdframe[pixi].rgbReserved = frame[pixi].rgbReserved;
                }
            }
            delete[] frame;
            frame = shdframe;
        }
    }

    proc.AddFrame(frame);

    tempframe = GetUndeletedFrameData(index);
    if(tempframe == NULL) return wxNullImage;

    if(tempframe->islocked)
    {
        tsunx = tempframe->sunoffx;
        tsuny = tempframe->sunoffy;
        tshdx = tempframe->shadowoffx;
        tshdy = tempframe->shadowoffy;
    }
    else
    {
        tsunx = globalsunoffx;
        tsuny = globalsunoffy;
        tshdx = globalshadowoffx;
        tshdy = globalshadowoffy;
    }

    if(makeshadow)
    {
        if(!proc.MakeShadow(shdtype, NULL, tsunx,tsuny,
                            tshdx, tshdy, shadowalpha))
        {
            return wxNullImage;
        }
    }

    if(AssiLine)
    {
        proc.AddAssiLine();
    }

    rgbdata = proc.GetFrameRGB(0, basecolor);
    if(rgbdata == NULL) return wxNullImage;

    wxImage img(GetGlobalWidth(), GetGlobalHeight(), rgbdata);
    return img;
}
bool WorkManager::SaveToMpc(const wxString outpath)
{
	return SaveToMpc(outpath, mpcdecode.DecodeType);
}
bool WorkManager::SaveToMpc(const wxString outpath, int decodeType)
{
    MAPICDATA proc(GetGlobalWidth(), GetGlobalHeight());
    MAPICDATA shdproc(GetGlobalWidth(), GetGlobalHeight()), tempshd;
    FILOCRGBQUAD *tempfrmdata, *tempshddata, bscol;
    FRAMERGBA *tempframe;
    long tsunx, tsuny, tshdx, tshdy;

    bscol.rgbRed = (BYTE)basecolor.Red();
    bscol.rgbGreen = (BYTE)basecolor.Green();
    bscol.rgbBlue = (BYTE)basecolor.Blue();
    bscol.rgbReserved = 0xFF;

    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
        if(tempfrmdata == NULL) return false;

        if(alphamask != 0)
        {
            MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
        }

        proc.AddFrame(tempfrmdata);
    }

	if(decodeType == 0)
	{
		proc.AddBaseColor(bscol);
	}

    if(!proc.SaveToMpc(outpath, direction, interval, bottom, false, decodeType)) return false;

    if(makeshadow)
    {
        for(unsigned long frmi = 0; frmi < framecounts; frmi++)
        {
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            tempframe = GetUndeletedFrameData(frmi);

            if(tempframe->islocked)
            {
                tsunx = tempframe->sunoffx;
                tsuny = tempframe->sunoffy;
                tshdx = tempframe->shadowoffx;
                tshdy = tempframe->shadowoffy;
            }
            else
            {
                tsunx = globalsunoffx;
                tsuny = globalsunoffy;
                tshdx = globalshadowoffx;
                tshdy = globalshadowoffy;
            }

            tempshd.ReNew();
            tempshd.Init(GetGlobalWidth(), GetGlobalHeight());

            tempshd.AddFrame(tempfrmdata);

            tempshddata = tempshd.MakeShadow(shdtype, 0, false, tsunx, tsuny, tshdx, tshdy, shadowalpha);

            if(!tempshddata) return false;

            shdproc.AddFrame(tempshddata);
        }

        wxString shdpath;
        shdpath = wxFileName::FileName(outpath).GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
        shdpath += wxFileName::FileName(outpath).GetName();
        shdpath += wxT(".shd");

        if(!shdproc.SaveToShd(shdpath, direction, interval, bottom))return false;
    }
    return true;
}
bool WorkManager::SaveToAsf(const wxString outpath)
{
    MAPICDATA proc(GetGlobalWidth(), GetGlobalHeight());
    MAPICDATA shdproc(GetGlobalWidth(), GetGlobalHeight()), tempshd;
    FILOCRGBQUAD *tempfrmdata, *tempshddata;
    FRAMERGBA *tempframe;
    long tsunx, tsuny, tshdx, tshdy;

    if(!makeshadow)
    {
        for(unsigned long frmi = 0; frmi < framecounts; frmi++)
        {
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            if(shdincluded)
            {
                tempshddata = GetUndeletedGlobalizedShdFrameData(frmi);
                if(tempshddata != NULL)
                {
                    for(long pixi = 0; pixi < GetGlobalWidth()*GetGlobalHeight(); pixi++)
                    {
                        if(tempfrmdata[pixi].rgbReserved != 0)
                        {
                            tempshddata[pixi].rgbBlue = tempfrmdata[pixi].rgbBlue;
                            tempshddata[pixi].rgbGreen = tempfrmdata[pixi].rgbGreen;
                            tempshddata[pixi].rgbRed = tempfrmdata[pixi].rgbRed;
                            tempshddata[pixi].rgbReserved = tempfrmdata[pixi].rgbReserved;
                        }
                    }
                    delete[] tempfrmdata;
                    tempfrmdata = tempshddata;
                }
            }

            proc.AddFrame(tempfrmdata);
        }

        if(!proc.SaveToAsf(outpath, direction, interval, bottom, left,false)) return false;
    }
    else
    {
        for(unsigned long frmi = 0; frmi < framecounts; frmi++)
        {
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            tempframe = GetUndeletedFrameData(frmi);

            if(tempframe->islocked)
            {
                tsunx = tempframe->sunoffx;
                tsuny = tempframe->sunoffy;
                tshdx = tempframe->shadowoffx;
                tshdy = tempframe->shadowoffy;
            }
            else
            {
                tsunx = globalsunoffx;
                tsuny = globalsunoffy;
                tshdx = globalshadowoffx;
                tshdy = globalshadowoffy;
            }

            tempshd.ReNew();
            tempshd.Init(GetGlobalWidth(), GetGlobalHeight());

            tempshd.AddFrame(tempfrmdata);
            tempshddata = tempshd.MakeShadow(shdtype, 0, true, tsunx, tsuny, tshdx, tshdy, shadowalpha);

            if(!tempshddata) return false;

            shdproc.AddFrame(tempshddata);
        }

        if(!shdproc.SaveToAsf(outpath, direction, interval, bottom, left,false))return false;
    }
    return true;
}
bool WorkManager::SaveToGif(const wxString outpath)
{
    MAPICDATA proc(GetGlobalWidth(), GetGlobalHeight());
    MAPICDATA shdproc(GetGlobalWidth(), GetGlobalHeight()), tempshd;
    FILOCRGBQUAD *tempfrmdata, *tempshddata, bscol;
    FRAMERGBA *tempframe;
    long tsunx, tsuny, tshdx, tshdy;

    bscol.rgbRed = (BYTE)basecolor.Red();
    bscol.rgbGreen = (BYTE)basecolor.Green();
    bscol.rgbBlue = (BYTE)basecolor.Blue();
    bscol.rgbReserved = 0xFF;

    if(!makeshadow)
    {
        for(unsigned long frmi = 0; frmi < framecounts; frmi++)
        {
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            if(shdincluded)
            {
                tempshddata = GetUndeletedGlobalizedShdFrameData(frmi);
                if(tempshddata != NULL)
                {
                    for(long pixi = 0; pixi < GetGlobalWidth()*GetGlobalHeight(); pixi++)
                    {
                        if(tempfrmdata[pixi].rgbReserved != 0)
                        {
                            tempshddata[pixi].rgbBlue = tempfrmdata[pixi].rgbBlue;
                            tempshddata[pixi].rgbGreen = tempfrmdata[pixi].rgbGreen;
                            tempshddata[pixi].rgbRed = tempfrmdata[pixi].rgbRed;
                            tempshddata[pixi].rgbReserved = tempfrmdata[pixi].rgbReserved;
                        }
                    }
                    delete[] tempfrmdata;
                    tempfrmdata = tempshddata;
                }
            }

            proc.AddFrame(tempfrmdata);
        }

        proc.AddBaseColor(bscol);

        if(!proc.SaveToGif(outpath)) return false;
    }
    else
    {
        for(unsigned long frmi = 0; frmi < framecounts; frmi++)
        {
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            tempframe = GetUndeletedFrameData(frmi);

            if(tempframe->islocked)
            {
                tsunx = tempframe->sunoffx;
                tsuny = tempframe->sunoffy;
                tshdx = tempframe->shadowoffx;
                tshdy = tempframe->shadowoffy;
            }
            else
            {
                tsunx = globalsunoffx;
                tsuny = globalsunoffy;
                tshdx = globalshadowoffx;
                tshdy = globalshadowoffy;
            }

            tempshd.ReNew();
            tempshd.Init(GetGlobalWidth(), GetGlobalHeight());

            tempshd.AddFrame(tempfrmdata);
            tempshddata = tempshd.MakeShadow(shdtype, 0, true, tsunx, tsuny, tshdx, tshdy, shadowalpha);

            if(!tempshddata) return false;

            shdproc.AddFrame(tempshddata);
        }

        shdproc.AddBaseColor(bscol);

        if(!shdproc.SaveToGif(outpath))return false;
    }

    if(!GifData::FilePaletteLoctoGlb(outpath, interval)) return false;
    return true;
}
bool WorkManager::SaveToPng(const wxString outpath, bool reverseFrames)
{
    MAPICDATA proc(GetGlobalWidth(), GetGlobalHeight());
    MAPICDATA shdproc(GetGlobalWidth(), GetGlobalHeight()), tempshd;
    FILOCRGBQUAD *tempfrmdata, *tempshddata;
    FRAMERGBA *tempframe;
    long tsunx, tsuny, tshdx, tshdy;

    if(!makeshadow)
    {
        for(unsigned long frmidx = 0; frmidx < framecounts; frmidx++)
        {
        	int frmi = frmidx;
        	if(reverseFrames)
			{
				frmi = (framecounts - 1) - frmidx;
			}
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            if(shdincluded)
            {
                tempshddata = GetUndeletedGlobalizedShdFrameData(frmi);
                if(tempshddata != NULL)
                {
                    for(long pixi = 0; pixi < GetGlobalWidth()*GetGlobalHeight(); pixi++)
                    {
                        if(tempfrmdata[pixi].rgbReserved != 0)
                        {
                            tempshddata[pixi].rgbBlue = tempfrmdata[pixi].rgbBlue;
                            tempshddata[pixi].rgbGreen = tempfrmdata[pixi].rgbGreen;
                            tempshddata[pixi].rgbRed = tempfrmdata[pixi].rgbRed;
                            tempshddata[pixi].rgbReserved = tempfrmdata[pixi].rgbReserved;
                        }
                    }
                    delete[] tempfrmdata;
                    tempfrmdata = tempshddata;
                }
            }

            proc.AddFrame(tempfrmdata);
        }

        if(!proc.SaveToPng(outpath)) return false;
    }
    else
    {
        for(unsigned long frmidx = 0; frmidx < framecounts; frmidx++)
        {
        	int frmi = frmidx;
        	if(reverseFrames)
			{
				frmi = (framecounts - 1) - frmidx;
			}
            tempfrmdata = GetUndeletedGlobalizedFrameData(frmi);
            if(tempfrmdata == NULL) return false;

            if(alphamask != 0)
            {
                MAPICDATA::MakeTransMask(tempfrmdata, GetGlobalWidth(), GetGlobalHeight(), alphamask);
            }

            tempframe = GetUndeletedFrameData(frmi);

            if(tempframe->islocked)
            {
                tsunx = tempframe->sunoffx;
                tsuny = tempframe->sunoffy;
                tshdx = tempframe->shadowoffx;
                tshdy = tempframe->shadowoffy;
            }
            else
            {
                tsunx = globalsunoffx;
                tsuny = globalsunoffy;
                tshdx = globalshadowoffx;
                tshdy = globalshadowoffy;
            }

            tempshd.ReNew();
            tempshd.Init(GetGlobalWidth(), GetGlobalHeight());

            tempshd.AddFrame(tempfrmdata);
            tempshddata = tempshd.MakeShadow(shdtype, 0, true, tsunx, tsuny, tshdx, tshdy, shadowalpha);

            if(!tempshddata) return false;

            shdproc.AddFrame(tempshddata);
        }

        if(!shdproc.SaveToPng(outpath))return false;
    }

    return true;
}

bool WorkManager::SetFrameLock(unsigned long index, bool locked)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return false;

    temp->islocked = locked;
    return true;
}
bool WorkManager::SetFrameSunX(unsigned long index, long Sunx)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return false;

    temp->sunoffx = Sunx;
    return true;
}
bool WorkManager::SetFrameSunY(unsigned long index, long Suny)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return false;

    temp->sunoffy = Suny;
    return true;
}
bool WorkManager::SetFrameShadowX(unsigned long index, long ShadowX)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return false;

    temp->shadowoffx = ShadowX;
    return true;
}
bool WorkManager::SetFrameShadowY(unsigned long index, long ShadowY)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return false;

    temp->shadowoffy = ShadowY;
    return true;
}
bool WorkManager::IsFrameLocked(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return false;

    return temp->islocked;
}
long WorkManager::GetFrameSunX(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return 0;

    return temp->sunoffx;
}
long WorkManager::GetFrameSunY(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return 0;

    return temp->sunoffy;
}
long WorkManager::GetFrameShadowX(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return 0;

    return temp->shadowoffx;
}
long WorkManager::GetFrameShadowY(unsigned long index)
{
    FRAMERGBA *temp;

    temp = GetUndeletedFrameData(index);
    if(temp == NULL)return 0;

    return temp->shadowoffy;
}

/////////////////
//private
/////////////////
void WorkManager::FreeRGBAData()
{
    if(firstframe != NULL)
    {
        FRAMERGBA *cur, *next;
        cur = firstframe;
        next = cur->next;
        for(; cur != NULL;)
        {
            delete[] cur->data;
            if(cur->shddata != NULL) delete[] cur->shddata;
            delete cur;
            cur = next;
            if(cur != NULL)next = cur->next;
        }
    }
}
void WorkManager::AddBaseColor(FILOCRGBQUAD *inout, long width, long height)
{
    unsigned char alpha;
    for(long pixi = 0; pixi < width*height; pixi++)
    {
        alpha = inout[pixi].rgbReserved;
        if(alpha == 0) continue;

        inout[pixi].rgbRed   = (BYTE)(((double)inout[pixi].rgbRed)*((double)alpha/(double)0xFF) +
                                      ((double)basecolor.Red())*((double)(0xFF-alpha)/(double)0xFF));
        inout[pixi].rgbGreen = (BYTE)(((double)inout[pixi].rgbGreen)*((double)alpha/(double)0xFF) +
                                      ((double)basecolor.Green())*((double)(0xFF-alpha)/(double)0xFF));
        inout[pixi].rgbBlue  = (BYTE)(((double)inout[pixi].rgbBlue)*((double)alpha/(double)0xFF) +
                                      ((double)basecolor.Blue())*((double)(0xFF-alpha)/(double)0xFF));
        inout[pixi].rgbReserved = 0xFF;
    }
}
