#include "Metal.h"

Metal::Metal(const Color &albedo, float fuzz) : m_Albedo(albedo), m_Fuzz(fuzz < 1 ? fuzz : 1) {}

bool Metal::Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const
{

    return true;
}
