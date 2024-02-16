#pragma once

#include "Pixel.h"
#include <vector>
#include <mutex>

class Image
{
public:
    int Width;
    float AspectRatioIdeal;
    int Height;
    float AspectRatioReal;

public:
    Image(int width, float aspectRatio);
    void AddPixel(float x, float y, const Color &color);
    std::vector<Pixel> GetPixels() const;
    void Clear();

private:
    std::vector<Pixel> m_Pixels;
    std::mutex m_Mtx;
};
