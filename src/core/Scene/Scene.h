#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "Math.h"
#include "HitRecord.h"

class Scene
{
public:
    std::vector<std::unique_ptr<Object>> Objects;
    std::vector<std::unique_ptr<Light>> Lights;
    Math::Vec3 BackgroundColor;

public:
    void AddObject(std::unique_ptr<Object> object);
    void AddLight(std::unique_ptr<Light> light);
    bool Intersect(const Ray &ray, HitRecord &rec) const;
};