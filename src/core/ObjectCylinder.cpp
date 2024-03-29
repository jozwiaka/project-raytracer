#include "ObjectCylinder.h"
#include <cmath>
#include <limits>
#include "Math.h"

ObjectCylinder::ObjectCylinder(const Vec3 &center, float radius, float height, const Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : Object(center, rotationDeg, material),
      Radius(radius),
      Height(height)
{
}

bool ObjectCylinder::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Ray rayLocal{Math::RotateT(Math::Translate(ray.Origin, -Center), -RotationDeg), Math::RotateT(ray.Direction, -RotationDeg)};
    // (p-C-((p-C)*v)*v)^2.0f=r^2.0f
    // p=P=O+tD
    auto v = Vec3(0.0f, 1.0f, 0.0f);
    auto oxz = rayLocal.Origin - (v * Math::Dot(rayLocal.Origin, v));
    auto dxz = rayLocal.Direction - (v * Math::Dot(rayLocal.Direction, v));

    float a = Math::Dot(dxz, dxz);
    float half_b = Math::Dot(oxz, dxz);
    float c = Math::Dot(oxz, oxz) - Radius * Radius;

    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f)
    {
        return false;
    }

    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;
    if (!ray_t.Surrounds(root))
    {
        root = (-half_b + sqrtd) / a;
        if (!ray_t.Surrounds(root))
        {
            return false;
        }
    }
    auto p = rayLocal.At(root);
    if (!Math::IsWithinRange(p.y, 0.0f, Height / 2.0f))
    {
        return false;
    }

    rec.T = root;
    rec.Point = ray.At(rec.T);
    auto outwardNormal = Math::Normalize(rec.Point - Center);
    rec.SetFaceNormal(ray, outwardNormal);
    rec.Mat = Mat;
    return true;
}
