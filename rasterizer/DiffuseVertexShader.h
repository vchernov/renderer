#pragma once

#include "IVertexShader.h"

class DiffuseVertexShader : public IVertexShader
{
public:
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::mat4 viewport = glm::mat4(1.0f);

    VertexOutput vertex(const Vertex& v) override;
};
