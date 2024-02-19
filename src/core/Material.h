#pragma once
#include "Math.h"
#include "Ray.h"
#include "Color.h"
#include "HitRecord.h"
#include "Texture.h"

class Material
{
public:
    Vec3 Col;

public:
    Material() = default;
    Material(const Color &color);
    virtual ~Material() = default;
    virtual bool Scatter(const Ray &ray, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const = 0;
    virtual Color Emitted(float u, float v, const Vec3 &p) const;
};