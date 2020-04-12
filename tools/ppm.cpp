#include "ppm.h"

#include <fstream>

void ppm(void* buffer, int width, int height, const char* fn)
{
    std::ofstream file(fn, std::ofstream::binary);
    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(static_cast<char*>(buffer), (size_t)width * height * 3);
    file.close();
}
