#include "Cuboid.h"
#include <cmath>

Cuboid::Cuboid(const glm::vec3 &center, unsigned int a, unsigned int b, unsigned int c, const glm::vec3 &rotationDeg, const Material &material)
    : Object(center, rotationDeg, material),
      a(a),
      b(b),
      c(c)
{
}

bool Cuboid::Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const
{
    // ab
    // bc
    // ca
    // ab'
    // bc'
    // ca'

    return false;
}
