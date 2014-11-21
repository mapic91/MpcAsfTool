#include "WorkManager.hpp"
#include "wx/filename.h"
#include "RpcDecode.hpp"

///////////////
//public
//////////////
bool WorkManager::OpenFile(wxString InPath, int frameBegin, int frameEnd )
{
    if(InPath.IsEmpty()) return false;
    wxString ext;
    long tempwidth, tempheight;
    FILOCRGBQUAD *tempdata, *tempshddata;

    ext = wxFileName::FileName(InPath).GetExt();

    if(ext.CmpNoCase(wxT("mpc")) == 0)
    {
        if(!mpcdecode.ReadMpcFile(InPath)) return false;

        tempwidth = mpcdecode.GetGlobleWidth();
        tempheight = mpcdecode.GetGlobleHeight();
        SetGlobalWidth(tempwidth);
        SetGlobalHeight(tempheight);
        SetDirection(mpcdecode.GetDirection());
        SetBottom(mpcdecode.GetBottom());
        SetInterval(mpcdecode.GetInterval());

        tempshddata = NULL;
        for(unsigned long conti = frameBegin; conti < mpcdecode.GetFramesCounts() && ((int)conti) <= frameEnd; conti++)
        {
            tempdata = mpcdecode.GetGlobleFIDecodedFrameData(conti, NULL, NULL, MpcDecode::PIC_BGRA);
            if(!tempdata) return false;
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
    else
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
