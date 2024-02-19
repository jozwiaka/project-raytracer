#include "MaterialDielectric.h"
#include <cmath>
#include "Random.h"

MaterialDielectric::MaterialDielectric(float indexOfRefraction) : IndexOfRefraction(indexOfRefraction) {}

bool MaterialDielectric::Scatter(const Ray &ray, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const
{
    attenuation = Color(1.0f, 1.0f, 1.0f);
    float refractionRatio = rec.FrontFace ? (1.0f / IndexOfRefraction) : IndexOfRefraction;
    auto unitDirection = Math::Normalize(ray.Direction);
    float cosTheta = std::fmin(Math::Dot(-unitDirection, rec.Normal), 1.0f);
    float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0f;
    Vec3 direction;

    if (cannotRefract || Reflectance(cosTheta, refractionRatio) > Random::RandomFloat())
    {
        direction = Math::Reflect(unitDirection, rec.Normal);
    }
    else
    {
        direction = Math::Refract(unitDirection, rec.Normal, refractionRatio);
    }

    scattered = Ray(rec.Point, direction);
    return true;
}

float MaterialDielectric::Reflectance(float cosine, float refIdx)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
