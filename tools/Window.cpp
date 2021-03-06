#include "Window.h"

Window::Window(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::render(void* buffer, int bufferWidth, int bufferHeight, uint32_t fps)
{
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
    #else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
    #endif

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(buffer, bufferWidth, bufferHeight, 24, bufferWidth * 3, rmask, gmask, bmask, amask);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    uint32_t minFrameTime = 1000 / fps;

    bool exit = false;
    while (!exit)
    {
        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                exit = true;
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
            {
                exit = true;
            }
        }

        uint32_t frameStartTime = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        uint32_t frameTime = SDL_GetTicks() - frameStartTime;
        if (frameTime < minFrameTime)
            SDL_Delay(minFrameTime - frameTime);
    }

    SDL_DestroyTexture(texture);
}
