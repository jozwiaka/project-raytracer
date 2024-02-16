#pragma once
#include "Math.h"
#include "Material.h"
#include "Color.h"
#include "Random.h"

class MaterialLambertian : public Material
{
public:
    MaterialLambertian(const Color &albedo);
    bool Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const override;

private:
    Color m_Albedo;
};