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

    return false;
}
