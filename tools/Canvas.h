#pragma once

#include <glm/glm.hpp>

#include "FrameBuffer.h"

class Canvas
{
public:
    Canvas(FrameBuffer& fb);
    virtual ~Canvas() = default;

    void drawPoint(glm::ivec2 location, glm::vec3 color);
    void drawLine(glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color);

private:
    FrameBuffer& fb;
};
