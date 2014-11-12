#ifndef FREEIMAGE_IO_CALLBACK_HPP_INCLUDED
#define FREEIMAGE_IO_CALLBACK_HPP_INCLUDED

#include "wx/stream.h"
#include "FreeImage.h"
struct FI_IO_Handle
{
    long pos;
    unsigned long size;
    BYTE *stream;
};
unsigned DLL_CALLCONV MyFI_ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle);
unsigned DLL_CALLCONV MyFI_WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle);
int DLL_CALLCONV MyFI_SeekProc(fi_handle handle, long offset, int origin);
long DLL_CALLCONV MyFI_TellProc(fi_handle handle);

#endif // FREEIMAGE_IO_CALLBACK_HPP_INCLUDED
