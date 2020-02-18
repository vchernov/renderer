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

// Draws flat triangle using scanline algorithm. Inspired by http://www-users.mat.uni.torun.pl/~wrona/3d_tutor/tri_fillers.html
void Canvas::triangle(glm::ivec2 point0, glm::ivec2 point1, glm::ivec2 point2, glm::vec3 color)
{
    glm::ivec2 points[] = {point0, point1, point2};
    std::sort(points, points + 3, [](const glm::ivec2& a, const glm::ivec2& b) -> bool
        {
            return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
        }
    );

    float dx01 = (float)(points[1].x - points[0].x) / (float)(points[1].y - points[0].y);
    float dx02 = (float)(points[2].x - points[0].x) / (float)(points[2].y - points[0].y);
    float dx12 = (float)(points[2].x - points[1].x) / (float)(points[2].y - points[1].y);

    auto horizontalLine = [this, &color](int y, int from, int to)
    {
        for (int x = from; x <= to; x++)
            pixel(x, y, color);
    };

    float xl, xr;
    xl = xr = (float)points[0].x;

    if (dx01 < dx02)
    {
        for (int y = points[0].y; y < points[1].y; y++, xl += dx01, xr += dx02)
            horizontalLine(y, (int)xl, (int)xr);
        xl = (float)points[1].x;
        for (int y = points[1].y; y <= points[2].y; y++, xl += dx12, xr += dx02)
            horizontalLine(y, (int)xl, (int)xr);
    }
    else if (dx01 > dx02)
    {
        for (int y = points[0].y; y < points[1].y; y++, xl += dx02, xr += dx01)
            horizontalLine(y, (int)xl, (int)xr);
        xr = (float)points[1].x;
        for (int y = points[1].y; y <= points[2].y; y++, xl += dx02, xr += dx12)
            horizontalLine(y, (int)xl, (int)xr);
    }
}
