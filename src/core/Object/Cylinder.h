#pragma once
#include "Object.h"

class Cylinder : public Object
{
public:
    float Radius;
    float Height;

public:
    Cylinder(const Math::Point3 &center, const float radius, const float height, const Math::Rotation3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const override;
};