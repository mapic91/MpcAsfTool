#include "wx/log.h"

#include <cstring>
#include <cstdlib>
#include <fstream>

#include "GifData.hpp"

using namespace std;

GifData::GifData(int width, int height, int interval, bool istransparent)
{
    Init();
    Width = width;
    Height = height;
    Interval = (interval+9)/10;
    isTrans = istransparent;
}
GifData::~GifData()
{
    if(FirstPage != NULL)
    {
        GifFrame *cur, *next;
        cur = FirstPage;
        next = cur->next;
        for(; cur != NULL;)
        {
            free(cur->data);
            delete cur;
            cur = next;
            next = cur->next;
        }
    }
}
void GifData::Init()
{
    Width = 0;
    Height = 0;
    Interval = 10;
    isTrans = false;
    FrameCounts = 0;
    FirstPage = NULL;
    LastPage = NULL;
    memset((void*)Palette, 0, sizeof(FILOCRGBQUAD)*256);
}
void GifData::AddPage(GifFrameData* page)
{
    if(page == NULL) return;
    if(FrameCounts == 0)
    {
        FirstPage = new GifFrame();
        FirstPage->data = page->data;
        FirstPage->datasize = page->datasize;
        FirstPage->next = NULL;
        LastPage = FirstPage;
    }
    else
    {
        LastPage->next = new GifFrame();
        LastPage->next->data = page->data;
        LastPage->next->datasize = page->datasize;
        LastPage->next->next = NULL;
        LastPage =  LastPage->next;
    }
    FrameCounts++;
}

bool GifData::Save()
{
    return false;//noncomplete,to be continue...

    if(OutPath.IsEmpty() || FrameCounts == 0) return false;

    unsigned char temp[20];
    ofstream outfile(OutPath.char_str(), ios_base::binary|ios_base::out);
    if(!outfile.is_open()) return false;

    outfile.write("GIF89a", 6);
    temp[0] = (unsigned char)((Width&0xFF));
    temp[1] = (unsigned char)((Width&0xFF00) >> 8);
    temp[2] = (unsigned char)((Height&0xFF));
    temp[3] = (unsigned char)((Height&0xFF00) >> 8);
    outfile.write((char*)temp, 4);

    temp[0] = 0;
    temp[0] |= 0x80;//globle palette
    temp[0] |= 0x70;//pixel size
    temp[0] |= 0x7; //globle palette size
    temp[1] = 0xFF; //background color index
    temp[2] = 0; //pixel aspect ratio
    outfile.write((char*)temp, 3);

    for(int pltidx = 0; pltidx < 256; pltidx++)
    {
        temp[0] = Palette[pltidx].rgbRed;
        temp[1] = Palette[pltidx].rgbGreen;
        temp[3] = Palette[pltidx].rgbBlue;
        outfile.write((char*)temp, 3);
    }
    //animate control
    temp[0] = 0x21;
    temp[1] = 0xFF;
    temp[2] = 0x0B;
    temp[3] = 0x4E;
    temp[4] = 0x45;
    temp[5] = 0x54;
    temp[6] = 0x53;
    temp[7] = 0x43;
    temp[8] = 0x41;
    temp[9] = 0x50;
    temp[10]= 0x45;
    temp[11]= 0x32;
    temp[12]= 0x2E;
    temp[13]= 0x30;
    temp[14]= 0x03;
    temp[15]= 0x01;
    temp[16]= 0x00;
    temp[17]= 0x00;
    temp[18]=0x00;
    outfile.write((char*)temp, 19);

    unsigned char grapctl[8];
    grapctl[0] = 0x21; //ExtensionIntroducer
    grapctl[1] = 0xF9; //GraphicControlLabel
    grapctl[2] = 0x04; //Block Size
    grapctl[3] = 0x00; //Flags
    grapctl[3]|= 0x08; //DisposalMethod
    grapctl[3]|= 0x01; //Transparent Flag
    grapctl[4] = (unsigned char)((Interval&0xFF));       //  Delay Time
    grapctl[5] = (unsigned char)((Interval&0xFF00) >> 8);//  Delay Time
    grapctl[6] = 0xFF; //TransparetnColorIndex
    grapctl[7] = 0x00; //BlockTerminator
    unsigned char imghed[10];
    imghed[0] = 0x2C; //ImageSeperator
    imghed[1] = 0x00; //ImageLeftPosition
    imghed[2] = 0x00; //ImageLeftPosition
    imghed[3] = 0x00; //ImageTopPosition
    imghed[4] = 0x00; //ImageTopPosition
    imghed[5] = (unsigned char)((Width&0xFF));        //ImageWidth
    imghed[6] = (unsigned char)((Width&0xFF00) >> 8); //ImageWidth
    imghed[7] = (unsigned char)((Height&0xFF));        //ImageHeight
    imghed[8] = (unsigned char)((Height&0xFF00) >> 8); //ImageHeight
    imghed[9] = 0x00; //Falg

    for(int frmidx = 0; frmidx < FrameCounts; frmidx++)
    {
        outfile.write((char*)grapctl, 8);
        outfile.write((char*)imghed, 10);
        //to be continue...
    }
}

