#pragma once

#include <vector>
#include <string>
#include "Color.h"

class Image
{
public:
    std::vector<std::vector<Color>> Data;

public:
    Image(uint32_t width, float aspectRatio);
    ~Image();
    void Resize(uint32_t width, uint32_t height);
    void Save();
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    float GetAspectRatio() const;
    std::vector<uint32_t> &GetVerticalIter();
    std::vector<uint32_t> &GetHorizontalIter();

private:
    void Init();
    void SetUpTmpDir();

private:
    uint32_t m_Width;
    uint32_t m_Height;
    float m_AspectRatio;
    std::vector<uint32_t> m_VerticalIter;
    std::vector<uint32_t> m_HorizontalIter;
    std::string m_TmpDir;
    uint32_t m_Channels = 3;
    uint32_t m_FrameIndex = 1;
};
