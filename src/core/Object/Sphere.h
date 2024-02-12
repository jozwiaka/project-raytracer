#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
    Sphere(const Math::Vec3 &center, float radius, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, HitRecord &rec) const override;

private:
    float m_Radius;
};