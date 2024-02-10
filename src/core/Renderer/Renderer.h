#pragma once

#include "Math.h"

class Renderer
{
public:
    static constexpr float AspectRatioIdeal = 16.0f / 9.0f;
    static constexpr int Width = 1200;
    static constexpr int Height = static_cast<int>(Width / AspectRatioIdeal);
    static constexpr float AspectRatioReal = static_cast<float>(Width) / static_cast<float>(Height);

public:
    static void Display();
    static void Init();
};