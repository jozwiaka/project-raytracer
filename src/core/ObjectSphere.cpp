#include "ObjectSphere.h"

ObjectSphere::ObjectSphere(const Vec3 &center, float radius, std::shared_ptr<Material> material)
    : Object(center, Vec3(), material),
      Radius(radius) {}

bool ObjectSphere::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Vec3 oc = ray.Origin - Center;
    float a = Math::Dot(ray.Direction, ray.Direction);
    float half_b = Math::Dot(oc, ray.Direction);
    float c = Math::Dot(oc, oc) - Radius * Radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f)
        return false;

    // Find the nearest root that lies in the acceptable range.
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;
    if (!ray_t.Surrounds(root))
    {
        root = (-half_b + sqrtd) / a;
        if (!ray_t.Surrounds(root))
            return false;
    }

    rec.T = root;
    rec.Point = ray.At(rec.T);
    auto outwardNormal = Math::Normalize(rec.Point - Center);
    rec.SetFaceNormal(ray, outwardNormal);
    rec.Mat = Mat;

    return true;
}
