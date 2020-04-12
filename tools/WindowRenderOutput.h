#pragma once

#include "IRenderOutput.h"

class WindowRenderOutput : public IRenderOutput
{
public:
    void render(void* buffer, int bufferWidth, int bufferHeight) override;
};
