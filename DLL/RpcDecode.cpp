#include "RpcDecode.hpp"
#include <fstream>
#include "Utils.hpp"

bool RpcDecode::ReadFile(wxString filePath)
{
    m_filePath = filePath;
    std::ifstream file(filePath.char_str(), std::ios_base::binary);
    char temp[100];
    if(!file.is_open()) return false;
    file.read(temp, 3);
    if(strncmp(temp, "RPC", 3) != 0) return false;

    file.seekg(12, std::ios_base::beg);
    file.read(temp, 4);
    m_globalWidth = CharToLong(temp);
    file.read(temp, 4);
    m_globalHeight = CharToLong(temp);
    file.read(temp, 4);
    m_frameCount = CharToLong(temp);
    file.read(temp, 4);
    m_direction = CharToLong(temp);
    file.seekg(44, std::ios_base::beg);
    file.read(temp, 4);
    m_interval = CharToLong(temp);
	m_bottom = 0;

    file.seekg(80, std::ios_base::beg);
    file.read(temp, 4);
    long value = CharToLong(temp);
    m_frameDataInfo = new DataInfo[m_frameCount];
//    if(value == 0)
//	{
//		file.read(temp, 8);
//		m_frameDataInfo[0].beginPos = 80 + 12 * m_frameCount;
//		m_frameDataInfo[0].dataLength = CharToLong(temp);;
//		for(long i = 1; i < m_frameCount; i++)
//		{
//			file.read(temp, 12);
//			m_frameDataInfo[i].beginPos = m_frameDataInfo[i - 1].beginPos +
//				m_frameDataInfo[i - 1].dataLength;
//			m_frameDataInfo[i].dataLength = CharToLong(temp+4);
//		}
//	}
//	else
	{
		file.seekg(0, std::ios_base::end);
		long size = (long)file.tellg() - 80;
		file.seekg(80, std::ios_base::beg);
		char *buffer = new char[size];
		file.read(buffer, size);
		long v1, v2, v3;
		long i = 0;
		for(; i < size; )
		{
			long j = 0;
			for(; j < m_frameCount; j++)
			{
				v1 = CharToLong(buffer + i + j*12);
				v2 = CharToLong(buffer + i + 4 + j*12);
				v3 = CharToLong(buffer + i + 8 + j*12);
				if(v1 == 0 && v2 != 0 && v3 == 0) continue;
				else break;
			}
			if(j == m_frameCount) break;
			i += 4;
		}
		if(i == size)
		{
			delete[] buffer;
			return false;
		}
		m_frameDataInfo[0].beginPos = 80 + i + 12 * m_frameCount;
		m_frameDataInfo[0].dataLength = CharToLong(buffer + i + 4);
		for(long k = 1; k < m_frameCount; k++)
		{
            m_frameDataInfo[k].beginPos = m_frameDataInfo[k - 1].beginPos +
				m_frameDataInfo[k - 1].dataLength;
			m_frameDataInfo[k].dataLength = CharToLong(buffer + i + k*12 + 4);
		}
		delete[] buffer;
	}

    return true;
}

//Mode RGBA
unsigned char* RpcDecode::GetDecodedFrameData(int index)
{
    if(index < 0 && index >= m_frameCount) return NULL;
    std::ifstream file(m_filePath.char_str(), std::ios_base::binary);
    char temp[10];
    if(!file.is_open()) return NULL;

    long length = m_frameDataInfo[index].dataLength;
    long beginPos = m_frameDataInfo[index].beginPos;
    long offset = m_globalHeight*2;
    file.seekg(beginPos + offset, std::ios_base::beg);
    unsigned char* data = (unsigned char*)malloc(m_globalWidth*m_globalHeight*4);
    if(data == NULL) return NULL;
    long idx = 0;
    unsigned char pixelCount;
    file.read(temp, 2);
    unsigned char rgb[3];
    for(long i = 0; i < length - offset;)
    {
        pixelCount = (unsigned char) temp[0];
        if(temp[1] == 0)
        {
			for(unsigned char pc = 0; pc < pixelCount; pc++)
			{
				data[idx++] = 0;
                data[idx++] = 0;
                data[idx++] = 0;
                data[idx++] = 0;
			}
        }
        else
        {
            unsigned char alpha = Bit5ToBit8(temp[1]);
            for(unsigned char pc = 0; pc < pixelCount; pc++)
            {
                file.read(temp, 2);
                i += 2;
                Bit5ToBit8RGB(temp, rgb);
                data[idx++] = rgb[0];
                data[idx++] = rgb[1];
                data[idx++] = rgb[2];
                data[idx++] = alpha;
            }
        }
        file.read(temp, 2);
        i += 2;
    }
    //wxMessageBox(wxString::Format("length:%d,idx:%d", length,idx));
    return data;
}

FILOCRGBQUAD* RpcDecode::GetFIDecodedFrameData(int index)
{
    unsigned char* data = GetDecodedFrameData(index);
    if(data == NULL) return NULL;
    long length = m_globalWidth*m_globalHeight;
    FILOCRGBQUAD *quad = new FILOCRGBQUAD[length];
    long idx = 0;
    for(long i = 0; i < length; i++)
    {
        quad[i].rgbBlue = data[idx++];
        quad[i].rgbGreen = data[idx++];
        quad[i].rgbRed = data[idx++];
        quad[i].rgbReserved = data[idx++];
    }
    free(data);
    return quad;
}
