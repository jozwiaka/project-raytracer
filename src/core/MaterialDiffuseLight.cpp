#include "MaterialDiffuseLight.h"

MaterialDiffuseLight::MaterialDiffuseLight(const Color &c) : Emit(std::make_shared<TextureSolidColor>(c)) {}

bool MaterialDiffuseLight::Scatter(const Ray &ray, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const
{
    return false;
}

Color MaterialDiffuseLight::Emitted(float u, float v, const Vec3 &p) const
{
    return Emit->Value(u, v, p);
}