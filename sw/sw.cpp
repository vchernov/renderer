#include <iostream>

#include <Window.h>
#include <FrameBuffer.h>
#include <Canvas.h>
#include <Mesh.h>
#include <ObjReader.h>

#include <glm/gtc/packing.hpp>

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;

    std::string fn;
    if (argc > 1)
        fn = argv[1];
    Mesh mesh = ObjReader::load(fn);

    FrameBuffer fb(1024, 1024);
    fb.fill({ 0.0f, 0.0f, 0.0f });
    Canvas canvas(fb);

    for (const auto& face : mesh.faces)
    {
        for (int i = 0; i < 3; i++)
        {
            int vertInd1 = face.vertexIndices[i];
            int vertInd2 = face.vertexIndices[(i + 1) % 3];
            glm::vec3 vert1 = mesh.vertices[vertInd1];
            glm::vec3 vert2 = mesh.vertices[vertInd2];

            glm::ivec2 point1;
            point1.x = static_cast<int>((vert1.x + 1.0f) * fb.width * 0.5f);
            point1.y = static_cast<int>((vert1.y + 1.0f) * fb.height * 0.5f);

            glm::ivec2 point2;
            point2.x = static_cast<int>((vert2.x + 1.0f) * fb.width * 0.5f);
            point2.y = static_cast<int>((vert2.y + 1.0f) * fb.height * 0.5f);

            canvas.drawLine(point1, point2, { 1.0f, 1.0f, 1.0f });
        }
    }

    Window wnd(1024, 1024);
    uint8_t* buffer = new uint8_t[(size_t) fb.width * fb.height * 3];
    fb.get(buffer, glm::packUnorm1x8);
    //fb.get(buffer, [](float c) { return static_cast<uint8_t>(c * 255.0f); });
    wnd.render(buffer, fb.width, fb.height);
    delete[] buffer;

    std::cout << "end" << std::endl;
    return 0;
}
