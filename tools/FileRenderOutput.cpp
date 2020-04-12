#include "FileRenderOutput.h"

#include "ppm.h"

FileRenderOutput::FileRenderOutput(const std::string& fn)
    : fn(fn)
{
}

void FileRenderOutput::render(void* buffer, int bufferWidth, int bufferHeight)
{
    ppm(buffer, bufferWidth, bufferHeight, fn.c_str());
}
