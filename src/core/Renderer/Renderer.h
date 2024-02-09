#pragma once

#include "Math.h"

class Renderer
{
public:
    static const int Width = 1200;
    static const int Height = static_cast<int>(Width / (16.0f / 9.0f));

public:
    static void Display();
    static void Init();
};