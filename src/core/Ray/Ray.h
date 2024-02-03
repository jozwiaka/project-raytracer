#pragma once
#include "Vec3.h"
class Ray
{
public:
    Vec3 Origin, Direction;

public:
    Ray(const Vec3 &origin, const Vec3 &direction);
};