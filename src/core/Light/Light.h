#pragma once
#include "Math.h"

class Light
{
public:
    Math::Vec3 Position;
    Math::Vec3 Color;

public:
    Light(const Math::Vec3 &position, const Math::Vec3 &color);
};