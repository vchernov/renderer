#pragma once

#include <glm/glm.hpp>

#include "FrameBuffer.h"

class Canvas
{
public:
    Canvas(FrameBuffer& fb);
    virtual ~Canvas() = default;

    void pixel(int x, int y, glm::vec3 color);

    void line(int x1, int y1, int x2, int y2, glm::vec3 color);

    void wireframe(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color);

    void scanline(int y, int x1, int x2, glm::vec3 color);

    void triangle(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color);

private:
    FrameBuffer& fb;
};
