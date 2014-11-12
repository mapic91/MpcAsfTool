#include "MpcDecode.hpp
#include "wx/file.h"

MpcDecode::MpcDecode(const wxString MpcFilePath)
{
    FilePath = MpcFilePath;
}
void MpcDecode::SetMpcFile(const wxString MpcFilePath)
{
    FilePath = MpcFilePath;
}
bool MpcDecode::ReadMpcFile()
{
    if(FilePath.IsEmpty()) return false;
    else
    {
        wxFile mpcfile;
    }
}
bool MpcDecode::ReadMpcFile(const wxString MpcFilePath)
{

}
wxString MpcDecode::GetVersionInfo()
{

}
unsigned long MpcDecode::GetFramesDataLengthSum()
{

}
unsigned long MpcDecode::GetFramesCounts()
{

}
unsigned long MpcDecode::GetFrameDataLength(const unsigned long index)
{

}
long MpcDecode::GetGlobleWidth()
{

}
long MpcDecode::GetGlobleHeight()
{

}
long MpcDecode::GetFrameWidth(const unsigned long index)
{

}
long MpcDecode::GetFrameHeight(const unsigned long index)
{

}
long MpcDecode::GetDirection()
{

}
unsigned long MpcDecode::GetColourCounts()
{

}
unsigned long MpcDecode::GetInterval()
{

}
long MpcDecode::GetBottom()
{

}
Palette* MpcDecode::GetPalette()
{

}
FrameData* MpcDecode::GetFrameData(const unsigned long index)
{

}
wxImage MpcDecode::GetFrameImage(const unsigned long index)
{

}
