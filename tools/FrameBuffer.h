#pragma once

#include <glm/glm.hpp>

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);
    virtual ~FrameBuffer();

    const int width;
    const int height;

    glm::vec3& operator()(int x, int y);

    void fill(glm::vec3 color);

    void get(uint8_t* buffer, uint8_t (*pack)(float));

private:
    glm::vec3* pixels;
};
