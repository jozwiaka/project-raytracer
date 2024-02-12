#pragma once
#include "Object.h"

class Cylinder : public Object
{
public:
    Cylinder(const Math::Vec3 &center, const float radius, const float height, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material);
    bool Intersect(const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const override;

private:
    float m_Radius;
    float m_Height;
};