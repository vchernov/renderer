#pragma once

class IRenderOutput
{
public:
    virtual ~IRenderOutput() = default;

    virtual void render(void* buffer, int bufferWidth, int bufferHeight) = 0;
};
