#include "ScanlineRasterizer.h"

#include <glm/gtc/matrix_transform.hpp>

ScanlineRasterizer::ScanlineRasterizer(FrameBuffer& fb) : canvas(fb)
{
    projectionMat = glm::perspective(glm::radians(45.0f), (float)fb.width / fb.height, 0.1f, 10.0f);
    viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    viewportMat = glm::mat4(1.0f);
    viewportMat[0][0] = viewportMat[3][0] = (float)(fb.width - 1) * 0.5f;
    viewportMat[1][1] = viewportMat[3][1] = (float)(fb.height - 1) * 0.5f;
}

void ScanlineRasterizer::drawTriangle(Vertex vertices[3], glm::mat4 modelMat)
{
    glm::mat4 mvp = projectionMat * viewMat * modelMat;

    glm::ivec2 points[3];

    for (int i = 0; i < 3; i++)
    {
        glm::vec4 ndc = mvp * glm::vec4(vertices[i].position, 1.0f);
        ndc /= ndc.w;

        glm::vec4 sc = viewportMat * ndc;

        points[i] = glm::ivec2((int)(sc.x + 0.5f), (int)(sc.y + 0.5f));
    }

    glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
    canvas.triangle(points[0], points[1], points[2], color);
}
