#pragma once
#include "Object.h"

class ObjectCuboid : public Object
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
    Vec3 Size;

public:
    ObjectCuboid(const Vec3 &center, const Vec3 &size, const Vec3 &rotationDeg, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const override;

    bool CheckWall(const Ray &rayLocal, const Wall &wall, const Ray &ray, Interval ray_t, HitRecord &rec) const;
};