#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    unsigned int a;
    unsigned int b;
    unsigned int c;

    Cuboid(const Vec3 &center, unsigned int a, unsigned int b, unsigned int c, const Vec3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, Vec3 &hitPoint, Vec3 &normal) const override;
};