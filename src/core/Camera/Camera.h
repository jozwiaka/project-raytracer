#pragma once

#include "Ray.h"
#include "Math.h"

class Camera
{
public:
    Math::Point3 Position;
    Math::Vec3 Forward, Right, Up;

public:
    Camera(const Math::Point3 &position, const Math::Point3 &target, const Math::Vec3 &upVector);
    Ray GenerateRay(float x, float y) const;
};