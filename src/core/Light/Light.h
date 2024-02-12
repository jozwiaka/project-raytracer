#pragma once
#include "Math.h"
#include "Color.h"

class Light
{
public:
    Math::Vec3 Position;
    Math::Vec3 m_Color;

public:
    Light(const Math::Vec3 &position, const Color &color);
};