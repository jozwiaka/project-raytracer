#include "Sphere.h"

Sphere::Sphere(const Math::Vec3 &center, float radius, std::shared_ptr<Material> material)
    : Object(center, Math::Vec3(), material),
      m_Radius(radius) {}

bool Sphere::Intersect(const Ray &ray, HitRecord &rec) const
{
    Math::Vec3 oc = ray.Origin - m_Center;
    float a = Math::Dot(ray.Direction, ray.Direction);
    float b = 2.0f * Math::Dot(oc, ray.Direction);
    float c = Math::Dot(oc, oc) - m_Radius * m_Radius;
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant >= 0.0f)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float t = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        if (t >= 0.0f)
        {
            rec.t = t;
            rec.Point = ray.At(rec.t);
            auto outwardNormal = (rec.Point - m_Center) / m_Radius;
            rec.SetFaceNormal(ray, outwardNormal);
            rec.Mat = m_Mat;
            return true;
        }
    }

    return false;
}
