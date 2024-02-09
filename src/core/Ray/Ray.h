#pragma once
#include "Math.h"
class Ray
{
public:
    Math::Point3 Origin;
    Math::Vec3 Direction;

public:
    Ray(const Math::Point3 &origin, const Math::Vec3 &direction);
};