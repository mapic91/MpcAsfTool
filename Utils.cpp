#include "Utils.hpp"

long CharToLong(char* char4)
{
	long temp = 0;
	temp |= ( ((long)((unsigned char)char4[0]) & (long)0xFF) );
	temp |= ( ((long)((unsigned char)char4[1]) & (long)0xFF) << 8 );
	temp |= ( ((long)((unsigned char)char4[2]) & (long)0xFF) << 16 );
	temp |= ( ((long)((unsigned char)char4[3]) & (long)0xFF) << 24 );
	return temp;
}

unsigned char Bit5ToBit8(char value)
{
	return Bit5ToBit8((unsigned char)value);
}

unsigned char Bit5ToBit8(unsigned char value)
{
	return (unsigned char)((float)value*(float)255/(float)31);
}

unsigned char Bit4ToBit8(unsigned char value)
{
	return (unsigned char)((float)value*(float)255/(float)15);
}

unsigned char Bit6ToBit8(unsigned char value)
{
	return (unsigned char)((float)value*(float)255/(float)63);
}

void Bit5ToBit8RGB(char* char2, unsigned char *rgb)
{
	unsigned char a = (unsigned char)char2[0];
	unsigned char b = (unsigned char)char2[1];
	unsigned long d = 0;
	d = ((d | b) << 8);
	d = (d | a);
	rgb[0] = (0x1F & d);
	rgb[1] = ((0x7E0 & d) >> 5);
	rgb[2] = ((0xF800 & d) >> 11);
	rgb[0] = Bit5ToBit8(rgb[0]);
	rgb[1] = Bit6ToBit8(rgb[1]);
	rgb[2] = Bit5ToBit8(rgb[2]);
}

FILOCRGBQUAD *RGBAtoFIRGBA(unsigned char *data, long width, long height, long globalWidth, long globalHeight, int offx, int offy)
{
	if(data == NULL) return NULL;
	long size = globalWidth*globalHeight;
	FILOCRGBQUAD *fidata = new FILOCRGBQUAD[size];
	if(!fidata) return NULL;
	for(long i = 0; i < size; i++)
	{
		fidata[i].rgbRed = 0;
		fidata[i].rgbGreen = 0;
		fidata[i].rgbBlue = 0;
		fidata[i].rgbReserved = 0;
	}
	long offwidth, offheight;
	for(long hi = 0; hi < globalWidth; hi++)
    {
        for(long wi = 0; wi < globalHeight; wi++)
        {
            offwidth = wi + offx;
            offheight = hi + offy;
            if(hi < height && wi < width &&
                    offwidth >= 0 && offwidth < globalWidth &&
                    offheight >= 0 && offheight < globalHeight)
            {
            	long index = (hi*width+wi)*4;
            	long fiIndex = offheight*globalWidth+offwidth;
                fidata[fiIndex].rgbRed = data[index];
                fidata[fiIndex].rgbGreen = data[index+1];
                fidata[fiIndex].rgbBlue = data[index+2];
                fidata[fiIndex].rgbReserved = data[index+3];
            }
        }
    }
    return fidata;
}
