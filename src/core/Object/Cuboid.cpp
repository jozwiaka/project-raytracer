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

bool Cuboid::Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const
{
    Ray rayLocal{Math::Rot(ray.Origin, -RotationDeg), Math::Rot(ray.Direction, -RotationDeg)};
    // xy
    auto p0 = Center + glm::vec3(0, 0, Size.z / 2); // point on the plane
    auto n = glm::vec3(0, 0, 1);                    // normal to the plane
    auto np0 = glm::dot(n, p0);
    t = (np0 - glm::dot(n, rayLocal.Origin)) / glm::dot(n, rayLocal.Direction);
    if (t >= 0)
    {
        glm::vec3 p = rayLocal.Origin + t * rayLocal.Direction;
        if (
            Math::IsAlmostEqual(glm::dot(n, p), np0) &&
            Math::IsWithinRange(p.x, Center.x, Size.x / 2) &&
            Math::IsWithinRange(p.y, Center.y, Size.y / 2))
        {
            hitPoint = Math::Rot(p, RotationDeg);
            normal = glm::normalize((hitPoint - Center));
            return true;
        }
    }
    return false;
}
