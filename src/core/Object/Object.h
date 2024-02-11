#pragma once

#include "Material.h"
#include "Ray.h"
#include "Math.h"
#include <memory>
class Object
{
public:
    Math::Point3 Center;
    Math::Rotation3 RotationDeg;
    std::shared_ptr<Material> Mat;

public:
    Object(const Math::Point3 &center, const Math::Rotation3 &rotationDeg, std::shared_ptr<Material> material);
    virtual ~Object() = default;
    virtual bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const = 0;
};