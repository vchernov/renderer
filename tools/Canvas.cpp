#include "Canvas.h"

#include <algorithm>

Canvas::Canvas(FrameBuffer& fb) : fb(fb)
{
}

void Canvas::drawPoint(glm::ivec2 location, glm::vec3 color)
{
    if (location.x < 0 || location.x >= fb.width || location.y < 0 || location.y >= fb.height)
        return;
    fb(location.x, location.y) = color;
}

/*
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
*/

void Canvas::drawLine(glm::ivec2 point0, glm::ivec2 point1, glm::vec3 color)
{
    bool steep = false;
    if (glm::abs(point0.x - point1.x) < glm::abs(point0.y - point1.y))
    {
        std::swap(point0.x, point0.y);
        std::swap(point1.x, point1.y);
        steep = true;
    }
    if (point0.x > point1.x)
    {
        std::swap(point0.x, point1.x);
        std::swap(point0.y, point1.y);
    }
    int dx = point1.x - point0.x;
    int dy = point1.y - point0.y;
    int derr = std::abs(dy) * 2;
    int err = 0;
    int y = point0.y;
    for (int x = point0.x; x <= point1.x; x++)
    {
        if (steep)
            drawPoint({y, x}, color);
        else
            drawPoint({x, y}, color);
        err += derr;
        if (err > dx)
        {
            y += (point1.y > point0.y) ? 1 : -1;
            err -= dx * 2;
        }
    }
}

void Canvas::wireframe(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color)
{
    drawLine(point0, point1, color);
    drawLine(point1, point2, color);
    drawLine(point2, point0, color);
}

void Canvas::triangle(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color)
{
    if (point0.y == point1.y && point0.y == point2.y)
        return;

    if (point0.y > point1.y)
        std::swap(point0, point1);
    if (point0.y > point2.y)
        std::swap(point0, point2);
    if (point1.y > point2.y)
        std::swap(point1, point2);

    int totalHeight = point2.y - point0.y;
    int firstHalfHeight = point1.y - point0.y;
    int secondHalfHeight = point2.y - point1.y;
    for (int i = 0; i < totalHeight; i++)
    {
        float alpha = (float)i / totalHeight;
        glm::ivec2 a = point0 + glm::ivec2(glm::round(glm::vec2(point2 - point0) * alpha));

        glm::ivec2 b;
        if (i > firstHalfHeight || point1.y == point0.y)
        {
            float beta = (float)(i - firstHalfHeight) / secondHalfHeight;
            b = point1 + glm::ivec2(glm::round(glm::vec2(point2 - point1) * beta));
        }
        else
        {
            float beta = (float)i / firstHalfHeight;
            b = point0 + glm::ivec2(glm::round(glm::vec2(point1 - point0) * beta));
        }

        if (a.x > b.x)
            std::swap(a, b);
        for (int x = a.x; x <= b.x; x++)
            drawPoint({x, point0.y + i}, color);
    }
}
