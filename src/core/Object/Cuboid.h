#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    Vec3 Corner1;
    Vec3 Corner2;

    Cuboid(const Vec3 &corner1, const Vec3 &corner2, const Material &material);

    bool Intersect(const Ray &ray, float &t, Vec3 &hitPoint, Vec3 &normal) const override;
};