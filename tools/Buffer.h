#pragma once

#include <cassert>

template<typename T>
class Buffer
{
public:
    Buffer(int width, int height)
        : width(width)
        , height(height)
    {
        assert(width >= 0);
        assert(height >= 0);
        data = new T[(size_t)width * height];
    }

    virtual ~Buffer()
    {
        delete[] data;
    }

    const int width;
    const int height;

    T& operator()(int x, int y)
    {
        return data[y * width + x];
    }

    void fill(T value)
    {
        for (auto i = 0, size = width * height; i < size; i++)
            data[i] = value;
    }

private:
    T* data;
};
