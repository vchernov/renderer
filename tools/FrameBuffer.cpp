#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
    : Buffer(width, height)
{
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

glm::mat4 FrameBuffer::getViewportMatrix() const
{
    glm::mat4 viewport(1.0f);
    viewport[0][0] = viewport[3][0] = (float)(width - 1) * 0.5f;
    viewport[1][1] = viewport[3][1] = (float)(height - 1) * 0.5f;
    return viewport;
}
