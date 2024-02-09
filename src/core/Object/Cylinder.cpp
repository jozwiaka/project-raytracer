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
    // (p-C-((p-C)*v)*v)^2=r^2
    // p=P=O+tD
    auto v = Math::Vec3(0, 1, 0);
    auto oc = rayLocal.Origin;
    auto dv = rayLocal.Direction - (v * Math::Dot(rayLocal.Direction, v));
    float a = Math::Dot(dv, dv);
    float b = 2 * Math::Dot(oc, dv);
    float c = Math::Dot(oc, oc) - Radius * Radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float tSmallerVal = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        if (tSmallerVal >= 0)
        {
            Math::Point3 p = rayLocal.At(tSmallerVal);
            if (Math::IsWithinRange(p.y, 0, Height / 2))
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
