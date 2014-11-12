#include <fstream>

#include "MAPICDATA.hpp"

#include "wx/msgdlg.h"
#include "wx/log.h"
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
void MAPICDATA::AddFrame(FILOCRGBQUAD *frame, long width, long height)
{
    isquantized = false;
    if(firstframe == NULL)
    {
        firstframe = new FRAMERGBA();
        firstframe->width = width;
        firstframe->height = height;
        firstframe->data = frame;
        firstframe->next = NULL;
        currentframe = firstframe;
    }
    else
    {
        currentframe->next = new FRAMERGBA();
        currentframe = currentframe->next;
        currentframe->width = width;
        currentframe->height = height;
        currentframe->data = frame;
        currentframe->next = NULL;
    }
    framecounts++;
}
BYTE* MAPICDATA::GetPixIndexData()
{
    if(isquantized) return pixindex;
    else return NULL;
}
bool MAPICDATA::Quantize(const int palettesize)
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
    BYTE *sumdata,red,green,blue,alpha;
    FIBITMAP *sumsample, *bmp24, *bmp8;
    FILOCRGBQUAD *plt;

    sumdata = (BYTE*)malloc(sumsize);
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
                sumdata[sumidx++] = (BYTE)(((double)blue)*((double)alpha/(double)0xFF) +
                                           ((double)0xFF)*((double)(0xFF-alpha)/(double)0xFF));
                sumdata[sumidx++] = (BYTE)(((double)green)*((double)alpha/(double)0xFF) +
                                           ((double)0xFF)*((double)(0xFF-alpha)/(double)0xFF));
                sumdata[sumidx++] = (BYTE)(((double)red)*((double)alpha/(double)0xFF) +
                                           ((double)0xFF)*((double)(0xFF-alpha)/(double)0xFF));
                sumdata[sumidx++] = 0xFF;
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

    pixindex = (BYTE*)malloc(quatwidth);
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
    BYTE *buffer;
    long bufsize = globalwidth*globalheight*4;
    unsigned long pixcout = globalwidth*globalheight, bufidx;
    FIBITMAP *png;

    buffer = (BYTE*)malloc((size_t)bufsize);
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
        if(!FreeImage_SaveU(FIF_PNG, png, path + wxString::Format(wxT("-%03ld.png"), fridx+1)))
        {
            free(buffer);
            return false;
        }
        temprgba = temprgba->next;
    }
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
    BYTE trasidx = 0xFF;
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
bool MAPICDATA::SaveToMpc(const wxString path, long direction, long interval, long bottom)
{
    if(framecounts == 0) return false;

    if(!Quantize(256)) return false;

    unsigned long databeg, framedatasum, encodelen, pipos;
    unsigned char translen, colorlen;
    bool ispixtran;
    FRAMERGBA *tempframe;

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
    outfile.write(nullv, 32);//null
    for(int plti = 0; plti < 256; plti++)//palette
    {
        outfile.write((char*)(&palette[plti].rgbBlue), 1);
        outfile.write((char*)(&palette[plti].rgbGreen), 1);
        outfile.write((char*)(&palette[plti].rgbRed), 1);
        outfile.write((char*)(&palette[plti].rgbReserved), 1);
    }

    databeg = (unsigned long)outfile.tellp();//frame 0 data offset

    outfile.write(nullv, 4);

    pipos = 0;
    framedatasum = 0;
    tempframe = firstframe;
    for(unsigned long frmi = 0; frmi < framecounts; frmi++)
    {
        translen = 0;
        colorlen = 0;
        encodelen = 20;//frame data head length

        outfile.seekp(databeg+4*frmi, ios_base::beg);
        temp[0] = (unsigned char)(framedatasum & 0xFF);
        temp[1] = (unsigned char)((framedatasum & 0xFF00) >> 8);
        temp[2] = (unsigned char)((framedatasum & 0xFF0000) >> 16);
        temp[3] = (unsigned char)((framedatasum & 0xFF000000) >> 24);
        outfile.write((char*)temp, 4);// frame data offset

        outfile.seekp(databeg+4*framecounts+framedatasum, ios_base::beg);//frame data

        if(tempframe->data[0].rgbReserved == 0x00)
        {
            ispixtran = true;
            translen++;
        }
        else
        {
            ispixtran = false;
            colorlen++;
        }
        for(long dati = 1; dati < globalwidth*globalheight; dati++)
        {
            if(translen == 0x7F)
            {
                translen = 0xFE;
                outfile.write((char*)&translen, 1);

                encodelen++;

                translen = 1;
            }
            else if(colorlen == 0x7F)
            {
                colorlen = 0x7E;
                outfile.write((char*)&colorlen, 1);
                outfile.write((char*)(pixindex+pipos), colorlen);

                encodelen += (unsigned long)(colorlen+1);
                pipos += (unsigned long)colorlen;

                colorlen = 1;
            }
            else if(dati == (globalwidth*globalheight-1))//data end
            {
                if(tempframe->data[dati].rgbReserved == 0x00 && ispixtran)
                {
                    translen++;

                    outfile.write((char*)&translen, 1);

                    encodelen++;

                    //loop ended
                }
                else if(tempframe->data[dati].rgbReserved == 0x00 && !ispixtran)
                {
                    ispixtran = true;
                    translen = 1;

                    outfile.write((char*)&colorlen, 1);
                    outfile.write((char*)(pixindex+pipos), colorlen);

                    encodelen += (unsigned long)(colorlen+1);
                    pipos += (unsigned long)colorlen;

                    outfile.write((char*)&translen, 1);
                    encodelen++;

                    //loop ended
                }
                else if(tempframe->data[dati].rgbReserved != 0x00 && ispixtran)
                {
                    ispixtran = false;
                    colorlen = 1;

                    outfile.write((char*)&translen, 1);

                    encodelen++;

                    outfile.write((char*)&colorlen, 1);
                    outfile.write((char*)(pixindex+pipos), colorlen);

                    encodelen += (unsigned long)(colorlen+1);
                    pipos += (unsigned long)colorlen;

                    //loop ended
                }
                else if(tempframe->data[dati].rgbReserved != 0x00 && !ispixtran)
                {
                    colorlen++;

                    outfile.write((char*)&colorlen, 1);
                    outfile.write((char*)(pixindex+pipos), colorlen);

                    encodelen += (unsigned long)(colorlen+1);
                    pipos += (unsigned long)colorlen;

                    //loop ended
                }
            }
            else if(tempframe->data[dati].rgbReserved == 0x00 && ispixtran)
            {
                translen++;
            }
            else if(tempframe->data[dati].rgbReserved == 0x00 && !ispixtran)
            {
                ispixtran = true;
                translen = 1;

                outfile.write((char*)&colorlen, 1);
                outfile.write((char*)(pixindex+pipos), colorlen);

                encodelen += (unsigned long)(colorlen+1);
                pipos += (unsigned long)colorlen;

                colorlen = 0;
            }
            else if(tempframe->data[dati].rgbReserved != 0x00 && ispixtran)
            {
                ispixtran = false;
                colorlen = 1;

                outfile.write((char*)&translen, 1);

                encodelen++;

                translen = 0x00;
            }
            else if(tempframe->data[dati].rgbReserved != 0x00 && !ispixtran)
            {
                colorlen++;
            }
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

    return true;
}
bool MAPICDATA::SaveToAsf(const wxString path)
{
    if(framecounts == 0) return false;

}
