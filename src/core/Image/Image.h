#pragma once
#include <vector>
#include "Vec3.h"
class Image
{
public:
    std::vector<Vec3> Pixels;
    int Width, Height;

    Image(int width, int height);
    void SetPixel(int x, int y, const Vec3 &color);
};