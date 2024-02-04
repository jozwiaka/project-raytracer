#pragma once
#include "Vec3.h"
class Light
{
public:
    Vec3 Position;
    Vec3 Color;

public:
    Light(const Vec3 &position, const Vec3 &color);
};