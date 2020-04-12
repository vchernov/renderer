#include "DiffuseFragmentShader.h"

glm::vec3 DiffuseFragmentShader::fragment(const FragmentInput& input)
{
    glm::vec3 lightDir = glm::normalize(input.worldPos - lightPos);
    glm::vec3 fragNormal = glm::normalize(normalMatrix * input.normal);
    float intensity = glm::max(glm::dot(fragNormal, lightDir), 0.0f);
    return input.color * intensity;
}
