#include "Cuboid.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <iostream>

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
            std::abs(glm::dot(n, p) - glm::dot(n, p0)) < std::numeric_limits<float>::epsilon() &&
            p.x >= Center.x - Size.x / 2 && p.x <= Center.x + Size.x / 2 &&
            p.y >= Center.y - Size.y / 2 && p.y <= Center.y + Size.y / 2)
        {
            t = t1;
            hitPoint = p;
            normal = glm::normalize((hitPoint - Center));
            return true;
        }
    }

    // if (std::abs(glm::dot(n, d)) < std::numeric_limits<float>::epsilon())
    // {
    //     std::cout << "Ok\n";
    // }

    // // Define a vector
    // glm::vec3 vec(1.0f, 0.0f, 0.0f); // Original vector pointing along the x-axis

    // // Define Euler angles (in radians)
    // float yaw = glm::radians(RotationDeg.x);   // Rotation around the y-axis
    // float pitch = glm::radians(RotationDeg.y); // Rotation around the x-axis
    // float roll = glm::radians(RotationDeg.z);  // Rotation around the z-axis

    // // Create rotation matrices
    // glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, 1, 0));
    // glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0));
    // glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0, 0, 1));

    // // Combine rotation matrices
    // glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;

    // // Transform the vector by the rotation matrix
    // glm::vec4 rotatedVec = rotationMatrix * glm::vec4(vec, 1.0f);

    // t = 1.0;
    // hitPoint = ray.Origin + ray.Direction * t;
    // normal = glm::normalize((hitPoint - Center));

    return false;
}
