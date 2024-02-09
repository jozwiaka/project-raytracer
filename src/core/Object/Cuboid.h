#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    enum class Wall
    {
        XY,
        XY_Prime,
        YZ,
        YZ_Prime,
        ZX,
        ZX_Prime
    };

public:
    Math::Vec3 Size;

public:
    Cuboid(const Math::Point3 &center, const Math::Vec3 &size, const Math::Rotation3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const override;

    bool CheckWall(const Ray &rayLocal, const Wall &wall, const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const;
};