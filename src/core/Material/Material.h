#pragma once
#include "Math.h"
#include "Ray.h"
#include "Color.h"
#include "HitRecord.h"

class Material
{
public:
    Math::Vec3 m_Color;

public:
    Material() = default;
    Material(const Color &color);
    virtual ~Material() = default;
    bool Scatter(const Ray &ray, const HitRecord &rec, Math::Vec3 &attenuation, Ray &scattered) const { return false; }
};