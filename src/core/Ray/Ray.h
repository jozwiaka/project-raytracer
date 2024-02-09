#pragma once
#include "Math.h"
class Ray
{
public:
    Math::Vec3 Origin, Direction;

public:
    Ray(const Math::Vec3 &origin, const Math::Vec3 &direction);
};