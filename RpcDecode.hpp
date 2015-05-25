#ifndef RPCDECODE_HPP_INCLUDED
#define RPCDECODE_HPP_INCLUDED

#include "wx/string.h"
#include "FreeImage.h"

struct DataInfo
{
	long beginPos;
	long dataLength;
};

class RpcDecode
{
public:
	RpcDecode()
	{
		m_frameDataInfo = NULL;
	}
	~RpcDecode()
	{
		if(m_frameDataInfo != NULL)delete []m_frameDataInfo;
	}
	bool ReadFile(wxString filePath);
	//Mode RGBA
	unsigned char* GetDecodedFrameData(int index);
	FILOCRGBQUAD* GetFIDecodedFrameData(int index);

	unsigned long GetFramesCounts()
	{
		return m_frameCount;
	}
    long GetGlobleWidth()
    {
    	return m_globalWidth;
    }
    long GetGlobleHeight()
    {
    	return m_globalHeight;
    }
    long GetDirection()
    {
    	return m_direction;
    }
    unsigned long GetInterval()
    {
    	return m_interval;
    }
    long GetBottom()
    {
    	return m_bottom;
    }
private:
	wxString m_filePath;
	long m_globalWidth;
	long m_globalHeight;
	long m_direction;
	long m_interval;
	long m_bottom;
	long m_frameCount;
	DataInfo *m_frameDataInfo;
};

#endif // RPCDECODE_HPP_INCLUDED
