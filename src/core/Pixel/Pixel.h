#pragma once

#include "Color.h"

class Pixel
{
public:
    float x, y;
    Color Col;

public:
    Pixel(float x, float y, const Color &color);
};