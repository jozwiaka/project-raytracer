#pragma once

#include "Material.h"
#include "TextureSolidColor.h"
#include <memory>

class MaterialDiffuseLight : public Material
{
public:
    std::shared_ptr<Texture> Emit;

public:
    MaterialDiffuseLight(const Color &c);
    bool Scatter(const Ray &ray, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const override;
    Color Emitted(float u, float v, const Vec3 &p) const override;
};