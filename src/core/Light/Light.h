#pragma once
#include "Math.h"

class Light
{
public:
    Math::Point3 Position;
    Math::Color Color;

public:
    Light(const Math::Point3 &position, const Math::Color &color);
};