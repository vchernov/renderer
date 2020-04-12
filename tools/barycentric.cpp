#include "barycentric.h"

// Barycentric coordinates https://vegard.wiki/w/Barycentric_coordinates
glm::vec3 barycentric(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 p)
{
    auto v0 = b - a;
    auto v1 = c - a;
    auto v2 = p - a;

    float d00 = glm::dot(v0, v0);
    float d01 = glm::dot(v0, v1);
    float d11 = glm::dot(v1, v1);
    float d20 = glm::dot(v2, v0);
    float d21 = glm::dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;

    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;

    return glm::vec3(u, v, w);
}

bool isInsideTriangle(float u, float v, float w)
{
    if (u < 0.0f || u > 1.0f)
        return false;
    if (v < 0.0f || v > 1.0f)
        return false;
    if (w < 0.0f || w > 1.0f)
        return false;
    return true;
}
