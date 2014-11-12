unsigned DLL_CALLCONV MyFI_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
{
    return (unsigned) fread(buffer, size, count, (FILE*)handle);
}
unsigned DLL_CALLCONV MyFI_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
{
    return (unsigned) fwrite(buffer, size, count, (FILE*)handle);
}
int DLL_CALLCONV MyFI_SeekProc(fi_handle handle, long offset, int origin)
{
    return (int) fseek((FILE*)handle, offset, origin);
}
long DLL_CALLCONV MyFI_TellProc(fi_handle handle)
{
    return (long) ftell((FILE*)handle);
}

    FreeImageIO io;
	io.read_proc = MyFI_ReadProc;
	io.write_proc = MyFI_WriteProc;
	io.seek_proc = MyFI_SeekProc;
	io.tell_proc = MyFI_TellProc;

	FILE* file = fopen("E:\\temp\\a.jpg", "rb");
	FILE* filemlt = fopen("E:\\temp\\multsave.gif", "wb");
	FIBITMAP* bitm = FreeImage_LoadFromHandle(FIF_JPEG, &io, (fi_handle)file, 0);
	//FIMULTIBITMAP* bitm = FreeImage_OpenMultiBitmap(FIF_GIF, "E:\\temp\\mlti.gif", TRUE, FALSE, TRUE, 0);
	fclose(file);
	if(bitm)
    {
        //FIBITMAP* bmp24bit = bitm;
        FIBITMAP* bmp24bit = FreeImage_ConvertTo24Bits(bitm);
        if(!bmp24bit) wxMessageBox(wxT("32bit convert filed!"));
        int width = FreeImage_GetWidth(bmp24bit);
        int height = FreeImage_GetHeight(bmp24bit);
        int scan_width = FreeImage_GetPitch(bmp24bit);
        BYTE* rawdata = (BYTE*)malloc(height*scan_width);
        wxMessageBox(wxString::Format(wxT("width:%d,height:%d,scan_width:%d"),width,height,scan_width));
        FreeImage_ConvertToRawBits(rawdata, bmp24bit, scan_width, 24,
                                   FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK,
                                   FI_RGBA_BLUE_MASK, true);


        wxImage timg(wxT("E:\\temp\\a.jpg"));
        unsigned char* timgdata = timg.GetData();
        int imgpos = 0;


        BYTE* imgdata = (BYTE*)malloc( height*width*3);
        /*
        RGBQUAD tempRGB;
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                FreeImage_GetPixelColor(bmp24bit, j, height-1-i, &tempRGB);
                imgdata[i*width*3 + j*3] = tempRGB.rgbRed;
                imgdata[i*width*3 + j*3 + 1] = tempRGB.rgbGreen;
                imgdata[i*width*3 + j*3 + 2] = tempRGB.rgbBlue;
                 //wxMessageBox(wxString::Format(wxT("%d %d %d "),tempRGB.rgbRed,tempRGB.rgbGreen,tempRGB.rgbBlue));
            }
        }
        */

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < 3*width; j+=3)
            {
                //BGR to RGB
                imgdata[i*width*3 + j]     = rawdata[i*scan_width + j + 2];
                imgdata[i*width*3 + j + 1] = rawdata[i*scan_width + j + 1];
                imgdata[i*width*3 + j + 2] = rawdata[i*scan_width + j];
            }
        }

        wxImage img(width, height, imgdata);
        //img.SaveFile(wxT("E:\\temp\\wximg.bmp"));

        //StaticBitmap_show->SetBitmap(wxBitmap(tempbmp.ConvertToImage()));
        StaticBitmap_show->SetBitmap(wxBitmap(img));
        this->Refresh();


        /*
        FIBITMAP* page1 = FreeImage_Load(FIF_BMP, "E:\\temp\\a.bmp", 0);
        if(!page1) wxMessageBox(wxT("page1 load failed!"));
        FIBITMAP* bmp24bbit = FreeImage_ConvertTo24Bits(page1);
        if(!bmp24bbit) wxMessageBox(wxT("24bit convert filed!"));
        FIBITMAP* bmp8bit = FreeImage_ColorQuantize(bmp24bbit, FIQ_NNQUANT);
        if(!bmp8bit) wxMessageBox(wxT("Quantize Failed"));
        FreeImage_AppendPage(bitm, bmp8bit);

        page1 = FreeImage_Load(FIF_JPEG, "E:\\temp\\a.jpg", 0);
        if(!page1) wxMessageBox(wxT("page1 load failed!"));
        bmp24bbit = FreeImage_ConvertTo24Bits(page1);
        if(!bmp24bbit) wxMessageBox(wxT("24bit convert filed!"));
        bmp8bit = FreeImage_ColorQuantize(bmp24bbit, FIQ_NNQUANT);
        if(!bmp8bit) wxMessageBox(wxT("Quantize Failed"));
        FreeImage_AppendPage(bitm, bmp8bit);

        bool res =
            //FreeImage_CloseMultiBitmap(bitm,0);
            FreeImage_SaveMultiBitmapToHandle(FIF_GIF, bitm, &io, (fi_handle)filemlt, 0);
        if(!res) wxMessageBox(wxT("save failed!"));



        FILE* file2 = fopen("E:\\temp\\save.gif", "wb");
        FIBITMAP* bmp32bit = FreeImage_ConvertTo24Bits(bitm);
        if(!bmp32bit) wxMessageBox(wxT("24bit convert filed!"));
        FIBITMAP* bmp24bbit = FreeImage_ConvertTo24Bits(bitm);
        if(!bmp24bbit) wxMessageBox(wxT("24bit convert filed!"));
        FIBITMAP* bmp8bit = FreeImage_ColorQuantize(bmp24bbit, FIQ_NNQUANT);
        if(!bmp8bit) wxMessageBox(wxT("Quantize Failed"));
        int width = FreeImage_GetWidth(bmp8bit);
        int height = FreeImage_GetHeight(bmp8bit);
        int scan_width = FreeImage_GetPitch(bmp8bit);
        BYTE* rawdata = (BYTE*)malloc(height*scan_width);
        wxMessageBox(wxString::Format(wxT("width:%d,height:%d,scan_width:%d"),width,height,scan_width));
        FreeImage_ConvertToRawBits(rawdata, bmp8bit, scan_width, 8,
                                   0xFF000000, 0xFF0000,
                                   0xFF, true);
        FIBITMAP* bmpfrraw = FreeImage_ConvertFromRawBits(rawdata, width, height,
                                                          scan_width, 8, 0xFF00000, 0xFF000,
                                                          0xFF00, true);
        if(!bmpfrraw) wxMessageBox(wxT("bmpfrraw Failed"));
        FreeImage_Save(FIF_BMP, bmpfrraw, "E:\\temp\\rawtobmp.bmp", 0);
        FreeImage_Save(FIF_BMP, bmp8bit, "E:\\temp\\convertobmp8.bmp", 0);
/*
        BYTE value[4];
         for(int i = 0; i < height; )
        {
            FreeImage_GetPixelIndex(bmp8bit, i, height-1, value);
            FreeImage_GetPixelIndex(bmp8bit, i+1, height-1, value+1);
            FreeImage_GetPixelIndex(bmp8bit, i+2, height-1, value+2);
            FreeImage_GetPixelIndex(bmp8bit, i+3, height-1, value+3);
            wxMessageBox(wxString::Format(wxT("%d %d %d %d"),value[0],value[1],value[2],value[3]));
            i+=4;
        }


        int indexc =0;
        for(int i = 0; i < height; i)
        {
             wxMessageBox(wxString::Format(wxT("%d %d %d %d"),
                                           rawdata[(indexc)],   rawdata[(indexc+1)],
                                           rawdata[(indexc+2)], rawdata[(indexc+3)]));
            indexc += 4;
        }
/*

        if(!bmpfrraw) wxMessageBox(wxT("convert from raw filed!"));
        RGBQUAD rgb;
        for(int i = 0; i < height; i++)
        {
            FreeImage_GetPixelColor(bmpfrraw, i, height-1, &rgb);
            wxMessageBox(wxString::Format(wxT("%d %d %d %d"),rgb.rgbRed,rgb.rgbGreen,rgb.rgbBlue,
                                          rgb.rgbReserved));
        }

       // FIBITMAP* bmp8bit = FreeImage_ColorQuantize(bitm, FIQ_WUQUANT);
        //if(!bmp8bit) wxMessageBox(wxT("Quantize Failed"));
        if(FreeImage_SaveToHandle(FIF_GIF,bmp8bit, &io, (fi_handle)file2, 0))
        {
            wxMessageBox(wxT("Saved!"));
        }
        else
        {
            wxMessageBox(wxT("Saved Filed!"));
        }
        fclose(file2);
        FreeImage_Unload(bitm);
        //wxMessageBox(wxT("Loaded!"));
        */
    }
    else
    {
        wxMessageBox(wxT("Read Failed!"));
    }

	
	

	
