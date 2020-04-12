#pragma once

#include <Buffer.h>
#include <Canvas.h>
#include <FrameBuffer.h>
#include <Mesh.h>

#include "IFragmentShader.h"
#include "IVertexShader.h"

class IRenderOutput;
class DiffuseVertexShader; //TODO

class Rasterizer
{
public:
    Rasterizer(FrameBuffer& fb);
    virtual ~Rasterizer();

    void rasterize(const Mesh& mesh, DiffuseVertexShader* vertexShader, IFragmentShader* fragmentShader);
    void render(IRenderOutput* output);

private:
    void getBounds(VertexOutput vo[3], glm::ivec2& boundsMin, glm::ivec2& boundsMax);

    FrameBuffer& fb;
    Canvas canvas;
    Buffer<float> zbuffer;
};
