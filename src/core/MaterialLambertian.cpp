#include "MaterialLambertian.h"

MaterialLambertian::MaterialLambertian(const Color &albedo) : Albedo(albedo) {}

bool MaterialLambertian::Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const
{
    auto scatterDirection = rec.Normal + Random::RandomUnitVector();

    if (Math::IsVectorNearZero(scatterDirection))
    {
        scatterDirection = rec.Normal;
    }

    scattered = Ray(rec.Point, scatterDirection);
    attenuation = Albedo;
    return true;
}
