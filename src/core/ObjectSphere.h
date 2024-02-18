#pragma once
#include "Object.h"

class ObjectSphere : public Object
{
public:
    ObjectSphere(const Math::Vec3 &center, float radius, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const override;

    float GetRadius() const;
    void SetRadius(float radius);

private:
    float m_Radius;
};