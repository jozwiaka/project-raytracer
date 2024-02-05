#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Ray.h"
#include "Vec3.h"
#include "Material.h"
class Scene
{
public:
    std::vector<std::unique_ptr<Object>> Objects;

public:
    void AddObject(std::unique_ptr<Object> object);
    bool Intersect(const Ray &ray, Vec3 &hitPoint, Vec3 &normal, Material &material) const;
};