#pragma once
#include "Math.h"
#include "Ray.h"

class Object;

class Material
{
public:
    Math::Vec3 Color;

public:
    Material() = default;
    Material(const Math::Vec3 &color);
    virtual ~Material() = default;
    bool Scatter(const Ray &ray, const Object &object, Math::Vec3 &attenuation, Ray &scattered) const { return false; }
};