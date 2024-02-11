#pragma once

#include "Material.h"
#include "Ray.h"
#include "Math.h"
#include <memory>
class Object
{
public:
    Object(const Math::Point3 &center, const Math::Rotation3 &rotationDeg, std::shared_ptr<Material> material);
    virtual ~Object() = default;
    virtual bool Intersect(const Ray &ray, float &t, Math::Point3 &hitPoint, Math::Vec3 &normal) const = 0;
    std::shared_ptr<Material> GetMaterial();

protected:
    Math::Point3 m_Center;
    Math::Rotation3 m_RotationDeg;
    std::shared_ptr<Material> m_Material;
};