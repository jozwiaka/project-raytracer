#include "Sphere.h"

Sphere::Sphere(const glm::vec3 &center, float radius, const Material &material)
    : Object(center, glm::vec3(), material),
      Radius(radius) {}

bool Sphere::Intersect(const Ray &ray, float &t, glm::vec3 &hitPoint, glm::vec3 &normal) const
{
    glm::vec3 oc = ray.Origin - Center;
    float a = glm::dot(ray.Direction, ray.Direction);
    float b = 2.0f * glm::dot(oc, ray.Direction);
    float c = glm::dot(oc, oc) - Radius * Radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        t = (t1 < t2) ? t1 : t2; // choose smaller value, because it is closer to the ray's origin

        hitPoint = ray.Origin + ray.Direction * t;
        normal = glm::normalize((hitPoint - Center));

        return true;
    }

    return false;
}
