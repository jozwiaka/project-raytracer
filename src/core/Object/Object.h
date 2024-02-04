#pragma once

#include "Vec3.h"
#include "Material.h"
#include "Ray.h"

class Object
{
public:
    Vec3 Position;
    Material ObjMaterial;

public:
    Object(const Vec3 &position, const Material &material);
    virtual bool Intersect(const Ray &ray, float &t, Vec3 &hitPoint, Vec3 &normal) const = 0;
};