#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "Math.h"
#include "HitRecord.h"
#include "Interval.h"
#include "Color.h"

class Scene
{
public:
    std::vector<std::unique_ptr<Object>> Objects;
    std::vector<std::unique_ptr<Light>> Lights;

public:
    bool Intersect(const Ray &ray, Interval ray_t, HitRecord &rec) const;
    void SetUpExampleScene();
};