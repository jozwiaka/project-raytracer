#pragma once

#include "Material.h"
#include "Ray.h"
#include "Math.h"
#include <memory>
class Object
{
public:
    Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material);
    virtual ~Object() = default;
    virtual bool Intersect(const Ray &ray, float &t, Math::Vec3 &hitPoint, Math::Vec3 &normal) const = 0;
    std::shared_ptr<Material> GetMaterial();

protected:
    Math::Vec3 m_Center;
    Math::Vec3 m_RotationDeg;
    std::shared_ptr<Material> m_Mat;
};