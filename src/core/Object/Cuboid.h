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
    Cuboid(const Math::Vec3 &center, const Math::Vec3 &size, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, HitRecord& rec) const override;

    bool CheckWall(const Ray &rayLocal, const Wall &wall, const Ray &ray, HitRecord& rec) const;

private:
    Math::Vec3 m_Size;
};