#include "Cuboid.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <iostream>
#include "Math.h"

Cuboid::Cuboid(const glm::vec3 &center, const glm::vec3 &size, const glm::vec3 &rotationDeg, const Material &material)
    : Object(center, rotationDeg, material),
      Size(size)
{
}

bool Cuboid::CheckWall(const Ray &rayLocal, const Cuboid::Wall &wall, const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const
{
    glm::vec3 p0;
    glm::vec3 n;
    bool range1 = false;
    bool range2 = false;

    switch (wall)
    {
    case Wall::XY:
    case Wall::XYprime:
        p0 = glm::vec3(0, 0, (wall == Wall::XY ? 1 : -1) * Size.z / 2);
        n = glm::vec3(0, 0, 1);
        break;
    case Wall::YZ:
    case Wall::YZprime:
        p0 = glm::vec3((wall == Wall::YZ ? 1 : -1) * Size.x / 2, 0, 0);
        n = glm::vec3(1, 0, 0);
        break;
    case Wall::ZX:
    case Wall::ZXprime:
        p0 = glm::vec3(0, (wall == Wall::ZX ? 1 : -1) * Size.y / 2, 0);
        n = glm::vec3(0, 1, 0);
        break;
    default:
        break;
    }

    float np0 = glm::dot(n, p0);
    t = (np0 - glm::dot(n, rayLocal.Origin)) / glm::dot(n, rayLocal.Direction);
    if (t >= 0)
    {
        glm::vec3 p = rayLocal.Origin + t * rayLocal.Direction;

        switch (wall)
        {
        case Wall::XY:
        case Wall::XYprime:
            range1 = Math::IsWithinRange(p.x, 0, Size.x / 2);
            range2 = Math::IsWithinRange(p.y, 0, Size.y / 2);
            break;
        case Wall::YZ:
        case Wall::YZprime:
            range1 = Math::IsWithinRange(p.y, 0, Size.y / 2);
            range2 = Math::IsWithinRange(p.z, 0, Size.z / 2);
            break;
        case Wall::ZX:
        case Wall::ZXprime:
            range1 = Math::IsWithinRange(p.x, 0, Size.x / 2);
            range2 = Math::IsWithinRange(p.z, 0, Size.z / 2);
            break;
        default:
            break;
        }

        if (
            Math::IsAlmostEqual(glm::dot(n, p), np0) &&
            range1 &&
            range2)
        {
            hitPoint = ray.Origin + t * ray.Direction;
            normal = glm::normalize((hitPoint - Center));
            return true;
        }
    }
    return false;
}

bool Cuboid::Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const
{
    Ray rayLocal{-Math::Rotate(Math::Translate(ray.Origin, Center), -RotationDeg), Math::Rotate(ray.Direction, -RotationDeg)};

    for (int i = static_cast<int>(Wall::XY); i <= static_cast<int>(Wall::ZXprime); ++i)
    {
        if (CheckWall(rayLocal, static_cast<Wall>(i), ray, t, hitPoint, normal))
        {
            return true;
        }
    }

    return false;
}
