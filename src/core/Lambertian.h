#pragma once
#include "Math.h"
#include "Material.h"
#include "Color.h"
#include "Random.h"

class Lambertian : public Material
{
public:
    Lambertian(const Color &albedo);
    bool Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const override;

private:
    Color m_Albedo;
};