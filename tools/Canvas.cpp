#include "Canvas.h"

Canvas::Canvas(FrameBuffer& fb) : fb(fb)
{
}

void Canvas::drawPoint(glm::ivec2 location, glm::vec3 color)
{
    if (location.x < 0 || location.x >= fb.width || location.y < 0 || location.y >= fb.height)
        return;
    fb(location.x, location.y) = color;
}

void Canvas::drawLine(glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color)
{
    if (glm::abs(point2.y - point1.y) < glm::abs(point2.x - point1.x))
    {
        glm::ivec2 start, end;
        if (point1.x > point2.x)
        {
            start = point2;
            end = point1;
        }
        else
        {
            start = point1;
            end = point2;
        }

        glm::ivec2 delta = end - start;
        int yi;
        if (delta.y < 0)
        {
            yi = -1;
            delta.y = -delta.y;
        }
        else
        {
            yi = 1;
        }
        int d = 2 * delta.y - delta.x;

        for (auto pos = start; pos.x <= end.x; pos.x++)
        {
            drawPoint(pos, color);
            if (d > 0)
            {
                pos.y += yi;
                d -= 2 * delta.x;
            }
            d += 2 * delta.y;
        }
    }
    else
    {
        glm::ivec2 start, end;
        if (point1.y > point2.y)
        {
            start = point2;
            end = point1;
        }
        else
        {
            start = point1;
            end = point2;
        }

        glm::ivec2 delta = end - start;
        int xi;
        if (delta.x < 0)
        {
            xi = -1;
            delta.x = -delta.x;
        }
        else
        {
            xi = 1;
        }
        int d = 2 * delta.x - delta.y;

        for (auto pos = start; pos.y <= end.y; pos.y++)
        {
            drawPoint(pos, color);
            if (d > 0)
            {
                pos.x += xi;
                d -= 2 * delta.y;
            }
            d += 2 * delta.x;
        }
    }
}
