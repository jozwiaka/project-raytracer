#pragma once
#include "Object.h"

class ObjectCylinder : public Object
{
public:
    ObjectCylinder(const Math::Vec3 &center, float radius, float height, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material);
    bool Intersect(const Ray &ray, Interval ray_t, HitRecord& rec) const override;

private:
    float m_Radius;
    float GetHeight();
};