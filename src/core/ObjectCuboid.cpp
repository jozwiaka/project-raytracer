#include "ObjectCuboid.h"
#include <cmath>
#include <limits>
#include "Math.h"

ObjectCuboid::ObjectCuboid(const Math::Vec3 &center, const Math::Vec3 &size, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : Object(center, rotationDeg, material),
      m_Size(size)
{
}

bool ObjectCuboid::CheckWall(const Ray &rayLocal, const ObjectCuboid::Wall &wall, const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Math::Vec3 p0;
    Math::Vec3 n;
    bool range1 = false;
    bool range2 = false;

    switch (wall)
    {
    case Wall::XY:
    case Wall::XY_Prime:
        p0 = Math::Vec3(0.0f, 0.0f, (wall == Wall::XY ? 1.0f : -1.0f) * m_Size.z / 2.0f);
        n = Math::Vec3(0.0f, 0.0f, 1.0f);
        break;
    case Wall::YZ:
    case Wall::YZ_Prime:
        p0 = Math::Vec3((wall == Wall::YZ ? 1.0f : -1.0f) * m_Size.x / 2.0f, 0.0f, 0.0f);
        n = Math::Vec3(1.0f, 0.0f, 0.0f);
        break;
    case Wall::ZX:
    case Wall::ZX_Prime:
        p0 = Math::Vec3(0.0f, (wall == Wall::ZX ? 1.0f : -1.0f) * m_Size.y / 2.0f, 0.0f);
        n = Math::Vec3(0.0f, 1.0f, 0.0f);
        break;
    default:
        break;
    }

    float np0 = Math::Dot(n, p0);
    float root = (np0 - Math::Dot(n, rayLocal.Origin)) / Math::Dot(n, rayLocal.Direction);

    if (!ray_t.Surrounds(root))
    {
        return false;
    }

    auto p = rayLocal.At(root);

    switch (wall)
    {
    case Wall::XY:
    case Wall::XY_Prime:
        range1 = Math::IsWithinRange(p.x, 0.0f, m_Size.x / 2.0f);
        range2 = Math::IsWithinRange(p.y, 0.0f, m_Size.y / 2.0f);
        break;
    case Wall::YZ:
    case Wall::YZ_Prime:
        range1 = Math::IsWithinRange(p.y, 0.0f, m_Size.y / 2.0f);
        range2 = Math::IsWithinRange(p.z, 0.0f, m_Size.z / 2.0f);
        break;
    case Wall::ZX:
    case Wall::ZX_Prime:
        range1 = Math::IsWithinRange(p.x, 0.0f, m_Size.x / 2.0f);
        range2 = Math::IsWithinRange(p.z, 0.0f, m_Size.z / 2.0f);
        break;
    default:
        break;
    }

    if (
        range1 &&
        range2)
    {
        rec.t = root;
        rec.Point = ray.At(rec.t);
        auto outwardNormal = Math::Normalize(rec.Point - m_Center); // TODO
        rec.SetFaceNormal(ray, outwardNormal);
        rec.Mat = m_Mat;
        return true;
    }
    return false;
}

bool ObjectCuboid::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Ray rayLocal{Math::RotateT(Math::Translate(ray.Origin, -m_Center), -m_RotationDeg), Math::RotateT(ray.Direction, -m_RotationDeg)};

    for (int i = static_cast<int>(Wall::XY); i <= static_cast<int>(Wall::ZX_Prime); ++i)
    {
        if (CheckWall(rayLocal, static_cast<Wall>(i), ray, ray_t, rec))
        {
            return true;
        }
    }

    return false;
}