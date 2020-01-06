#include <iostream>

#include <Window.h>
#include <FrameBuffer.h>
#include <Canvas.h>
#include <Mesh.h>
#include <ObjReader.h>

#include <glm/gtc/packing.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;

    std::string fn;
    if (argc > 1)
        fn = argv[1];
    Mesh mesh = ObjReader::load(fn);

    FrameBuffer fb(1024, 768);
    fb.fill({0.0f, 0.0f, 0.0f});
    Canvas canvas(fb);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)fb.width / fb.height, 0.1f, 10.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::mat4(1.0f);

    for (const auto& face : mesh.faces)
    {
        glm::ivec2 screenCoords[3];
        for (int i = 0; i < 3; i++)
        {
            glm::vec3 position = mesh.vertices[face.vertexIndices[i]];
            glm::vec3 sc = glm::project(position, view * model, projection, glm::vec4(0.0f, 0.0f, (float)fb.width, (float)fb.height));
            screenCoords[i] = sc;
        }

        canvas.wireframe(screenCoords[0], screenCoords[1], screenCoords[2], {1.0f, 1.0f, 1.0f});
    }

    Window wnd(fb.width, fb.height);
    uint8_t* buffer = new uint8_t[(size_t)fb.width * fb.height * 3];
    fb.get(buffer, [](float c) { return static_cast<uint8_t>(c * 255.0f); });
    wnd.render(buffer, fb.width, fb.height);
    delete[] buffer;

    std::cout << "end" << std::endl;
    return 0;
}
