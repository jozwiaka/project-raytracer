#include "Cylinder.h"
#include <cmath>
#include <limits>
#include <iostream>
#include "Math.h"

Cylinder::Cylinder(const Math::Point3 &center, const float radius, const float height, const Math::Rotation3 &rotationDeg, const Material &material)
    : Object(center, rotationDeg, material),
      Radius(radius),
      Height(height)
{
}

bool Cylinder::Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const
{
    Ray rayLocal{-Math::Rotate(Math::Translate(ray.Origin, Center), -RotationDeg), Math::Rotate(ray.Direction, -RotationDeg)};
    // (p-C-((p-C)*v)*v)^2.0f=r^2.0f
    // p=P=O+tD
    auto v = Math::Vec3(0.0f, 1.0f, 0.0f);
    auto oc = rayLocal.Origin;
    auto dv = rayLocal.Direction - (v * Math::Dot(rayLocal.Direction, v));
    float a = Math::Dot(dv, dv);
    float b = 2.0f * Math::Dot(oc, dv);
    float c = Math::Dot(oc, oc) - Radius * Radius;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant >= 0.0f)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float tSmallerVal = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        if (tSmallerVal >= 0.0f)
        {
            Math::Point3 p = rayLocal.At(tSmallerVal);
            if (Math::IsWithinRange(p.y, 0.0f, Height / 2.0f))
            {
                t = tSmallerVal;
                hitPoint = ray.At(t);
                normal = Math::Normalize((hitPoint - Center));
                return true;
            }
        }
    }

    return false;
}
