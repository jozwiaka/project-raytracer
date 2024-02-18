#pragma once
#include "Math.h"
#include "Color.h"

class Light
{
public:
    Math::Vec3 Pos;
    Math::Vec3 Col;

public:
    Light(const Math::Vec3 &position, const Color &color);
};