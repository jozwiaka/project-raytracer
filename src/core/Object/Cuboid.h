#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    enum class Wall
    {
        XY,
        XYprime,
        YZ,
        YZprime,
        ZX,
        ZXprime
    };

public:
    Math::Vec3 Size;

public:
    Cuboid(const Math::Vec3 &center, const Math::Vec3 &size, const Math::Vec3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const override;

    bool CheckWall(const Ray &rayLocal, const Wall &wall, const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const;
};