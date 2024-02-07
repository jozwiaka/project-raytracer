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
    // xy
    glm::vec3 p0 = Center + glm::vec3(0, 0, Size.z / 2);
    glm::vec3 n = glm::vec3(0, 0, 1);

    float t1 = (glm::dot(n, p0) - glm::dot(n, ray.Origin)) / glm::dot(n, ray.Direction);
    if (t1 >= 0)
    {
        glm::vec3 p = ray.Origin + t1 * ray.Direction;

        if (
            Math::IsAlmostEqual(glm::dot(n, p), glm::dot(n, p0)) &&
            Math::IsWithinRange(p.x, Center.x, Size.x / 2) &&
            Math::IsWithinRange(p.y, Center.y, Size.y / 2))
        {
            t = t1;
            hitPoint = Math::Rot(p, RotationDeg);
            normal = glm::normalize((hitPoint - Center));

            return true;
        }
    }

    return false;
}
