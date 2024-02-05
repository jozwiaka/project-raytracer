#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Ray.h"
#include "Vec3.h"
#include "Material.h"
#include "Light.h"
class Scene
{
public:
    std::vector<std::unique_ptr<Object>> Objects;
    std::vector<std::unique_ptr<Light>> Lights;

public:
    void AddObject(std::unique_ptr<Object> object);
    void AddLight(std::unique_ptr<Light> light);
    bool Intersect(const Ray &ray, Vec3 &hitPoint, Vec3 &normal, Material &material) const;
};