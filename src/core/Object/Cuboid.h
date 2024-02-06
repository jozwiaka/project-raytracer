#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    Vec3 Center;
    float Radius;

    Cuboid(const Vec3 &center, float radius, const Material &material);

    bool Intersect(const Ray &ray, float &t, Vec3 &hitPoint, Vec3 &normal) const override;
};