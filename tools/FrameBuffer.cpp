#include "FrameBuffer.h"

#include <cassert>

FrameBuffer::FrameBuffer(int width, int height) : width(width), height(height)
{
    assert(width >= 0);
    assert(height >= 0);
    pixels = new glm::vec3[(size_t) width * height];
}

FrameBuffer::~FrameBuffer()
{
    delete[] pixels;
}

glm::vec3& FrameBuffer::operator()(int x, int y)
{
    return pixels[y * width + x];
}

void FrameBuffer::fill(glm::vec3 color)
{
    for (auto i = 0, size = width * height; i < size; i++)
        pixels[i] = color;
}

void FrameBuffer::get(uint8_t* buffer, uint8_t (*pack)(float))
{
    int offset = 0;
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            const glm::vec3& p = (*this)(x, y);
            buffer[offset] = pack(p.r);
            buffer[offset + 1] = pack(p.g);
            buffer[offset + 2] = pack(p.b);
            offset += 3;
        }
    }
}
