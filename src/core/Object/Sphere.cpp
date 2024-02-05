#include "Sphere.h"

Sphere::Sphere(const Vec3 &position, float radius, const Material &material)
    : Object(position, material),
      Radius(radius) {}

bool Sphere::Intersect(const Ray &ray, float &t, Vec3 &hitPoint, Vec3 &normal) const
{
    Vec3 oc = ray.Origin - Position; // offset from the sphere's centre to the origin of the ray
    float a = ray.Direction.Dot(ray.Direction);
    float b = 2.0f * oc.Dot(ray.Direction);
    float c = oc.Dot(oc) - Radius * Radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        t = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        hitPoint = ray.Origin + ray.Direction * t;
        normal = (hitPoint - Position).Normalize();

        return true;
    }

    return false;
}
