#include "FreeImage_IO_CallBack.hpp"
#include "wx/log.h"

#include <cstdio>

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
    memcpy(buffer, (void*)(data+pos), (size_t)readc);
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
        if(offset >= (long)str_size) return -1;
        ioh->pos = offset;
        return 0;
        break;
    case SEEK_CUR:
        newpos = pos+offset;
        if(newpos < 0 || newpos >= (long)str_size) return -1;
        ioh->pos = newpos;
        return 0;
        break;
    case SEEK_END:
        newpos = (long)str_size - 1 - offset;
        if(newpos < 0 || newpos >= (long)str_size) return -1;
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
