#pragma once

#include "Buffer.h"

#include <glm/glm.hpp>

class FrameBuffer : public Buffer<glm::vec3>
{
public:
    FrameBuffer(int width, int height);

    void get(uint8_t* buffer, uint8_t (*pack)(float));

    glm::mat4 getViewportMatrix() const;
};
