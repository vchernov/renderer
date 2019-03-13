#include "ObjReader.h"

#include <fstream>
#include <string>
#include <sstream>

Mesh ObjReader::load(const std::string& fn)
{
    Mesh mesh;
    std::ifstream file(fn);
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string descriptor;
        ss >> descriptor;
        if (descriptor == "v")
        {
            glm::vec3 vertex;
            ss >> vertex.x;
            ss >> vertex.y;
            ss >> vertex.z;
            mesh.vertices.push_back(vertex);
        }
        else if (descriptor == "vt")
        {
            glm::vec2 texCoord;
            ss >> texCoord.x;
            ss >> texCoord.y;
            mesh.texCoords.push_back(texCoord);
        }
        else if (descriptor == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x;
            ss >> normal.y;
            ss >> normal.z;
            mesh.normals.push_back(normal);
        }
        else if (descriptor == "f")
        {
            Face face;
            int index;
            char delimiter;
            for (int i = 0; i < 3; i++)
            {
                ss >> index;
                face.vertexIndices[i] = index - 1;
                ss >> delimiter;
                ss >> index;
                face.texCoordIndices[i] = index - 1;
                ss >> delimiter;
                ss >> index;
                face.normalIndices[i] = index - 1;
            }
            mesh.faces.push_back(face);
        }
    }
    return mesh;
}
