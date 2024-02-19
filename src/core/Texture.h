#pragma once

#include "Math.h"
#include "Color.h"

class Texture
{
public:
    virtual Color Value(float u, float v, const Vec3 &p) const = 0;
};