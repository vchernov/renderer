#pragma once

#include "IFragmentShader.h"

class DiffuseFragmentShader : public IFragmentShader
{
public:
    glm::mat3 normalMatrix;
    glm::vec3 lightPos;

    glm::vec3 fragment(const FragmentInput& input) override;
};
