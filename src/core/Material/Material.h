#pragma once
#include "Vec3.h"
class Material
{
public:
    Vec3 Color;

public:
    Material() = default;
    Material(const Vec3 &color);
    Material(const Material &other);
};