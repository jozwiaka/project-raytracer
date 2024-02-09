#include "Sphere.h"

Sphere::Sphere(const Math::Vec3 &center, float radius, const Material &material)
    : Object(center, Math::Vec3(), material),
      Radius(radius) {}

bool Sphere::Intersect(const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const
{
    Math::Vec3 oc = ray.Origin - Center;
    float a = Math::Dot(ray.Direction, ray.Direction);
    float b = 2.0f * Math::Dot(oc, ray.Direction);
    float c = Math::Dot(oc, oc) - Radius * Radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float tSmallerVal = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        if (tSmallerVal >= 0)
        {
            t = tSmallerVal;
            hitPoint = ray.Origin + ray.Direction * t;
            normal = Math::Normalize((hitPoint - Center));
            return true;
        }
    }

    return false;
}
