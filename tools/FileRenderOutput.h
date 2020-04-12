#pragma once

#include <string>

#include "IRenderOutput.h"

class FileRenderOutput : public IRenderOutput
{
public:
    FileRenderOutput(const std::string& fn);

    void render(void* buffer, int bufferWidth, int bufferHeight) override;

private:
    std::string fn;
};
