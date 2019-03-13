#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Face
{
	glm::ivec3 vertexIndices;
	glm::ivec3 texCoordIndices;
	glm::ivec3 normalIndices;
};

struct Mesh
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<Face> faces;
};
