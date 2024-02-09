#pragma once

#include "Material.h"
#include "Ray.h"
#include "Math.h"

class Object
{
public:
    Math::Point3 Center;
    Math::Rotation3 RotationDeg;
    Material Substance;

public:
    Object(const Math::Point3 &center, const Math::Rotation3 &rotationDeg, const Material &material);
    virtual bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const = 0;
};