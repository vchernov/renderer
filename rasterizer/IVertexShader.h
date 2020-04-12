#pragma once

#include "Vertex.h"

struct VertexOutput
{
    glm::vec4 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 worldPos;
    glm::vec4 ndc; // normalized device coordinates
    glm::vec4 sc; // screen coordinates
    glm::vec3 nsc; // normalized screen coordinates
    glm::ivec2 sp;
};

class IVertexShader
{
public:
    virtual ~IVertexShader() = default;

    virtual VertexOutput vertex(const Vertex& v) = 0;
};
