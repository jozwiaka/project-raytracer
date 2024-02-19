#pragma once

#include "Material.h"
#include "Ray.h"
#include "Math.h"
#include <memory>
#include "HitRecord.h"
#include "Interval.h"

class Object
{
public:
    Vec3 Center;
    Vec3 RotationDeg;
    std::shared_ptr<Material> Mat;

public:
    Object(const Vec3 &center, const Vec3 &rotationDeg, std::shared_ptr<Material> material);
    virtual ~Object() = default;
    virtual bool Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const = 0;
};