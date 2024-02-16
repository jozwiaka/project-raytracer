#pragma once
#include "Math.h"
#include "Material.h"
#include "Color.h"
#include "Random.h"

class MaterialMetal : public Material
{
public:
    MaterialMetal(const Color &albedo, float fuzz);
    bool Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const override;

private:
    Color m_Albedo;
    float m_Fuzz;
};