#pragma once
#include "Math.h"

class Material
{
public:
    Math::Color3 Color;

public:
    Material() = default;
    Material(const Math::Color3 &color);
};