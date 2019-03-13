#pragma once

#include "Mesh.h"

class ObjReader
{
public:
    static Mesh load(const std::string& fn);
};
