#pragma once
#include "Math.h"

class Light
{
public:
    Math::Point3 Position;
    Math::Color3 Color;

public:
    Light(const Math::Point3 &position, const Math::Color3 &color);
};