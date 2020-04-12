#pragma once

#include <memory>
#include <vector>

#include "IRenderOutput.h"

class CompositeRenderOutput : public IRenderOutput
{
public:
    void render(void* buffer, int bufferWidth, int bufferHeight) override;

    void add(std::shared_ptr<IRenderOutput> output);

private:
    std::vector<std::shared_ptr<IRenderOutput>> outputs;
};
