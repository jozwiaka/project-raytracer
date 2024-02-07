#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
    float Radius;

    Sphere(const glm::vec3 &center, float radius, const Material &material);

    bool Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const override;
};