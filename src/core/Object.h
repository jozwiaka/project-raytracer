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
    Object(const Math::Vec3 &center, const Math::Vec3 &rotationDeg, std::shared_ptr<Material> material);
    virtual ~Object() = default;
    virtual bool Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const = 0;

    Math::Vec3 GetCenter() const;
    void SetCenter(const Math::Vec3 &center);

    Math::Vec3 GetRotationDeg() const;
    void SetRotationDeg(const Math::Vec3 &rotationDeg);

    std::shared_ptr<Material> GetMaterial() const;
    void SetMaterial(const std::shared_ptr<Material> &material);

protected:
    Math::Vec3 m_Center;
    Math::Vec3 m_RotationDeg;
    std::shared_ptr<Material> m_Mat;
};