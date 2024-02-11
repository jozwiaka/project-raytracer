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
    Cuboid(const Math::Point3 &center, const Math::Vec3 &size, const Math::Rotation3 &rotationDeg, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const override;

    bool CheckWall(const Ray &rayLocal, const Wall &wall, const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const;

private:
    Math::Vec3 m_Size;
};