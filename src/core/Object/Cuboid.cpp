#include "Cuboid.h"

Cuboid::Cuboid(const Vec3 &corner1, const Vec3 &corner2, const Material &material)
    : Object(material),
      Corner1(corner1),
      Corner2(corner2)
{
}

bool Cuboid::Intersect(const Ray &ray, float &t, Vec3 &hitPoint, Vec3 &normal) const
{

    // Vec3 oc = ray.Origin - Center;
    // float a = ray.Direction.Dot(ray.Direction);
    // float b = 2.0f * oc.Dot(ray.Direction);
    // float c = oc.Dot(oc) - Radius * Radius;
    // float discriminant = b * b - 4 * a * c;

    // if (discriminant > 0)
    // {
    //     float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
    //     float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
    //     t = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

    //     hitPoint = ray.Origin + ray.Direction * t;
    //     normal = (hitPoint - Center).Normalize();

    //     return true;
    // }

    return false;
}
