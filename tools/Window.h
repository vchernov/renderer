#pragma once

#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height);
    virtual ~Window();

    void render(void* buffer, int width, int height);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