FIMEMORY *GifData::FIPaletteLoctoGlb(FIMEMORY *instream)
{
    if(instream == NULL) return NULL;

    FIMEMORY *outstream = FreeImage_OpenMemory(NULL, 0);
    if(outstream == NULL) return NULL;

    unsigned char temp[256], gbplt[256*3];

    FreeImage_SeekMemory(instream, 0, SEEK_SET);
    FreeImage_ReadMemory(temp, 13, 1, instream);
    if(memcmp(temp, "GIF89a", 6) != 0) return NULL;
    if((temp[0x0A] & 0x80) != 0 ) return NULL;

    FreeImage_WriteMemory("GIF89a", 6, 1, outstream);
    temp[0] = (unsigned char)((Width&0xFF));
    temp[1] = (unsigned char)((Width&0xFF00) >> 8);
    temp[2] = (unsigned char)((Height&0xFF));
    temp[3] = (unsigned char)((Height&0xFF00) >> 8);
    FreeImage_WriteMemory(temp, 4, 1, outstream);

    temp[0] = 0;
    temp[0] |= 0x80;//globle palette
    temp[0] |= 0x70;//pixel size
    temp[0] |= 0x7; //globle palette size
    temp[1] = 0xFF; //background color index
    temp[2] = 0; //pixel aspect ratio
    FreeImage_WriteMemory(temp, 3, 1, outstream);

    FreeImage_SeekMemory(instream, 0xD, SEEK_SET);

    FreeImage_ReadMemory(temp, 2, 1, instream);
    for(; temp[0] != 0x2C ;)
    {
        if(temp[0] == 0x21)
        {
            if(temp[1] == 0xFF)
            {
                FreeImage_SeekMemory(instream, 12, SEEK_CUR);//application head
                FreeImage_ReadMemory(temp, 1, 1, instream);// data size
                FreeImage_SeekMemory(instream, temp[0]+1, SEEK_CUR);
            }
            else if(temp[1] == 0xF9)
            {
                FreeImage_SeekMemory(instream, 6, SEEK_CUR);//control head
            }
        }

        FreeImage_ReadMemory(temp, 2, 1, instream);
    }
    FreeImage_SeekMemory(instream, 8, SEEK_CUR);//img head
    FreeImage_ReadMemory(gbplt, 256*3, 1, instream);//Local palette content

    FreeImage_WriteMemory(gbplt, 256*3, 1, outstream);//Global palette


    unsigned char grapctl[8];
    grapctl[0] = 0x21; //ExtensionIntroducer
    grapctl[1] = 0xF9; //GraphicControlLabel
    grapctl[2] = 0x04; //Block Size
    grapctl[3] = 0x00; //Flags
    grapctl[3]|= 0x08; //DisposalMethod
    grapctl[3]|= 0x01; //Transparent Flag
    grapctl[4] = (unsigned char)((Interval&0xFF));       //  Delay Time
    grapctl[5] = (unsigned char)((Interval&0xFF00) >> 8);//  Delay Time
    grapctl[6] = 0xFF; //TransparetnColorIndex
    grapctl[7] = 0x00; //BlockTerminator
    unsigned char imghed[10];
    imghed[0] = 0x2C; //ImageSeperator
    imghed[1] = 0x00; //ImageLeftPosition
    imghed[2] = 0x00; //ImageLeftPosition
    imghed[3] = 0x00; //ImageTopPosition
    imghed[4] = 0x00; //ImageTopPosition
    imghed[5] = (unsigned char)((Width&0xFF));        //ImageWidth
    imghed[6] = (unsigned char)((Width&0xFF00) >> 8); //ImageWidth
    imghed[7] = (unsigned char)((Height&0xFF));        //ImageHeight
    imghed[8] = (unsigned char)((Height&0xFF00) >> 8); //ImageHeight
    imghed[9] = 0x00; //Falg

    FreeImage_SeekMemory(instream, 0xD, SEEK_SET);
    FreeImage_ReadMemory(temp, 1, 1, instream);
    for(; temp[0] != 0x3B;) //0x3B indicate file end
    {
        FreeImage_ReadMemory(temp+1, 1, 1, instream);
        if(temp[0] == 0x21)
        {
            if(temp[1] == 0xFF) // Application ext,control animation
            {
                //Skip
                FreeImage_SeekMemory(instream, 12, SEEK_CUR);//application head
                FreeImage_ReadMemory(temp, 1, 1, instream);// data size
                FreeImage_SeekMemory(instream, temp[0]+1, SEEK_CUR);

                //Save predefined setting
                temp[0] = 0x21;
                temp[1] = 0xFF;
                temp[2] = 0x0B;
                temp[3] = 0x4E;
                temp[4] = 0x45;
                temp[5] = 0x54;
                temp[6] = 0x53;
                temp[7] = 0x43;
                temp[8] = 0x41;
                temp[9] = 0x50;
                temp[10]= 0x45;
                temp[11]= 0x32;
                temp[12]= 0x2E;
                temp[13]= 0x30;
                temp[14]= 0x03;
                temp[15]= 0x01;
                temp[16]= 0x00;
                temp[17]= 0x00;
                temp[18]= 0x00;
                FreeImage_WriteMemory(temp, 19, 1, outstream);
            }
            else if(temp[1] == 0xF9)//control ext
            {
                FreeImage_SeekMemory(instream, 6, SEEK_CUR);//control head
                FreeImage_WriteMemory(grapctl, 8, 1, outstream);

            }
        }
        else // 0x2C
        {
            FreeImage_WriteMemory(imghed, 10, 1, outstream);
            FreeImage_SeekMemory(instream, 8+256*3, SEEK_CUR);
            FreeImage_ReadMemory(temp, 1, 1, instream); //LZWMinimumCodeSize
            FreeImage_WriteMemory(temp, 1, 1, outstream);

            FreeImage_ReadMemory(temp, 1, 1, instream);
            for(;temp[0] != 0; )//Image data
            {
                FreeImage_ReadMemory(temp+1, temp[0], 1, instream);
                FreeImage_WriteMemory(temp, temp[0]+1, 1, outstream);

                FreeImage_ReadMemory(temp, 1, 1, instream);
            }
            FreeImage_WriteMemory(temp, 1, 1, outstream);
        }

        FreeImage_ReadMemory(temp, 1, 1, instream);
    }
    temp[0] = 0x3B;//file end
    FreeImage_WriteMemory(temp, 1, 1, outstream);
    return outstream;

}
bool GifData::FilePaletteLoctoGlb(const wxString inpath, long Interval)
{
    FIMULTIBITMAP *giff;
    FIBITMAP  *page;
    unsigned width,height,filesize;
    FIMEMORY *gifmem, *glbpal;
    BOOL res;
    BYTE *buffer;
    FILOCDWORD bufsize;
    wxString outpath = inpath;
    giff = FreeImage_OpenMultiBitmap(FIF_GIF, inpath.char_str(), FALSE, TRUE);
    if(!giff)
    {
        return false;
    }

    page = FreeImage_LockPage(giff, 0);
    width = FreeImage_GetWidth(page);
    height = FreeImage_GetHeight(page);
    FreeImage_UnlockPage(giff, page, FALSE);
    FreeImage_CloseMultiBitmap(giff, 0); giff = NULL;

    long intv = Interval;
    //wxString strintv;
    //strintv = TextCtrl_interval->GetLineText(0);
    //if(!strintv.ToLong(&intv))return;
    GifData data((int)width, (int)height, intv);

    std::ifstream ingiffile(inpath.char_str(), std::ios_base::binary|std::ios_base::in);
    if(!ingiffile.is_open()) return false;
    ingiffile.seekg(0, std::ios_base::end);
    filesize = (unsigned)ingiffile.tellg()+1;
    ingiffile.seekg(0, std::ios_base::beg);

    buffer = (BYTE*)malloc((size_t)filesize);
    if(!buffer) return false;
    ingiffile.read((char*)buffer, filesize);
    if(ingiffile.bad()) return false;
    ingiffile.close();

    gifmem = FreeImage_OpenMemory(buffer, filesize);
    if(!gifmem)
    {
        return false;
    }
    glbpal = data.FIPaletteLoctoGlb(gifmem);
    FreeImage_CloseMemory(gifmem); gifmem = NULL;
    free(buffer);buffer = NULL;
    if(!glbpal)
    {
        return false;
    }
    res = FreeImage_AcquireMemory(glbpal, &buffer, &bufsize);
    if(!res)
    {
        FreeImage_CloseMemory(glbpal);
        return false;
    }

    std::ofstream outfile(outpath.char_str(), std::ios_base::binary|std::ios_base::out);
    if(!outfile.is_open())
    {
        FreeImage_CloseMemory(glbpal);
        return false;
    }
    outfile.write((char*)buffer, bufsize);

    FreeImage_CloseMemory(glbpal);
    return true;
}
