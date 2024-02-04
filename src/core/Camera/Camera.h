#pragma once

#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
    Vec3 Position;
    Vec3 Forward, Right, Up;

public:
    Camera(const Vec3 &position, const Vec3 &target, const Vec3 &upVector);
    Ray GenerateRay(float x, float y) const;
};