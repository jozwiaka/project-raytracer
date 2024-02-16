#include "MaterialMetal.h"

MaterialMetal::MaterialMetal(const Color &albedo, float fuzz) : m_Albedo(albedo), m_Fuzz(fuzz < 1 ? fuzz : 1) {}

bool MaterialMetal::Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const
{
    auto reflected = Math::Reflect(Math::Normalize(ray.Direction), rec.Normal);
    scattered = Ray(rec.Point, reflected + m_Fuzz * Random::RandomInUnitSphere());
    attenuation = m_Albedo;
    return (Math::Dot(scattered.Direction, rec.Normal) > 0);
}
