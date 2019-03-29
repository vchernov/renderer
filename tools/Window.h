#pragma once

#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height);
    virtual ~Window();

    void render(void* buffer, int bufferWidth, int bufferHeight, uint32_t fps = 30);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