struct FI_IO_Handle
{
    long pos;
    unsigned long size;
    BYTE *stream;
};
	unsigned DLL_CALLCONV MyFI_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
{
    FI_IO_Handle *ioh = (FI_IO_Handle*)handle;
    long pos = ioh->pos;
    unsigned long str_size = ioh->size;
    BYTE *data = ioh->stream;
    unsigned readc;
    if(size < count) readc = size;
    else readc = count;
    if((pos+readc) > str_size) readc = (str_size - pos);
    memcpy(buffer, (void*)data, (size_t)readc);
    ioh->pos += (long)readc;
    return readc;
}
unsigned DLL_CALLCONV MyFI_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
{
    //Load not Neaded
}
int DLL_CALLCONV MyFI_SeekProc(fi_handle handle, long offset, int origin)
{
    FI_IO_Handle *ioh = (FI_IO_Handle*)handle;
    long pos = ioh->pos, newpos;
    unsigned long str_size = ioh->size;
    switch(origin)
    {
    case SEEK_SET:
        if(offset >= str_size) return -1;
        ioh->pos = offset;
        return 0;
        break;
    case SEEK_CUR:
        newpos = pos+offset;
        if(newpos < 0 || newpos >= str_size) return -1;
        ioh->pos = newpos;
        return 0;
        break;
    case SEEK_END:
        newpos = (long)str_size - 1 - offset;
        if(newpos < 0 || newpos >= str_size) return -1;
        ioh->pos = newpos;
        return 0;
        break;
    default:
        return -1;
    }
}
long DLL_CALLCONV MyFI_TellProc(fi_handle handle)
{
    FI_IO_Handle *ioh = (FI_IO_Handle*)handle;
    long pos = ioh->pos;
    return pos;
}











