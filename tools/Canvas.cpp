#include "Canvas.h"

#include <algorithm>

Canvas::Canvas(FrameBuffer& fb) : fb(fb)
{
}

void Canvas::pixel(int x, int y, glm::vec3 color)
{
    if (x < 0 || x >= fb.width || y < 0 || y >= fb.height)
        return;
    fb(x, y) = color;
}

// Bresenham Line Algorithm http://www.edepot.com/linebresenham.html
void Canvas::line(int x1, int y1, int x2, int y2, glm::vec3 color)
{
    int dx, dy;
    int incx, incy;

    if (x2 >= x1)
    {
        dx = x2 - x1;
        incx = 1;
    }
    else
    {
        dx = x1 - x2;
        incx = -1;
    }

    if (y2 >= y1)
    {
        dy = y2 - y1;
        incy = 1;
    }
    else
    {
        dy = y1 - y2;
        incy = -1;
    }

    int x = x1;
    int y = y1;

    if (dx >= dy)
    {
        dy <<= 1;
        int balance = dy - dx;
        dx <<= 1;

        while (x != x2)
        {
            pixel(x, y, color);
            if (balance >= 0)
            {
                y += incy;
                balance -= dx;
            }
            balance += dy;
            x += incx;
        }
        pixel(x, y, color);
    }
    else
    {
        dx <<= 1;
        int balance = dx - dy;
        dy <<= 1;

        while (y != y2)
        {
            pixel(x, y, color);
            if (balance >= 0)
            {
                x += incx;
                balance -= dy;
            }
            balance += dx;
            y += incy;
        }
        pixel(x, y, color);
    }
}

void Canvas::wireframe(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color)
{
    line(point0.x, point0.y, point1.x, point1.y, color);
    line(point1.x, point1.y, point2.x, point2.y, color);
    line(point2.x, point2.y, point0.x, point0.y, color);
}

void Canvas::scanline(int y, int x1, int x2, glm::vec3 color)
{
    if (x1 > x2)
        std::swap(x1, x2);
    for (int x = x1; x <= x2; x++)
        pixel(x, y, color);
}

void Canvas::triangle(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color)
{
    if (point0.y == point1.y && point1.y == point2.y)
        return;

    if (point0.y > point1.y)
        std::swap(point0, point1);
    if (point0.y > point2.y)
        std::swap(point0, point2);
    if (point1.y > point2.y)
        std::swap(point1, point2);

    pixel(point0.x, point0.y, color);

    for (int y = point0.y + 1; y < point1.y; y++)
    {
        float x01 = point0.x + (float)(point1.x - point0.x) * (float)(y - point0.y) / (float)(point1.y - point0.y);
        float x02 = point0.x + (float)(point2.x - point0.x) * (float)(y - point0.y) / (float)(point2.y - point0.y);
        scanline(y, (int)(x01 + 0.5f), (int)(x02 + 0.5f), color);
    }

    for (int y = point1.y; y < point2.y; y++)
    {
        float x12 = point1.x + (float)(point2.x - point1.x) * (float)(y - point1.y) / (float)(point2.y - point1.y);
        float x02 = point0.x + (float)(point2.x - point0.x) * (float)(y - point0.y) / (float)(point2.y - point0.y);
        scanline(y, (int)(x12 + 0.5f), (int)(x02 + 0.5f), color);
    }

    pixel(point2.x, point2.y, color);
}
