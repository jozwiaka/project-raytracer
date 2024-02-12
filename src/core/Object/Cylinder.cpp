#include "Cylinder.h"
#include <cmath>
#include <limits>
#include "Math.h"

Cylinder::Cylinder(const Math::Vec3 &center, float radius, float height, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : Object(center, rotationDeg, material),
      m_Radius(radius),
      m_Height(height)
{
}

bool Cylinder::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Ray rayLocal{Math::RotateT(Math::Translate(ray.Origin, -m_Center), -m_RotationDeg), Math::RotateT(ray.Direction, -m_RotationDeg)};
    // (p-C-((p-C)*v)*v)^2.0f=r^2.0f
    // p=P=O+tD
    auto v = Math::Vec3(0.0f, 1.0f, 0.0f);
    auto oc = rayLocal.Origin;
    auto dv = rayLocal.Direction - (v * Math::Dot(rayLocal.Direction, v));
    float a = Math::Dot(dv, dv);
    float half_b = Math::Dot(oc, dv);
    float c = Math::Dot(oc, oc) - m_Radius * m_Radius;

    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f)
    {
        return false;
    }

    // Find the nearest root that lies in the acceptable range.
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
    if (!Math::IsWithinRange(p.y, 0.0f, m_Height / 2.0f))
    {
        return false;
    }

    rec.t = root;
    rec.Point = ray.At(rec.t);
    auto outwardNormal = Math::Normalize(rec.Point - m_Center);
    rec.SetFaceNormal(ray, outwardNormal);
    rec.Mat = m_Mat;
    return true;
}
