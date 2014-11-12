#include "Little_Big_Endian_Convert.hpp"

unsigned long LittoLocUL(const unsigned long value)
{
    unsigned long a = 1;
    if((*(char*)&a) == 1 ) return value;
    else
    {
        a = 0;
        a |= ( (value & 0xFF) << 24);
        a |= ( (value & 0xFF00) << 8);
        a |= ( (value & 0xFF0000) >> 8);
        a |= ( (value & 0xFF000000) >> 24);
        return a;
    }
}
long LittoLocL(const long value)
{
    long a = 1;
    if((*(char*)&a) == 1 ) return value;
    else
    {
        a = 0;
        a |= ( (value & 0xFF) << 24);
        a |= ( (value & 0xFF00) << 8);
        a |= ( (value & 0xFF0000) >> 8);
        a |= ( (value & 0xFF000000) >> 24);
        return a;
    }
}
unsigned short LittoLocUS(const unsigned short value)
{
    unsigned short a = 1;
    if((*(char*)&a) == 1 ) return value;
    else
    {
        a = 0;
        a |= ( (value & 0xFF) << 8);
        a |= ( (value & 0xFF00) >> 8);
        return a;
    }
}
short LittoLocS(const short value)
{
    short a = 1;
    if((*(char*)&a) == 1 ) return value;
    else
    {
        a = 0;
        a |= ( (value & 0xFF) << 8);
        a |= ( (value & 0xFF00) >> 8);
        return a;
    }
}
