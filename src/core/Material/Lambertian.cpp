#include "Lambertian.h"

Lambertian::Lambertian(const Color &albedo) : m_Albedo(albedo) {}

bool Lambertian::Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const
{
    auto scatterDirection = rec.Normal + Random::RandomUnitVector();

    if (Math::IsVectorNearZero(scatterDirection))
    {
        scatterDirection = rec.Normal;
    }

    scattered = Ray(rec.Point, scatterDirection);
    attenuation = m_Albedo;
    return true;
}
