#pragma once

#include "Material.h"
#include "TextureSolidColor.h"
#include <memory>

class MaterialIsotropic : public Material
{
public:
    std::shared_ptr<Texture> Albedo;

public:
    MaterialIsotropic(const Color &c);
    MaterialIsotropic(std::shared_ptr<Texture> a);
    bool Scatter(const Ray &ray, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const override;
};