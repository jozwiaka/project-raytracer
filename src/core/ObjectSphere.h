#pragma once
#include "Object.h"

class ObjectSphere : public Object
{
public:
    float Radius;

public:
    ObjectSphere(const Vec3 &center, float radius, std::shared_ptr<Material> material);

    bool Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const override;
};