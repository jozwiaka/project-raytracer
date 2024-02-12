#include "Cylinder.h"
#include <cmath>
#include <limits>
#include "Math.h"

Cylinder::Cylinder(const Math::Vec3 &center, const float radius, const float height, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material)
    : Object(center, rotationDeg, material),
      m_Radius(radius),
      m_Height(height)
{
}

bool Cylinder::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Ray rayLocal{-Math::Rotate(Math::Translate(ray.Origin, m_Center), -m_RotationDeg), Math::Rotate(ray.Direction, -m_RotationDeg)};
    // (p-C-((p-C)*v)*v)^2.0f=r^2.0f
    // p=P=O+tD
    auto v = Math::Vec3(0.0f, 1.0f, 0.0f);
    auto oc = rayLocal.Origin;
    auto dv = rayLocal.Direction - (v * Math::Dot(rayLocal.Direction, v));
    float a = Math::Dot(dv, dv);
    float b = 2.0f * Math::Dot(oc, dv);
    float c = Math::Dot(oc, oc) - m_Radius * m_Radius;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant >= 0.0f)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float t = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        if (t >= 0.0f)
        {
            Math::Vec3 p = rayLocal.At(t);
            if (Math::IsWithinRange(p.y, 0.0f, m_Height / 2.0f))
            {
                rec.t = t;
                rec.Point = ray.At(rec.t);
                auto outwardNormal = Math::Normalize(rec.Point - m_Center);
                rec.SetFaceNormal(ray, outwardNormal);
                rec.Mat = m_Mat;
                return true;
            }
        }
    }

    return false;
}
