#pragma once

#include "Ray.h"
#include "Math.h"
#include <memory>

class Material;

class HitRecord
{
public:
    Vec3 Point;
    Vec3 Normal;
    std::shared_ptr<Material> Mat;
    float T;
    float U;
    float V;
    bool FrontFace;

public:
    void SetFaceNormal(const Ray &ray, const Vec3 &outwardNormal);
};