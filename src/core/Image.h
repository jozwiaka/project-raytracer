#pragma once

#include <vector>
#include <string>
#include "Color.h"

class Image
{
public:
    uint32_t Width;
    uint32_t Height;
    float AspectRatio;
    std::vector<uint32_t> VerticalIter;
    std::vector<uint32_t> HorizontalIter;
    std::vector<std::vector<Color>> Data;

public:
    Image(uint32_t width, float aspectRatio);
    void Resize();
    void SaveAsPNG();

private:
    std::string m_TmpDir = "../images/rendered/tmp/";
    uint32_t m_Channels = 3;
};