#include "MpctoGif.hpp"
#include "MpcDecode.hpp"
//#include "FreeImage_IO_CallBack.hpp"

#include "FreeImage.h"

#include "wx/log.h"
#include "wx/stream.h"
#include "wx/mstream.h"
#include <fstream>

CovMpctoGif::CovMpctoGif(const wxString inMpcFilePath, const wxString outGifFilePath)
{
    inFilePath = inMpcFilePath;
    outFilePath = outGifFilePath;
}

bool CovMpctoGif::Save()
{
    if(inFilePath.IsEmpty() || outFilePath.IsEmpty()) return false;
    else
    {
        unsigned long framessum,strsize;
        unsigned long width, height;
        wxImage tempimg;
       // BYTE* rawdata;
        unsigned char* imgdata;
        //wxMemoryOutputStream outstr;
        // wxMemoryInputStream instr;
        BYTE* strdata = NULL;
        FILE *flh;
        FI_IO_Handle *iohandle;
        FreeImageIO io;
        FIBITMAP *fibmp, *fiquat;
        FIMULTIBITMAP* gifimg =
            FreeImage_OpenMultiBitmap(FIF_GIF, outFilePath.char_str(), TRUE,
                                      FALSE, TRUE, 0);
        io.read_proc = MyFI_ReadProc;
        io.write_proc = NULL;
        io.seek_proc = MyFI_SeekProc;
        io.tell_proc = MyFI_TellProc;

        if(!gifimg)
        {
            wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
            return false;
        }

        MpcDecode decode;
        if(!decode.ReadMpcFile(inFilePath))
        {
            wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
            return false;
        }

        framessum = decode.GetFramesCounts();

        for(unsigned long i = 0; i < framessum; i++)
        {
            //tempimg = decode.GetFrameImage(i);
            strdata = decode.GetDecodedFrameData(i, &width, &height);
            if(!strdata)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }
            wxLogDebug(wxT("Frame : %d"), i);

            //wxMemoryOutputStream outstr;
            //outstr = new wxMemoryOutputStream();
           // tempimg.SaveFile(outstr, wxBITMAP_TYPE_BMP);
            //wxMemoryInputStream instr(outstr);
           // strsize = instr.GetSize();
           // strdata = (BYTE*)malloc(strsize);
            if(strdata == NULL)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }
            if(instr.Read((void*)strdata, strsize).LastRead() != strsize)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }
            iohandle = new FI_IO_Handle;
            iohandle->pos = 0;
            iohandle->size = strsize;
            iohandle->stream = strdata;
            //std::ofstream dumpf("E:\\temp\\dump.txt", std::ios_base::binary|std::ios_base::out);
           // dumpf.write((char*)strdata, strsize);
            //flh = tmpfile();
            //fwrite((void*)strdata,strsize,strsize,flh);
           // fseek(flh, 0, SEEK_SET);
            // char tc;
            //fread((void*)&tc,1,1,flh);
            //wxLogDebug(wxT("char: %X"), tc);
            wxLogDebug(wxT("Stream size: %ld"), strsize);
            //iohandle = new FI_IO_Handle;
            //iohandle->pos = 0;
            //iohandle->size = (unsigned long)strsize;
            // iohandle->stream = strdata;

            fibmp = FreeImage_LoadFromHandle(FIF_BMP, &io, (fi_handle)iohandle, 0);
            free(strdata);
            //fclose(flh);
            delete iohandle;
            iohandle = NULL;

            // flh = fopen("E:\\temp\\dkjlasdjfalsdf.png", "rb");
            // fibmp = FreeImage_LoadFromHandle(FIF_PNG, &io, (fi_handle)flh, 0);
            //fibmp = FreeImage_Load(FIF_PNG, "E:\\temp\\dkjlasdjfalsdf.png", 0);
            if(!fibmp)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }
            fiquat = FreeImage_ColorQuantize(fibmp, FIQ_NNQUANT);
            FreeImage_Unload(fibmp);
            fibmp = NULL;
            if(!fiquat)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }

            /*
            width = tempimg.GetHeight();
            height = tempimg.GetHeight();
            rawdata = (BYTE*)malloc(width*height*3);
            if(rawdata == NULL)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }
            imgdata = tempimg.GetData();
            for(int j = 0; j < width*height; j++)
            {
                rawdata[j*3]     = (BYTE)imgdata[j*3 + 2];
                rawdata[j*3 + 1] = (BYTE)imgdata[j*3 + 1];
                rawdata[j*3 + 2] = (BYTE)imgdata[j*3];
            }

            //((24*width + 31)/32)*4
            fibmp = FreeImage_ConvertFromRawBits(rawdata, width, height, width*3,
                                                 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK,
                                                 FI_RGBA_BLUE_MASK, TRUE);
            if(!fibmp)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }

            if( i == 0 )
            {
                FreeImage_Save(FIF_BMP, fibmp, "E:\\temp\\page1.bmp", 0);
            }

            fiquat = FreeImage_ColorQuantize(fibmp, FIQ_NNQUANT);
            FreeImage_Unload(fibmp);
            fibmp = NULL;
            if(!fiquat)
            {
                wxLogDebug(wxT("Failed at - %s: %d"), __FILE__, __LINE__);
                return false;
            }

            if( i == 0 )
            {
                FreeImage_Save(FIF_GIF, fiquat, "E:\\temp\\page1.gif", 0);
            }
            */

            FreeImage_AppendPage(gifimg, fiquat);
            FreeImage_Unload(fiquat);
            fiquat = NULL;
        }
        wxMessageBox(wxT("Gif constructing ok"));
        FreeImage_CloseMultiBitmap(gifimg, 0);
        return true;
    }
}


         translen = 0;
            colorlen = 0;
            if(line[0] == 0x00)
            {
                ispixtran = true;
                translen++;
            }
            else
            {
                ispixtran = false;
                colorlen++;
            }
            for( wi = 1; wi < globalwidth; wi++)
            {
                if(translen == 0x80)
                {
                    translen = 0xFF;
                    outfile.write((char*)&translen, 1);

                    encodelen++;

                    translen = 1;
                }
                else if(colorlen == 0x80)
                {
                    colorlen = 0x7F;
                    outfile.write((char*)&colorlen, 1);

                    for(unsigned char ci = 0; ci < colorlen; ci++)
                    {
                        outfile.write((char*)(line + (wi-1)*2 - (colorlen -ci)*2 + 1), 1);
                    }

                    encodelen += (unsigned long)(colorlen+1);

                    colorlen = 1;
                }

                if(wi == (globalwidth -1))//data end
                {
                    if(line[wi*2] == 0x00 && ispixtran)
                    {
                        translen++;

                        temp[0] = translen + 0x80;
                        outfile.write((char*)&temp, 1);

                        encodelen++;

                        //loop ended
                    }
                    else if(line[wi*2] == 0x00 && !ispixtran)
                    {
                        ispixtran = true;
                        translen = 1;

                        outfile.write((char*)&colorlen, 1);
                        for(unsigned char ci = 0; ci < colorlen; ci++)
                        {
                            outfile.write((char*)(line + wi*2 - (colorlen -ci)*2 + 1), 1);
                        }

                        encodelen += (unsigned long)(colorlen+1);

                        temp[0] = translen + 0x80;
                        outfile.write((char*)&temp, 1);
                        encodelen++;

                        //loop ended
                    }
                    else if(line[wi*2] != 0x00 && ispixtran)
                    {
                        ispixtran = false;
                        colorlen = 1;

                        temp[0] = translen + 0x80;
                        outfile.write((char*)&temp, 1);

                        encodelen++;

                        outfile.write((char*)&colorlen, 1);
                        for(unsigned char ci = 0; ci < colorlen; ci++)
                        {
                            outfile.write((char*)(line + (wi+1)*2 - (colorlen -ci)*2 + 1), 1);
                        }

                        encodelen += (unsigned long)(colorlen+1);

                        //loop ended
                    }
                    else if(line[wi*2] != 0x00 && !ispixtran)
                    {
                        colorlen++;

                        outfile.write((char*)&colorlen, 1);
                        for(unsigned char ci = 0; ci < colorlen; ci++)
                        {
                            outfile.write((char*)(line + (wi+1)*2 - (colorlen -ci)*2 + 1), 1);
                        }

                        encodelen += (unsigned long)(colorlen+1);

                        //loop ended
                    }
                }
                else if(line[wi*2] == 0x00 && ispixtran)
                {
                    translen++;
                }
                else if(line[wi*2] == 0x00 && !ispixtran)
                {
                    ispixtran = true;
                    translen = 1;

                    outfile.write((char*)&colorlen, 1);
                    for(unsigned char ci = 0; ci < colorlen; ci++)
                    {
                        outfile.write((char*)(line + wi*2 - (colorlen -ci)*2 + 1), 1);
                    }

                    encodelen += (unsigned long)(colorlen+1);

                    colorlen = 0;
                }
                else if(line[wi*2] != 0x00 && ispixtran)
                {
                    ispixtran = false;
                    colorlen = 1;

                    temp[0] = translen + 0x80;
                    outfile.write((char*)&temp, 1);

                    encodelen++;

                    translen = 0x00;
                }
                else if(line[wi*2] != 0x00 && !ispixtran)
                {
                    colorlen++;
                }
            }