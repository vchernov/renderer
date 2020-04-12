#pragma once

#include <glm/glm.hpp>

struct FragmentInput
{
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec3 worldPos;
};

class IFragmentShader
{
public:
    virtual ~IFragmentShader() = default;

    virtual glm::vec3 fragment(const FragmentInput& input) = 0;
};
