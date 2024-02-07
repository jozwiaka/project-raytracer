#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    unsigned int a;
    unsigned int b;
    unsigned int c;

    Cuboid(const glm::vec3 &center, unsigned int a, unsigned int b, unsigned int c, const glm::vec3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const override;
};