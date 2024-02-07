#pragma once
#include "Object.h"

class Cylinder : public Object
{
public:
    float Radius;
    float Height;

public:
    Cylinder(const glm::vec3 &center, const float radius, const float height, const glm::vec3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const override;
};