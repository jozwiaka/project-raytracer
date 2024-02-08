#include "Cylinder.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <iostream>
#include "Math.h"

Cylinder::Cylinder(const glm::vec3 &center, const float radius, const float height, const glm::vec3 &rotationDeg, const Material &material)
    : Object(center, rotationDeg, material),
      Radius(radius),
      Height(height)
{
}

bool Cylinder::Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const
{
    Ray rayLocal{-Math::Rotate(Math::Translate(ray.Origin, Center), -RotationDeg), Math::Rotate(ray.Direction, -RotationDeg)};
    // P=O+tD;
    // (p-C-((p-C)*v)*v)^2=r^2
    // p=P
    auto v = glm::vec3(0, 1, 0);
    auto oc = rayLocal.Origin;
    auto dv = rayLocal.Direction - (v * glm::dot(rayLocal.Direction, v));
    float a = glm::dot(dv, dv);
    float b = 2 * glm::dot(oc, dv);
    float c = glm::dot(oc, oc) - Radius * Radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float tSmallerVal = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        if (tSmallerVal >= 0)
        {
            glm::vec3 p = rayLocal.Origin + tSmallerVal * rayLocal.Direction;
            if (Math::IsWithinRange(p.y, 0, Height / 2))
            {
                t = tSmallerVal;
                hitPoint = ray.Origin + ray.Direction * t;
                normal = glm::normalize((hitPoint - Center));
                return true;
            }
        }
    }

    return false;
}
