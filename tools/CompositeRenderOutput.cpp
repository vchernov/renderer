#include "CompositeRenderOutput.h"

void CompositeRenderOutput::render(void* buffer, int bufferWidth, int bufferHeight)
{
    for (const auto& output : outputs)
        output->render(buffer, bufferWidth, bufferHeight);
}

void CompositeRenderOutput::add(std::shared_ptr<IRenderOutput> output)
{
    outputs.push_back(std::move(output));
}
