#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
    Sphere(const Math::Point3 &center, float radius, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const override;

private:
    float m_Radius;
};