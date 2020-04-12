#include "WindowRenderOutput.h"

#include "Window.h"

void WindowRenderOutput::render(void* buffer, int bufferWidth, int bufferHeight)
{
    Window wnd(bufferWidth, bufferHeight);
    wnd.render(buffer, bufferWidth, bufferHeight);
}
