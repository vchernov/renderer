#pragma once

#include <glm/glm.hpp>

glm::vec3 barycentric(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

bool isInsideTriangle(float u, float v, float w);
