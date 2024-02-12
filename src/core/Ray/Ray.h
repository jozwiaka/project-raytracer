#pragma once
#include "Math.h"
class Ray
{
public:
    Math::Vec3 Origin;
    Math::Vec3 Direction;

public:
    Ray(const Math::Vec3 &origin, const Math::Vec3 &direction);
    Math::Vec3 At(float t) const;
};