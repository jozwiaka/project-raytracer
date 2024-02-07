#include "Math.h"
#include <cmath>
#include <limits>

glm::vec3 Math::Rotate(const glm::vec3 &vec, const glm::vec3 &rotationDeg) noexcept
{
    float yaw = glm::radians(rotationDeg.x);
    float pitch = glm::radians(rotationDeg.y);
    float roll = glm::radians(rotationDeg.z);
    glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, 1, 0));
    glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0));
    glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0, 0, 1));
    glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;
    return glm::vec3(rotationMatrix * glm::vec4(vec, 1.0f));
}

glm::vec3 Math::Translate(const glm::vec3 &vec, const glm::vec3 &translation) noexcept
{
    return vec + translation;
}

glm::vec3 Math::Transform(const glm::vec3 &vec, const glm::vec3 &translation, const glm::vec3 &rotationDeg) noexcept
{
    return Translate(Rotate(vec, rotationDeg), translation);
}

bool Math::IsAlmostEqual(float val1, float val2) noexcept
{
    return std::abs(val1 - val2) < std::numeric_limits<float>::epsilon();
}

bool Math::IsWithinRange(float val, float center, float radius) noexcept
{
    return val >= center - radius && val <= center + radius;
}
