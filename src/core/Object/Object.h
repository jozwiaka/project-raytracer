#pragma once

#include <glm/glm.hpp>
#include "Material.h"
#include "Ray.h"

class Object
{
public:
    glm::vec3 Center;
    glm::vec3 RotationDeg;
    Material Substance;

public:
    Object(const glm::vec3 &center, const glm::vec3 &rotationDeg, const Material &material);
    virtual bool Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const = 0;
};