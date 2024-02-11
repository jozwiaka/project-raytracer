#pragma once
#include "Math.h"
#include "Ray.h"

class Material
{
public:
    Math::Color3 Color;

public:
    Material() = default;
    Material(const Math::Color3 &color);
    virtual ~Material() = default;
    // virtual bool Scatter(const Ray &ray, const Object &object, Math::Color3 &attenuation, Ray &scattered);
};