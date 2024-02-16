#pragma once

#include "Ray.h"
#include "Math.h"
#include <memory>

class Material;

class HitRecord
{
public:
    Math::Vec3 Point;
    Math::Vec3 Normal;
    std::shared_ptr<Material> Mat;
    float t;
    bool FrontFace;

public:
    void SetFaceNormal(const Ray &ray, const Math::Vec3 &outwardNormal);
};