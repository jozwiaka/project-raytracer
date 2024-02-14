#pragma once

#include "Pixel.h"
#include <vector>

class Image
{
public:
    int Width;
    float AspectRatioIdeal;
    int Height;
    float AspectRatioReal;
    std::vector<Pixel> Pixels;

public:
    Image(int width, float aspectRatio);

private:
};
