#include <iostream>

#include <Window.h>
#include <FrameBuffer.h>
#include <Mesh.h>
#include <ObjReader.h>

#include <glm/gtc/packing.hpp>

#include "ScanlineRasterizer.h"

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;

    std::string fn;
    if (argc > 1)
        fn = argv[1];
    Mesh mesh = ObjReader::load(fn);

    FrameBuffer fb(1024, 768);
    fb.fill({0.0f, 0.0f, 0.0f});

    ScanlineRasterizer rasterizer(fb);

    for (const auto& face : mesh.faces)
    {
        Vertex vertices[3];
        for (int i = 0; i < 3; i++)
        {
            vertices[i].position = mesh.vertices[face.vertexIndices[i]];
            vertices[i].texCoords = mesh.texCoords[face.texCoordIndices[i]];
            vertices[i].normal = mesh.normals[face.normalIndices[i]];
            vertices[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
        }

        rasterizer.drawTriangle(vertices, glm::mat4(1.0f));
    }

    Window wnd(fb.width, fb.height);
    uint8_t* buffer = new uint8_t[(size_t)fb.width * fb.height * 3];
    fb.get(buffer, glm::packUnorm1x8);
    wnd.render(buffer, fb.width, fb.height);
    delete[] buffer;

    std::cout << "end" << std::endl;
    return 0;
}
