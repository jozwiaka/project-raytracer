#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
    float Radius;

    Sphere(const Math::Point3 &center, float radius, const Material &material);

    bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const override;
};