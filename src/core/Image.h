#pragma once

#include <vector>
#include <string>
#include "Color.h"

class Image
{
public:
    std::vector<uint32_t> VerticalIter;
    std::vector<uint32_t> HorizontalIter;
    std::vector<std::vector<Color>> Data;

public:
    Image(uint32_t width, float aspectRatio);
    void Resize(uint32_t width, uint32_t height);
    void SaveAsPNG() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    float GetAspectRatio() const;

private:
    void Init();

private:
    uint32_t m_Width;
    uint32_t m_Height;
    float m_AspectRatio;
    std::string m_TmpDir = "../images/rendered/tmp/";
    uint32_t m_Channels = 3;
};
