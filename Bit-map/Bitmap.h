#ifndef __BITMAP__
#define __BITMAP__

#include <cstdint>
#include <memory>

class Bitmap
{
private:
    uint8_t     *buffer;
    uint8_t     width;
    uint32_t    size;
    bool        is_init;

public:
    Bitmap():buffer(nullptr), size(0), is_init(false), width(0)
    {}

    bool Init(uint32_t  _s)
    {
        size = _s;
        width = sizeof(uint8_t);
        buffer = new uint8_t[size/width+1];
        if(buffer)
        {
            memset(buffer, 0x00, size/width+1);
            is_init = true;
        }
        return is_init;
    }

    bool SetBit(uint32_t index)
    {
        if( is_init == false || index >= size)
        {
            return false;
        }

        buffer[index / width] |= GetMask(index);
        return true;
    }

    int GetBit(uint32_t index)
    {
        if( is_init == false || index >= size)
        {
            return -1;
        }
        return buffer[index / width] & GetMask(index);
    }

    bool ClrBit(uint32_t index)
    {
        if( is_init == false || index >= size)
        {
            return false;
        }
        buffer[index / width] &= ~GetMask(index);
        return true;
    }

    void Clear()
    {
        if(is_init)
        {
            memset(buffer, 0x00, size/width+1);
        }
    }

private:
    uint8_t GetMask(uint32_t index)
    {
        return (uint8_t)0x01 << (index % width);
    }
};

#endif