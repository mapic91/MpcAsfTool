#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

long CharToLong(char* char4);
unsigned char Bit5ToBit8(char value);
unsigned char Bit5ToBit8(unsigned char value);
void Bit5ToBit8RGB(char* char2, unsigned char *rgb);

#include "FreeImage.h"
FILOCRGBQUAD *RGBAtoFIRGBA(unsigned char *data, bool freeData, long width, long height, long globalWidth, long globalHeight, int offx, int offy);

#endif // UTILS_HPP_INCLUDED
