#pragma once
#include "Math.h"
#include "Material.h"
#include "Color.h"
#include "Random.h"

class Dielectric : public Material
{
public:
    Dielectric(float indexOfRefraction);
    bool Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const override;

private:
    float m_IndexOfRefraction;

private:
    static float Reflectance(float cosine, float refIdx);
};