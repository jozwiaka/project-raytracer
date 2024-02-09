#include "Cuboid.h"
#include <cmath>
#include <limits>
#include <iostream>
#include "Math.h"

Cuboid::Cuboid(const Math::Vec3 &center, const Math::Vec3 &size, const Math::Vec3 &rotationDeg, const Material &material)
    : Object(center, rotationDeg, material),
      Size(size)
{
}

bool Cuboid::CheckWall(const Ray &rayLocal, const Cuboid::Wall &wall, const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const
{
    Math::Vec3 p0;
    Math::Vec3 n;
    bool range1 = false;
    bool range2 = false;

    switch (wall)
    {
    case Wall::XY:
    case Wall::XYprime:
        p0 = Math::Vec3(0, 0, (wall == Wall::XY ? 1 : -1) * Size.z / 2);
        n = Math::Vec3(0, 0, 1);
        break;
    case Wall::YZ:
    case Wall::YZprime:
        p0 = Math::Vec3((wall == Wall::YZ ? 1 : -1) * Size.x / 2, 0, 0);
        n = Math::Vec3(1, 0, 0);
        break;
    case Wall::ZX:
    case Wall::ZXprime:
        p0 = Math::Vec3(0, (wall == Wall::ZX ? 1 : -1) * Size.y / 2, 0);
        n = Math::Vec3(0, 1, 0);
        break;
    default:
        break;
    }

    float np0 = Math::Dot(n, p0);
    t = (np0 - Math::Dot(n, rayLocal.Origin)) / Math::Dot(n, rayLocal.Direction);
    if (t >= 0)
    {
        Math::Vec3 p = rayLocal.Origin + t * rayLocal.Direction;

        switch (wall)
        {
        case Wall::XY:
        case Wall::XYprime:
            range1 = Math::IsWithinRange(p.x, 0, Size.x / 2);
            range2 = Math::IsWithinRange(p.y, 0, Size.y / 2);
            break;
        case Wall::YZ:
        case Wall::YZprime:
            range1 = Math::IsWithinRange(p.y, 0, Size.y / 2);
            range2 = Math::IsWithinRange(p.z, 0, Size.z / 2);
            break;
        case Wall::ZX:
        case Wall::ZXprime:
            range1 = Math::IsWithinRange(p.x, 0, Size.x / 2);
            range2 = Math::IsWithinRange(p.z, 0, Size.z / 2);
            break;
        default:
            break;
        }

        if (
            Math::IsAlmostEqual(Math::Dot(n, p), np0) &&
            range1 &&
            range2)
        {
            hitPoint = ray.Origin + t * ray.Direction;
            normal = Math::Normalize((hitPoint - Center));
            return true;
        }
    }
    return false;
}

bool Cuboid::Intersect(const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const
{
    Ray rayLocal{-Math::Rotate(Math::Translate(ray.Origin, Center), -RotationDeg), Math::Rotate(ray.Direction, -RotationDeg)};

    for (int i = static_cast<int>(Wall::XY); i <= static_cast<int>(Wall::ZXprime); ++i)
    {
        if (CheckWall(rayLocal, static_cast<Wall>(i), ray, t, hitPoint, normal))
        {
            return true;
        }
    }

    return false;
}
