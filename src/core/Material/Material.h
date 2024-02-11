#pragma once
#include "Math.h"
#include "Ray.h"

class Object;

class Material
{
public:
    Math::Color Color;

public:
    Material() = default;
    Material(const Math::Color &color);
    virtual ~Material() = default;
    bool Scatter(const Ray &ray, const Object &object, Math::Color &attenuation, Ray &scattered) const { return false; }
};