#pragma once

#include "Material.h"
#include "Ray.h"
#include "Math.h"

class Object
{
public:
    Math::Vec3 Center;
    Math::Vec3 RotationDeg;
    Material Substance;

public:
    Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, const Material &material);
    virtual bool Intersect(const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const = 0;
};