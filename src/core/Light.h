#pragma once
#include "Math.h"
#include "Color.h"

class Light
{
public:
    Vec3 Pos;
    Vec3 Col;

public:
    Light(const Vec3 &position, const Color &color);
};