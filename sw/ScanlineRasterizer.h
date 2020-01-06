#pragma once

#include <Canvas.h>

#include "Vertex.h"

class ScanlineRasterizer
{
public:
    ScanlineRasterizer(FrameBuffer& fb);

    void drawTriangle(Vertex vertices[3], glm::mat4 modelMat);

private:
    Canvas canvas;

    glm::mat4 viewportMat;
    glm::mat4 projectionMat;
    glm::mat4 viewMat;
};
