#include <iostream>

#include <Window.h>
#include <FrameBuffer.h>

#include <glm/gtc/packing.hpp>

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;

    FrameBuffer fb(1024, 768);
    for (int j = 0; j < fb.height; j++)
        for (int i = 0; i < fb.width; i++)
            fb(i, j) = glm::vec3(j / (float)fb.height, i / (float)fb.width, 0.0f);

    Window wnd(800, 600);
    uint8_t* buffer = new uint8_t[(size_t) fb.width * fb.height * 3];
    fb.get(buffer, glm::packUnorm1x8);
    wnd.render(buffer, fb.width, fb.height);
    delete[] buffer;

    std::cout << "end" << std::endl;
    return 0;
}
