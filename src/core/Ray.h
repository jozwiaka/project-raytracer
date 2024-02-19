#pragma once
#include "Math.h"
class Ray
{
public:
    Vec3 Origin;
    Vec3 Direction;

public:
    Ray() = default;
    Ray(const Vec3 &origin, const Vec3 &direction);
    Vec3 At(float t) const;
};