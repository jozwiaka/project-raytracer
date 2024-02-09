#pragma once
#include "Math.h"

class Material
{
public:
    Math::Vec3 Color;

public:
    Material() = default;
    Material(const Math::Vec3 &color);
};