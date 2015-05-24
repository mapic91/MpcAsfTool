#include <fstream>

#include "MAPICDATA.hpp"

#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wx/filename.h"
#include <cstdlib>

using namespace std;

MAPICDATA::~MAPICDATA()
{
    FreeRGBAData();
}
void MAPICDATA::Init()
{
    globalwidth = 0;
    globalheight = 0;
    firstframe = NULL;
    currentframe = NULL;
    pixindex = NULL;
    framecounts = 0;
    isquantized = false;
}
void MAPICDATA::AddFrame(FILOCRGBQUAD *frame)
{
    isquantized = false;
    if(firstframe == NULL)
    {
        firstframe = new FRAMERGBA();
        firstframe->data = frame;
        firstframe->next = NULL;
        currentframe = firstframe;
    }
    else
    {
        currentframe->next = new FRAMERGBA();
        currentframe = currentframe->next;
        currentframe->data = frame;
        currentframe->next = NULL;
    }
    framecounts++;
}
FRAMERGBA* MAPICDATA::GetFrameData(unsigned long index)
{
    if(index >= framecounts) return NULL;

    FRAMERGBA *temp;

    temp = firstframe;
    for(unsigned long i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}
FIBYTE* MAPICDATA::GetPixIndexData()
{
    if(isquantized) return pixindex;
    else return NULL;
}
bool MAPICDATA::Quantize(const int palettesize, bool keepalpha)
{
    if(framecounts == 0) return false;
    if(pixindex != NULL)
    {
        free(pixindex);
        pixindex = NULL;
    }

    unsigned long sumidx, sumsize = globalwidth*globalheight*framecounts*4,
                          globalpixsum = globalwidth*globalheight;
    FRAMERGBA *temprgba;
    FIBYTE *sumdata,red,green,blue,alpha;
    FIBITMAP *sumsample, *bmp24, *bmp8;
    FILOCRGBQUAD *plt;

    sumdata = (FIBYTE*)malloc(sumsize);
    if(!sumdata)return false;

    sumidx = 0;
    temprgba = firstframe;
    for(unsigned long fridx = 0; fridx < framecounts; fridx++)
    {
        for(unsigned long dati = 0; dati < globalpixsum; dati++)
        {
            alpha = temprgba->data[dati].rgbReserved;
            if(alpha != 0)
            {
                red = temprgba->data[dati].rgbRed;
                green = temprgba->data[dati].rgbGreen;
                blue = temprgba->data[dati].rgbBlue;
                if(keepalpha)
                {
                    sumdata[sumidx++] = blue;
                    sumdata[sumidx++] = green;
                    sumdata[sumidx++] = red;
                    sumdata[sumidx++] = 0xFF;
                }
                else
                {
                    sumdata[sumidx++] = (FIBYTE)(((double)blue)*((double)alpha/(double)0xFF) +
                                                 ((double)0xFF)*((double)(0xFF-alpha)/(double)0xFF));
                    sumdata[sumidx++] = (FIBYTE)(((double)green)*((double)alpha/(double)0xFF) +
                                                 ((double)0xFF)*((double)(0xFF-alpha)/(double)0xFF));
                    sumdata[sumidx++] = (FIBYTE)(((double)red)*((double)alpha/(double)0xFF) +
                                                 ((double)0xFF)*((double)(0xFF-alpha)/(double)0xFF));
                    sumdata[sumidx++] = 0xFF;
                }

            }
        }
        temprgba = temprgba->next;
    }

    quatwidth = sumidx/4;
    sumsample = FreeImage_ConvertFromRawBits(sumdata, quatwidth, 1, sumidx, 32, FI_RGBA_RED_MASK,
                FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);

    if(!sumsample) return false;
    free(sumdata);
    sumdata = NULL;
    bmp24 = FreeImage_ConvertTo24Bits(sumsample);
    if(!bmp24) return false;
    bmp8 = FreeImage_ColorQuantizeEx(bmp24, FIQ_WUQUANT, palettesize);
    if(!bmp8) return false;

    plt = FreeImage_GetPalette(bmp8);
    if(!plt) return false;

    for(int pltidx = 0; pltidx < palettesize; pltidx++)
    {
        palette[pltidx].rgbBlue = plt[pltidx].rgbBlue;
        palette[pltidx].rgbGreen = plt[pltidx].rgbGreen;
        palette[pltidx].rgbRed = plt[pltidx].rgbRed;
        palette[pltidx].rgbReserved  = plt[pltidx].rgbReserved;
    }
    pltsize = palettesize;

    pixindex = (FIBYTE*)malloc(quatwidth);
    if(!pixindex) return false;
    for(unsigned long locpix = 0; locpix < quatwidth; locpix++)
    {
        if(!FreeImage_GetPixelIndex(bmp8, locpix, 0, pixindex+locpix)) return false;
    }

    isquantized = true;
    return true;

}
void MAPICDATA::FreeRGBAData()
{
    if(firstframe != NULL)
    {
        FRAMERGBA *cur, *next;
        cur = firstframe;
        next = cur->next;
        for(; cur != NULL;)
        {
            delete[] cur->data;
            delete cur;
            cur = next;
            if(cur != NULL)next = cur->next;
        }
    }
}
bool MAPICDATA::SaveToPng(const wxString path)
{
    if(framecounts == 0) return false;

    FRAMERGBA *temprgba;
    FIBYTE *buffer;
    long bufsize = globalwidth*globalheight*4;
    unsigned long pixcout = globalwidth*globalheight, bufidx;
    FIBITMAP *png;

    buffer = (FIBYTE*)malloc((size_t)bufsize);
    if(!buffer) return false;

    temprgba = firstframe;
    for(unsigned long fridx = 0; fridx < framecounts; fridx++)
    {
        bufidx = 0;
        for(unsigned long pixi = 0; pixi < pixcout; pixi++)
        {
            buffer[bufidx++] = temprgba->data[pixi].rgbBlue;
            buffer[bufidx++] = temprgba->data[pixi].rgbGreen;
            buffer[bufidx++] = temprgba->data[pixi].rgbRed;
            buffer[bufidx++] = temprgba->data[pixi].rgbReserved;
        }
        png = FreeImage_ConvertFromRawBits(buffer, globalwidth, globalheight, globalwidth*4, 32, FI_RGBA_RED_MASK,
                                           FI_RGBA_GREEN_MASK,FI_RGBA_BLUE_MASK, TRUE);
        if(!png)
        {
            free(buffer);
            return false;
        }
        if(framecounts == 1)
        {
            if(!FreeImage_SaveU(FIF_PNG, png, path + wxT(".png")))
            {
                FreeImage_Unload(png);
                free(buffer);
                return false;
            }
        }
        else
        {
            if(!FreeImage_SaveU(FIF_PNG, png, path + wxString::Format(wxT("-%03ld.png"), fridx+1)))
            {
                FreeImage_Unload(png);
                free(buffer);
                return false;
            }
        }
        FreeImage_Unload(png);

        temprgba = temprgba->next;
    }
    free(buffer);
    return true;
}
bool MAPICDATA::SaveToGif(const wxString path)
{
    if(framecounts == 0) return false;
    if(!isquantized)
    {
        if(!Quantize(255)) return false;
    }

    FIBITMAP *page;
    FIMULTIBITMAP *gif;
    FILOCRGBQUAD *pageplt;
    unsigned long pixidxc;
    FIBYTE trasidx = 0xFF;
    FRAMERGBA *temprgba;

    gif = FreeImage_OpenMultiBitmap(FIF_GIF, path.char_str(), TRUE, FALSE, TRUE);
    if(!gif)return false;

    page = FreeImage_Allocate(globalwidth, globalheight, 8);
    if(!page)
    {
        FreeImage_CloseMultiBitmap(gif);
        return false;
    }
    pageplt = FreeImage_GetPalette(page);
    if(!pageplt)
    {
        FreeImage_CloseMultiBitmap(gif);
        return false;
    }
    for(int cpi = 0; cpi < 256; cpi++)
    {
        pageplt[cpi].rgbBlue = palette[cpi].rgbBlue;
        pageplt[cpi].rgbGreen = palette[cpi].rgbGreen;
        pageplt[cpi].rgbRed = palette[cpi].rgbRed;
        pageplt[cpi].rgbReserved = palette[cpi].rgbReserved;//not really needed
    }
    FreeImage_SetTransparentIndex(page, trasidx);

    temprgba = firstframe;
    pixidxc = 0;
    for(unsigned long fridx = 0; fridx < framecounts; fridx++)
    {
        if(pixidxc > quatwidth || temprgba == NULL)return false;

        for(unsigned long hi = 0; hi < (unsigned long)globalheight; hi++)
        {
            for(unsigned long wi = 0; wi < (unsigned long)globalwidth; wi++)
            {
                if(temprgba->data[hi*globalwidth+wi].rgbReserved == 0)
                {
                    FreeImage_SetPixelIndex(page, wi, globalheight-1-hi, &trasidx);
                }
                else
                {
                    FreeImage_SetPixelIndex(page, wi, globalheight-1-hi, pixindex+(pixidxc++));
                }
            }
        }

        FreeImage_AppendPage(gif, page);
        temprgba = temprgba->next;
    }
    FreeImage_Unload(page);

    if(!FreeImage_CloseMultiBitmap(gif)) return false;

    return true;
}
bool MAPICDATA::SaveToMpc(const wxString path, long direction, long interval, long bottom, bool makeshow, int codeType)
{
    if(framecounts == 0) return false;

    if(makeshow)
    {
        MAPICDATA *shddata;
        if(!MakeShadow(SHD_MPC, &shddata)) return false;
        wxString shdpath = wxFileName::FileName(path).GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);
        shdpath += wxFileName::FileName(path).GetName();
        shdpath += wxT(".shd");
        if(!shddata->SaveToShd(shdpath, direction, interval, bottom))
        {
            delete shddata;
            return false;
        }
        else delete shddata;
    }

    if(!Quantize(256, codeType == 1)) return false;

    unsigned long databeg, framedatasum, encodelen, pipos, tempsize;
    unsigned char *encdata = NULL;
    long wli = 0,hi = 0;
    FRAMERGBA *tempframe;
    unsigned char coliline[globalwidth + 1];
    unsigned char maskline[globalwidth + 1];

    unsigned char temp[8];
    char headinf[] = "MPC File Ver2.0";
    char nullv[60] = {0};

    ofstream outfile(path.char_str(), ios_base::out|ios_base::binary);
    if(!outfile.is_open()) return false;

    outfile.write(headinf, 15); //version info
    outfile.write(nullv, 49); // zero
    outfile.seekp(4, ios_base::cur); //frames data length(head+data) sum
    temp[0] = (unsigned char)( globalwidth & 0xFF );
    temp[1] = (unsigned char)( (globalwidth & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (globalwidth & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (globalwidth & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//width(global)
    temp[0] = (unsigned char)( globalheight & 0xFF );
    temp[1] = (unsigned char)( (globalheight & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (globalheight & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (globalheight & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//height(global)
    temp[0] = (unsigned char)( framecounts & 0xFF );
    temp[1] = (unsigned char)( (framecounts & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (framecounts & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (framecounts & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//fram counts
    temp[0] = (unsigned char)( direction & 0xFF );
    temp[1] = (unsigned char)( (direction & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (direction & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (direction & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//direction
    temp[0] = (unsigned char)(256 & 0xFF);
    temp[1] = (unsigned char)((256 & 0xFF00) >> 8);
    temp[2] = (unsigned char)((256 & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((256 & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//colour counts
    temp[0] = (unsigned char)(interval & 0xFF);
    temp[1] = (unsigned char)((interval & 0xFF00) >> 8);
    temp[2] = (unsigned char)((interval & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((interval & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//interval
    temp[0] = (unsigned char)(bottom & 0xFF);
    temp[1] = (unsigned char)((bottom & 0xFF00) >> 8);
    temp[2] = (unsigned char)((bottom & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((bottom & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//bottom
    if(codeType == 1)
    {
        nullv[0] = 0x06;
    }
    outfile.write(nullv, 32);//null
    nullv[0] = 0x00;
    for(int plti = 0; plti < 256; plti++)//palette
    {
        outfile.write((char*)(&palette[plti].rgbBlue), 1);
        outfile.write((char*)(&palette[plti].rgbGreen), 1);
        outfile.write((char*)(&palette[plti].rgbRed), 1);
        outfile.write((char*)(&palette[plti].rgbReserved), 1);
    }

    databeg = (unsigned long)outfile.tellp();//frame 0 data offset

    //outfile.write(nullv, 4);

    pipos = 0;
    framedatasum = 0;
    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        encodelen = 20;//frame data head length

        outfile.seekp(databeg+4*frmi, ios_base::beg);
        temp[0] = (unsigned char)(framedatasum & 0xFF);
        temp[1] = (unsigned char)((framedatasum & 0xFF00) >> 8);
        temp[2] = (unsigned char)((framedatasum & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((framedatasum & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);// frame data offset

        outfile.seekp(databeg+4*framecounts+framedatasum+20, ios_base::beg);//frame data

        for(hi = 0; hi < globalheight; hi++)
        {

            for(wli =0; wli < globalwidth; wli++)
            {
                if(tempframe->data[hi*globalwidth+wli].rgbReserved == 0x00)
                {
                    maskline[wli] = 0;
                }
                else
                {
                    maskline[wli] = (codeType == 0 ? 1 : tempframe->data[hi*globalwidth+wli].rgbReserved);
                    coliline[wli] = pixindex[pipos++];
                }
            }

            encdata = MpcRunLenEncode(maskline, coliline, &tempsize, codeType);
            if(!encdata)
            {
                outfile.close();
                return false;
            }
            outfile.write((char*)encdata, tempsize);
            encodelen += tempsize;
            free(encdata);
            encdata = NULL;
        }

        outfile.seekp(databeg+4*framecounts+framedatasum, ios_base::beg);//frame data
        temp[0] = (unsigned char)(encodelen & 0xFF);
        temp[1] = (unsigned char)((encodelen & 0xFF00) >> 8);
        temp[2] = (unsigned char)((encodelen & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((encodelen & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//encoded frame data length + head length
        temp[0] = (unsigned char)(globalwidth & 0xFF);
        temp[1] = (unsigned char)((globalwidth & 0xFF00) >> 8);
        temp[2] = (unsigned char)((globalwidth & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((globalwidth & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//width is same to globalwidth
        temp[0] = (unsigned char)(globalheight & 0xFF);
        temp[1] = (unsigned char)((globalheight & 0xFF00) >> 8);
        temp[2] = (unsigned char)((globalheight & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((globalheight & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//height is same to globalheight
        outfile.write(nullv, 8); //8 bytes null

        framedatasum += encodelen;

        tempframe = tempframe->next;
    }

    outfile.seekp(64, ios_base::beg);
    temp[0] = (unsigned char)(framedatasum & 0xFF);
    temp[1] = (unsigned char)((framedatasum & 0xFF00) >> 8);
    temp[2] = (unsigned char)((framedatasum & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((framedatasum & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//frames data length(head+data) sum

    if(!outfile.good())
    {
        outfile.close();
        return false;
    }
    outfile.close();

    return true;
}
bool MAPICDATA::SaveToAsf(const wxString path, long direction, long interval,
                          long left, long bottom, bool makeshow,
                          long offsetsunx, long offsetsuny,long offsetposx, long offsetposy)
{
    if(framecounts == 0) return false;

    if(makeshow)
    {
        if(!MakeShadow(SHD_ASF, NULL, offsetsunx, offsetsuny, offsetposx, offsetposy)) return false;
    }
    if(!Quantize(256, true)) return false;

    unsigned long databeg, framedatasum, encodelen, pipos, tempsize;
    unsigned char *encdata = NULL;
    long wli = 0,hi = 0;
    FRAMERGBA *tempframe;
    unsigned char coliline[globalwidth];
    unsigned char maskline[globalwidth];

    unsigned char temp[8];
    char headinf[] = "ASF 1.00";
    char nullv[60] = {0};

    ofstream outfile(path.char_str(), ios_base::out|ios_base::binary);
    if(!outfile.is_open()) return false;

    outfile.write(headinf, 8); //version info
    outfile.write(nullv, 8); // zero
    temp[0] = (unsigned char)( globalwidth & 0xFF );
    temp[1] = (unsigned char)( (globalwidth & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (globalwidth & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (globalwidth & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//width(global)
    temp[0] = (unsigned char)( globalheight & 0xFF );
    temp[1] = (unsigned char)( (globalheight & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (globalheight & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (globalheight & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//height(global)
    temp[0] = (unsigned char)( framecounts & 0xFF );
    temp[1] = (unsigned char)( (framecounts & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (framecounts & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (framecounts & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//fram counts
    temp[0] = (unsigned char)( direction & 0xFF );
    temp[1] = (unsigned char)( (direction & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (direction & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (direction & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//direction
    temp[0] = (unsigned char)(256 & 0xFF);
    temp[1] = (unsigned char)((256 & 0xFF00) >> 8);
    temp[2] = (unsigned char)((256 & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((256 & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//colour counts
    temp[0] = (unsigned char)(interval & 0xFF);
    temp[1] = (unsigned char)((interval & 0xFF00) >> 8);
    temp[2] = (unsigned char)((interval & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((interval & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//interval
    temp[0] = (unsigned char)(bottom & 0xFF);
    temp[1] = (unsigned char)((bottom & 0xFF00) >> 8);
    temp[2] = (unsigned char)((bottom & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((bottom & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//bottom
    temp[0] = (unsigned char)(left & 0xFF);
    temp[1] = (unsigned char)((left & 0xFF00) >> 8);
    temp[2] = (unsigned char)((left & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((left & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//left
    outfile.write(nullv, 16);//null
    for(int plti = 0; plti < 256; plti++)//palette
    {
        outfile.write((char*)(&palette[plti].rgbBlue), 1);
        outfile.write((char*)(&palette[plti].rgbGreen), 1);
        outfile.write((char*)(&palette[plti].rgbRed), 1);
        outfile.write((char*)(&palette[plti].rgbReserved), 1);
    }

    databeg = (unsigned long)outfile.tellp();//frame 0 data offset

    pipos = 0;
    framedatasum = 0;
    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        encodelen = 0;

        outfile.seekp(databeg+frmi*8, ios_base::beg);
        temp[0] = (unsigned char)((databeg+framecounts*8+framedatasum) & 0xFF);
        temp[1] = (unsigned char)(((databeg+framecounts*8+framedatasum) & 0xFF00) >> 8);
        temp[2] = (unsigned char)(((databeg+framecounts*8+framedatasum) & 0xFF0000) >> 16);
        temp[3] = (unsigned char)(((databeg+framecounts*8+framedatasum) & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);// frame data position(from file head)

        outfile.seekp(databeg+framecounts*8+framedatasum, ios_base::beg);//frame data

        for(hi = 0; hi < globalheight; hi++)
        {

            for(wli =0; wli < globalwidth; wli++)
            {
                if(tempframe->data[hi*globalwidth+wli].rgbReserved == 0x00)
                {
                    maskline[wli] = 0;
                }
                else
                {
                    maskline[wli] = tempframe->data[hi*globalwidth+wli].rgbReserved;
                    coliline[wli] = pixindex[pipos++];
                }
            }

            encdata = AsfRunLenEncode(maskline, coliline, &tempsize);
            if(!encdata)
            {
                outfile.close();
                return false;
            }
            outfile.write((char*)encdata, tempsize);
            encodelen += tempsize;
            free(encdata);
            encdata = NULL;
        }

        outfile.seekp(databeg+frmi*8+4, ios_base::beg);//frame data length began
        temp[0] = (unsigned char)(encodelen & 0xFF);
        temp[1] = (unsigned char)((encodelen & 0xFF00) >> 8);
        temp[2] = (unsigned char)((encodelen & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((encodelen & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//frame data length

        framedatasum += encodelen;

        tempframe = tempframe->next;
    }

    if(!outfile.good())
    {
        outfile.close();
        return false;
    }
    outfile.close();

    return true;
}
bool MAPICDATA::SaveToShd(const wxString path, long direction, long interval, long bottom)
{
    if(framecounts == 0) return false;

    unsigned long databeg, framedatasum, encodelen, tempsize;
    unsigned char *encdata = NULL;
    long wli = 0,hi = 0;
    FRAMERGBA *tempframe;
    unsigned char maskline[globalwidth];

    unsigned char temp[8];
    char headinf[] = "SHD File Ver2.0";
    char nullv[60] = {0};

    ofstream outfile(path.char_str(), ios_base::out|ios_base::binary);
    if(!outfile.is_open()) return false;

    outfile.write(headinf, 15); //version info
    outfile.write(nullv, 49); // zero
    outfile.seekp(4, ios_base::cur); //frames data length(head+data) sum
    temp[0] = (unsigned char)( globalwidth & 0xFF );
    temp[1] = (unsigned char)( (globalwidth & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (globalwidth & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (globalwidth & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//width(global)
    temp[0] = (unsigned char)( globalheight & 0xFF );
    temp[1] = (unsigned char)( (globalheight & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (globalheight & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (globalheight & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//height(global)
    temp[0] = (unsigned char)( framecounts & 0xFF );
    temp[1] = (unsigned char)( (framecounts & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (framecounts & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (framecounts & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//fram counts
    temp[0] = (unsigned char)( direction & 0xFF );
    temp[1] = (unsigned char)( (direction & 0xFF00) >> 8 );
    temp[2] = (unsigned char)( (direction & 0xFF0000) >> 16 );
    temp[3] = (unsigned char)( (direction & 0xFF000000) >> 24 );
    outfile.write((char*)temp, 4);//direction
    temp[0] = (unsigned char)(256 & 0xFF);
    temp[1] = (unsigned char)((256 & 0xFF00) >> 8);
    temp[2] = (unsigned char)((256 & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((256 & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//colour counts
    temp[0] = (unsigned char)(interval & 0xFF);
    temp[1] = (unsigned char)((interval & 0xFF00) >> 8);
    temp[2] = (unsigned char)((interval & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((interval & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//interval
    temp[0] = (unsigned char)(bottom & 0xFF);
    temp[1] = (unsigned char)((bottom & 0xFF00) >> 8);
    temp[2] = (unsigned char)((bottom & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((bottom & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//bottom
    outfile.write(nullv, 32);//null

    databeg = (unsigned long)outfile.tellp();//frame 0 data offset

    //outfile.write(nullv, 4);

    framedatasum = 0;
    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        encodelen = 20;//frame data head length

        outfile.seekp(databeg+4*frmi, ios_base::beg);
        temp[0] = (unsigned char)(framedatasum & 0xFF);
        temp[1] = (unsigned char)((framedatasum & 0xFF00) >> 8);
        temp[2] = (unsigned char)((framedatasum & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((framedatasum & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);// frame data offset

        outfile.seekp(databeg+4*framecounts+framedatasum+20, ios_base::beg);//frame data

        for(hi = 0; hi < globalheight; hi++)
        {

            for(wli =0; wli < globalwidth; wli++)
            {
                if(tempframe->data[hi*globalwidth+wli].rgbReserved == 0x00)
                {
                    maskline[wli] = 0;
                }
                else
                {
                    maskline[wli] = 1;
                }
            }

            encdata = ShdRunLenEncode(maskline, &tempsize);
            if(!encdata)
            {
                outfile.close();
                return false;
            }
            outfile.write((char*)encdata, tempsize);
            encodelen += tempsize;
            free(encdata);
            encdata = NULL;
        }

        outfile.seekp(databeg+4*framecounts+framedatasum, ios_base::beg);//frame data
        temp[0] = (unsigned char)(encodelen & 0xFF);
        temp[1] = (unsigned char)((encodelen & 0xFF00) >> 8);
        temp[2] = (unsigned char)((encodelen & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((encodelen & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//encoded frame data length + head length
        temp[0] = (unsigned char)(globalwidth & 0xFF);
        temp[1] = (unsigned char)((globalwidth & 0xFF00) >> 8);
        temp[2] = (unsigned char)((globalwidth & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((globalwidth & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//width is same to globalwidth
        temp[0] = (unsigned char)(globalheight & 0xFF);
        temp[1] = (unsigned char)((globalheight & 0xFF00) >> 8);
        temp[2] = (unsigned char)((globalheight & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((globalheight & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);//height is same to globalheight
        outfile.write(nullv, 8); //8 bytes null

        framedatasum += encodelen;

        tempframe = tempframe->next;
    }

    outfile.seekp(64, ios_base::beg);
    temp[0] = (unsigned char)(framedatasum & 0xFF);
    temp[1] = (unsigned char)((framedatasum & 0xFF00) >> 8);
    temp[2] = (unsigned char)((framedatasum & 0xFF0000) >> 16);
    temp[3] = (unsigned char)((framedatasum & 0xFF000000) >> 24);
    outfile.write((char*)temp, 4);//frames data length(head+data) sum

    if(!outfile.good())
    {
        outfile.close();
        return false;
    }
    outfile.close();

    return true;
}
bool MAPICDATA::MakeShadow(SHD_TYPE type, MAPICDATA **outshd, long offsetsunx, long offsetsuny,
                           long offsetposx, long offsetposy, unsigned char shadowalpha)
{
    if(framecounts == 0) return false;

    FRAMERGBA *tempframe;
    long basey = 0, shdx, shdy;
    long offx, offy;
    const long precision = 12;

    switch(type)
    {
    case SHD_MPC:
        offx = 4 + offsetsunx;
        offy = 4 + offsetsuny;
        break;
    case SHD_ASF:
        offx = 6 + offsetsunx;
        offy = 3 + offsetsuny;
        break;
    default:
        return false;
    }


    tempframe = firstframe;

    FILOCRGBQUAD *shdframe = NULL;
    MAPICDATA *shddata = new MAPICDATA(globalwidth, globalheight);

    if(!shddata) return false;

    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        shdframe = new FILOCRGBQUAD[globalwidth*globalheight];
        if(!shdframe)
        {
            delete shddata;
            return false;
        }
        //initializing to transparent
        for(long initi = 0; initi < globalwidth*globalheight; initi++)
        {
            shdframe[initi].rgbBlue = 0xFF;
            shdframe[initi].rgbGreen = 0xFF;
            shdframe[initi].rgbRed = 0xFF;
            shdframe[initi].rgbReserved = 0x00;
        }

        for(long ihi = globalheight - 1; ihi >= 0; ihi--)
        {
            for(long iwi = 0 ; iwi < globalwidth; iwi++)
            {
                if(tempframe->data[ihi*globalwidth+iwi].rgbReserved != 0)
                {
                    basey = ihi;
                    iwi = globalwidth;
                    ihi = -1;
                }
            }
        }

        if(offx >= 0)//make shadow right to left, because shadow is at right or middle
        {
            for(long wi = globalwidth - 1 ; wi >=0; wi--)
            {
                for(long hi = globalheight - 1; hi >= 0; hi--)
                {
                    if(tempframe->data[hi*globalwidth+wi].rgbReserved != 0)
                    {

                        shdx = (long)( ((double)(basey - hi))*((double)offx/(double)precision) + (double) wi + (double)offsetposx );
                        shdy = (long)( (double)basey - ((double)(basey - hi))*((double)offy/(double)precision) - (double)offsetposy );

                        if(shdy < globalheight && shdy >= 0 &&
                                shdx < globalwidth && shdx >= 0 &&
                                tempframe->data[shdy*globalwidth+shdx].rgbReserved == 0x00)
                        {
                            shdframe[shdy*globalwidth+shdx].rgbBlue = 0x00;
                            shdframe[shdy*globalwidth+shdx].rgbGreen = 0x00;
                            shdframe[shdy*globalwidth+shdx].rgbRed = 0x00;
                            shdframe[shdy*globalwidth+shdx].rgbReserved = shadowalpha;
                        }
                    }
                }
            }
        }
        else//make shadow left to right, because shadow is at left
        {
            for(long wi = 0 ; wi < globalwidth; wi++)
            {
                for(long hi = globalheight - 1; hi >= 0; hi--)
                {
                    if(tempframe->data[hi*globalwidth+wi].rgbReserved != 0)
                    {

                        shdx = (long)( ((double)(basey - hi))*((double)offx/(double)precision) + (double) wi + (double)offsetposx );
                        shdy = (long)( (double)basey - ((double)(basey - hi))*((double)offy/(double)precision) - (double)offsetposy );

                        if(shdy < globalheight && shdy >= 0 &&
                                shdx < globalwidth && shdx >= 0 &&
                                tempframe->data[shdy*globalwidth+shdx].rgbReserved == 0x00)
                        {
                            shdframe[shdy*globalwidth+shdx].rgbBlue = 0x00;
                            shdframe[shdy*globalwidth+shdx].rgbGreen = 0x00;
                            shdframe[shdy*globalwidth+shdx].rgbRed = 0x00;
                            shdframe[shdy*globalwidth+shdx].rgbReserved = shadowalpha;
                        }
                    }
                }
            }
        }

        if(outshd == NULL)
        {
            for(long pixi = 0; pixi < globalwidth*globalheight; pixi++)
            {
                if(shdframe[pixi].rgbReserved != 0 &&
                        tempframe->data[pixi].rgbReserved == 0)
                {
                    tempframe->data[pixi].rgbBlue = shdframe[pixi].rgbBlue;
                    tempframe->data[pixi].rgbGreen = shdframe[pixi].rgbGreen;
                    tempframe->data[pixi].rgbRed = shdframe[pixi].rgbRed;
                    tempframe->data[pixi].rgbReserved = shdframe[pixi].rgbReserved;
                }
            }
        }

        shddata->AddFrame(shdframe);
        tempframe = tempframe->next;
    }
    if(outshd != NULL)*outshd = shddata;
    else delete shddata;

    return true;
}
FILOCRGBQUAD* MAPICDATA::MakeShadow(SHD_TYPE type, unsigned long index, bool orgincluded, long offsetsunx, long offsetsuny,
                                    long offsetposx, long offsetposy, unsigned char shadowalpha)
{
    if(index >= framecounts) return NULL;

    FRAMERGBA *tempframe;
    FILOCRGBQUAD *shdframe;
    long basey = 0, shdx, shdy;
    long offx, offy;
    const long precision = 12;

    switch(type)
    {
    case SHD_MPC:
        offx = 4 + offsetsunx;
        offy = 4 + offsetsuny;
        break;
    case SHD_ASF:
        offx = 6 + offsetsunx;
        offy = 3 + offsetsuny;
        break;
    default:
        return NULL;
    }

    tempframe = GetFrameData(index);
    shdframe = NULL;

    shdframe = new FILOCRGBQUAD[globalwidth*globalheight];
    if(!shdframe)
    {
        return NULL;
    }
    //initializing to transparent
    for(long initi = 0; initi < globalwidth*globalheight; initi++)
    {
        shdframe[initi].rgbBlue = 0xFF;
        shdframe[initi].rgbGreen = 0xFF;
        shdframe[initi].rgbRed = 0xFF;
        shdframe[initi].rgbReserved = 0x00;
    }

    for(long ihi = globalheight - 1; ihi >= 0; ihi--)
    {
        for(long iwi = 0 ; iwi < globalwidth; iwi++)
        {
            if(tempframe->data[ihi*globalwidth+iwi].rgbReserved != 0)
            {
                basey = ihi;
                iwi = globalwidth;
                ihi = -1;
            }
        }
    }

    if(offx >= 0)//make shadow right to left, because shadow is at right or middle
    {
        for(long wi = globalwidth - 1 ; wi >=0; wi--)
        {
            for(long hi = globalheight - 1; hi >= 0; hi--)
            {
                if(tempframe->data[hi*globalwidth+wi].rgbReserved != 0)
                {

                    shdx = (long)( ((double)(basey - hi))*((double)offx/(double)precision) + (double) wi + (double)offsetposx );
                    shdy = (long)( (double)basey - ((double)(basey - hi))*((double)offy/(double)precision) - (double)offsetposy );

                    if(shdy < globalheight && shdy >= 0 &&
                            shdx < globalwidth && shdx >= 0 &&
                            tempframe->data[shdy*globalwidth+shdx].rgbReserved == 0x00)
                    {
                        shdframe[shdy*globalwidth+shdx].rgbBlue = 0x00;
                        shdframe[shdy*globalwidth+shdx].rgbGreen = 0x00;
                        shdframe[shdy*globalwidth+shdx].rgbRed = 0x00;
                        shdframe[shdy*globalwidth+shdx].rgbReserved = shadowalpha;
                    }
                }
            }
        }
    }
    else//make shadow left to right, because shadow is at left
    {
        for(long wi = 0 ; wi < globalwidth; wi++)
        {
            for(long hi = globalheight - 1; hi >= 0; hi--)
            {
                if(tempframe->data[hi*globalwidth+wi].rgbReserved != 0)
                {

                    shdx = (long)( ((double)(basey - hi))*((double)offx/(double)precision) + (double) wi + (double)offsetposx );
                    shdy = (long)( (double)basey - ((double)(basey - hi))*((double)offy/(double)precision) - (double)offsetposy );

                    if(shdy < globalheight && shdy >= 0 &&
                            shdx < globalwidth && shdx >= 0 &&
                            tempframe->data[shdy*globalwidth+shdx].rgbReserved == 0x00)
                    {
                        shdframe[shdy*globalwidth+shdx].rgbBlue = 0x00;
                        shdframe[shdy*globalwidth+shdx].rgbGreen = 0x00;
                        shdframe[shdy*globalwidth+shdx].rgbRed = 0x00;
                        shdframe[shdy*globalwidth+shdx].rgbReserved = shadowalpha;
                    }
                }
            }
        }
    }

    if(orgincluded)
    {
        for(long wi = globalwidth - 1 ; wi >=0; wi--)
        {
            for(long hi = globalheight - 1; hi >= 0; hi--)
            {
                if(tempframe->data[hi*globalwidth+wi].rgbReserved != 0)
                {
                    shdframe[hi*globalwidth+wi].rgbBlue = tempframe->data[hi*globalwidth+wi].rgbBlue;
                    shdframe[hi*globalwidth+wi].rgbGreen = tempframe->data[hi*globalwidth+wi].rgbGreen;
                    shdframe[hi*globalwidth+wi].rgbRed = tempframe->data[hi*globalwidth+wi].rgbRed;
                    shdframe[hi*globalwidth+wi].rgbReserved = tempframe->data[hi*globalwidth+wi].rgbReserved;
                }
            }
        }
    }

    return shdframe;
}
void MAPICDATA::MakeTransMask(unsigned char transmask)
{
    if(framecounts == 0) return;

    FRAMERGBA *tempframe;

    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        for(long pixi = 0; pixi < globalwidth*globalheight; pixi++)
        {
            if(tempframe->data[pixi].rgbReserved < transmask)
            {
                tempframe->data[pixi].rgbReserved = 0x00;
            }
        }
        tempframe = tempframe->next;
    }
}
void MAPICDATA::MakeTransMask(FILOCRGBQUAD *inoutdata, long width, long height, unsigned char transmask)
{
    for(long pixi = 0; pixi < width*height; pixi++)
    {
        if(inoutdata[pixi].rgbReserved < transmask)
        {
            inoutdata[pixi].rgbReserved = 0x00;
        }
    }
}
void MAPICDATA::AddBaseColor(FILOCRGBQUAD basecolor)
{
    if(framecounts == 0) return;

    FRAMERGBA *tempframe;
    FIBYTE alpha;

    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        for(long pixi = 0; pixi < globalwidth*globalheight; pixi++)
        {
            alpha = tempframe->data[pixi].rgbReserved;

            if(alpha == 0) continue;

            tempframe->data[pixi].rgbRed   = (FIBYTE)(((double)tempframe->data[pixi].rgbRed)*((double)alpha/(double)0xFF) +
                                             ((double)basecolor.rgbRed)*((double)(0xFF-alpha)/(double)0xFF));
            tempframe->data[pixi].rgbGreen = (FIBYTE)(((double)tempframe->data[pixi].rgbGreen)*((double)alpha/(double)0xFF) +
                                             ((double)basecolor.rgbGreen)*((double)(0xFF-alpha)/(double)0xFF));
            tempframe->data[pixi].rgbBlue  = (FIBYTE)(((double)tempframe->data[pixi].rgbBlue)*((double)alpha/(double)0xFF) +
                                             ((double)basecolor.rgbBlue)*((double)(0xFF-alpha)/(double)0xFF));
            tempframe->data[pixi].rgbReserved = 0xFF;
        }
        tempframe = tempframe->next;
    }
}
void MAPICDATA::AddAssiLine()
{
    if(framecounts == 0) return;

    FRAMERGBA *tempframe;
    long wpos = globalwidth/2;
    long hpos = globalheight/2;

    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        for(long hi = 0; hi < globalheight; hi++)
        {
            for(long wi = 0; wi < globalwidth; wi++)
            {
                if(wi == wpos || hi == hpos)
                {
                    tempframe->data[hi*globalwidth+wi].rgbRed = 0xFF;
                    tempframe->data[hi*globalwidth+wi].rgbGreen = 0x00;
                    tempframe->data[hi*globalwidth+wi].rgbBlue = 0x00;
                    tempframe->data[hi*globalwidth+wi].rgbReserved = 0xFF;
                }
            }
        }
        tempframe = tempframe->next;
    }
}
unsigned char* MAPICDATA::GetFrameRGB(unsigned long index, wxColor transcolor)
{
    if(index >= framecounts) return NULL;

    unsigned long bufpos;
    unsigned char *buffer, alpha;
    FRAMERGBA *temp;

    buffer = (unsigned char*)malloc((size_t)globalwidth*globalheight*3);
    if(!buffer) return NULL;

    temp = GetFrameData(index);

    bufpos = 0;
    for(long pixi = 0; pixi < globalwidth*globalheight; pixi++)
    {
        alpha = temp->data[pixi].rgbReserved;

        buffer[bufpos++] = (unsigned char)(((double)temp->data[pixi].rgbRed)*((double)alpha/(double)0xFF) +
                                           ((double)transcolor.Red())*((double)(0xFF-alpha)/(double)0xFF));
        buffer[bufpos++] = (unsigned char)(((double)temp->data[pixi].rgbGreen)*((double)alpha/(double)0xFF) +
                                           ((double)transcolor.Green())*((double)(0xFF-alpha)/(double)0xFF));
        buffer[bufpos++] = (unsigned char)(((double)temp->data[pixi].rgbBlue)*((double)alpha/(double)0xFF) +
                                           ((double)transcolor.Blue())*((double)(0xFF-alpha)/(double)0xFF));
    }

    return buffer;
}
unsigned char* MAPICDATA::MpcRunLenEncode(const unsigned char* maskline, const unsigned char* coliline, unsigned long *outsize, int codeType)
{
    if(maskline == NULL && coliline == NULL && outsize == NULL) return NULL;

    if(codeType == 0)
    {
        unsigned long buffer[globalwidth], samcot, bufpos, rsize;
        unsigned char *out = (unsigned char*)malloc(globalwidth*2);
        if(!out) return NULL;

        samcot = 1;
        bufpos = 0;
        for(long i = 1; i < globalwidth; i++)
        {
            if(maskline[i-1] == maskline[i] && samcot < 0x7F)
            {
                samcot++;
            }
            else
            {
                buffer[bufpos++] = samcot;
                samcot = 1;
            }
        }
        //last one
        if(samcot == 1) buffer[bufpos++] = 1;
        else buffer[bufpos++] = samcot;

        bufpos = 0;
        rsize = 0;
        for(long j = 0; j < globalwidth;)
        {
            if(maskline[j] == 0)
            {
                out[rsize] = (unsigned char)(buffer[bufpos] + 0x80);
                j += buffer[bufpos];
                rsize++;
                bufpos++;
            }
            else
            {
                out[rsize] = (unsigned char)(buffer[bufpos]);
                rsize++;
                for(unsigned char cnt = 0; cnt < buffer[bufpos]; cnt++)
                {
                    out[rsize] = coliline[j++];
                    rsize++;
                }
                bufpos++;
            }
        }
        *outsize = rsize;
        return out;
    }
    else
	{
		unsigned char *out = (unsigned char*)malloc(globalwidth*4);
        if(!out) return NULL;
        unsigned long rsize = 0;

        int bj;
        for(long j = 0; j < globalwidth;)
		{
			if(maskline[j] == 0)
			{
				bj = j;
				while(j < globalwidth && (j - bj < 0x7FFF) && maskline[++j] == 0);
				int o = (j - bj) + 0x8000;
				 out[rsize++] = (o & 0x00FF);
				 out[rsize++] = ((o & 0xFF00) >> 8);
			}
			else if(maskline[j] == 255)
			{
				bj = j;
				while(j < globalwidth && (j - bj < 0xFF) && maskline[++j] == 255);
				int o = j - bj;
				out[rsize++] = (unsigned char)o;
				out[rsize++] = 0x00;
				for(int oi = 0; oi < o; oi++)
				{
					out[rsize++] = coliline[bj + oi];
				}
			}
			else
			{
				bj = j;
				while(j < globalwidth && (j - bj < 0xFF) && maskline[++j] != 0 && maskline[j] != 255);
				int o = j - bj;
				out[rsize++] = (unsigned char)o;
				out[rsize++] = 0x40;
				for(int oi = 0; oi < o; oi++)
				{
					out[rsize++] = maskline[bj + oi];
					out[rsize++] = coliline[bj + oi];
				}
			}
		}
		*outsize = rsize;
        return out;
	}

}
unsigned char* MAPICDATA::AsfRunLenEncode(const unsigned char* maskline, const unsigned char* coliline, unsigned long *outsize)
{
    if(maskline == NULL && coliline == NULL && outsize == NULL) return NULL;

    unsigned long buffer[globalwidth], samcot, bufpos, rsize;
    unsigned char *out = (unsigned char*)malloc(globalwidth*3);
    if(!out) return NULL;

    samcot = 1;
    bufpos = 0;
    for(long i = 1; i < globalwidth; i++)
    {
        if(maskline[i-1] == maskline[i] && samcot < 0xFF)
        {
            samcot++;
        }
        else
        {
            buffer[bufpos++] = samcot;
            samcot = 1;
        }
    }
    //last one
    if(samcot == 1) buffer[bufpos++] = 1;
    else buffer[bufpos++] = samcot;

    bufpos = 0;
    rsize = 0;
    for(long j = 0; j < globalwidth;)
    {
        if(maskline[j] == 0)
        {
            out[rsize] = (unsigned char)(buffer[bufpos]);
            j += buffer[bufpos];
            rsize++;
            out[rsize] = 0;
            rsize++;
            bufpos++;
        }
        else
        {
            out[rsize] = (unsigned char)(buffer[bufpos]);
            rsize++;
            out[rsize] = maskline[j];
            rsize++;
            for(unsigned char cnt = 0; cnt < buffer[bufpos]; cnt++)
            {
                out[rsize] = coliline[j++];
                rsize++;
            }
            bufpos++;
        }
    }
    *outsize = rsize;
    return out;
}
unsigned char* MAPICDATA::ShdRunLenEncode(const unsigned char* maskline, unsigned long *outsize)
{
    if(maskline == NULL && outsize == NULL) return NULL;

    unsigned long buffer[globalwidth], samcot, bufpos, rsize;
    unsigned char *out = (unsigned char*)malloc(globalwidth*2);
    if(!out) return NULL;

    samcot = 1;
    bufpos = 0;
    for(long i = 1; i < globalwidth; i++)
    {
        if(maskline[i-1] == maskline[i] && samcot < 0x7F)
        {
            samcot++;
        }
        else
        {
            buffer[bufpos++] = samcot;
            samcot = 1;
        }
    }
    //last one
    if(samcot == 1) buffer[bufpos++] = 1;
    else buffer[bufpos++] = samcot;

    bufpos = 0;
    rsize = 0;
    for(long j = 0; j < globalwidth;)
    {
        if(maskline[j] == 0)
        {
            out[rsize] = (unsigned char)(buffer[bufpos] + 0x80);
            j += buffer[bufpos];
            rsize++;
            bufpos++;
        }
        else
        {
            out[rsize] = (unsigned char)(buffer[bufpos]);
            j += buffer[bufpos];
            rsize++;
            bufpos++;
        }
    }
    *outsize = rsize;
    return out;
}






