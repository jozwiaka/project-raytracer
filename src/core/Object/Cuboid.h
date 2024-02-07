#pragma once
#include "Object.h"

class Cuboid : public Object
{
public:
    enum class Wall
    {
        XY,
        XYprime,
        YZ,
        YZprime,
        ZX,
        ZXprime
    };

public:
    glm::vec3 Size;

public:
    Cuboid(const glm::vec3 &center, const glm::vec3 &size, const glm::vec3 &rotationDeg, const Material &material);

    bool Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const override;

    bool CheckWall(const Ray &rayLocal, const Wall &wall, const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const;
};