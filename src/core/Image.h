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
    std::vector<uint32_t> VerticalIter;
    std::vector<uint32_t> HorizontalIter;

public:
    Image(int width, float aspectRatio);
    void AddPixel(float x, float y, const Color &color);
    std::vector<Pixel> GetPixels();
    void Clear();
    void SaveAsPNG();

private:
    std::vector<Pixel> m_Pixels;
    std::mutex m_Mtx;
    std::string m_TmpDir = "../images/rendered/tmp/";
    int m_Channels = 3;
};
