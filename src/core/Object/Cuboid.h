#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    glm::vec3 Size;
    // glm::vec3 Corner;

    Cuboid(const glm::vec3 &center, const glm::vec3 &size, const glm::vec3 &rotationDeg, const Material &material);
    // Cuboid(const glm::vec3 &corner, const glm::vec3 &size, const glm::vec3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const override;
};