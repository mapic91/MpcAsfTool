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

