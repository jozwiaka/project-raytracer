#include "ObjectSphere.h"

ObjectSphere::ObjectSphere(const Math::Vec3 &center, float radius, std::shared_ptr<Material> material)
    : Object(center, Math::Vec3(), material),
      m_Radius(radius) {}

bool ObjectSphere::Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    Math::Vec3 oc = ray.Origin - m_Center;
    float a = Math::Dot(ray.Direction, ray.Direction);
    float half_b = Math::Dot(oc, ray.Direction);
    float c = Math::Dot(oc, oc) - m_Radius * m_Radius;
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

    rec.t = root;
    rec.Point = ray.At(rec.t);
    auto outwardNormal = Math::Normalize(rec.Point - m_Center);
    rec.SetFaceNormal(ray, outwardNormal);
    rec.Mat = m_Mat;

    return true;
}
