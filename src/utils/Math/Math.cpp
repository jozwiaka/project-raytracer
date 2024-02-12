#include "Math.h"
#include <cmath>
#include <limits>

float Math::Infinity() noexcept
{
    return std::numeric_limits<float>::infinity();
}

float Math::Epsilon() noexcept
{
    return std::numeric_limits<float>::epsilon();
}

float Math::Dot(const Vec3 &v1, const Vec3 &v2) noexcept
{
    return glm::dot(v1, v2);
}

Math::Vec3 Math::Cross(const Vec3 &v1, const Vec3 &v2) noexcept
{
    return glm::cross(v1, v2);
}

float Math::Length(const Vec3 &v) noexcept
{
    return glm::length(v);
}

Math::Vec3 Math::Normalize(const Vec3 &v) noexcept
{
    return glm::normalize(v);
}

Math::Vec3 Math::Rotate(const Vec3 &v, const Vec3 &rotationDeg) noexcept
{
    float roll = glm::radians(rotationDeg.x);
    float pitch = glm::radians(rotationDeg.y);
    float yaw = glm::radians(rotationDeg.z);
    glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), roll, Vec3(1, 0, 0));
    glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, Vec3(0, 1, 0));
    glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), yaw, Vec3(0, 0, 1));
    glm::mat4 rotationMatrix = rollMatrix * pitchMatrix * yawMatrix;
    return Vec3(rotationMatrix * glm::vec4(v, 1.0f));
}

Math::Vec3 Math::RotateT(const Vec3 &v, const Vec3 &rotationDeg) noexcept
{
    float roll = glm::radians(-rotationDeg.x);
    float pitch = glm::radians(-rotationDeg.y);
    float yaw = glm::radians(-rotationDeg.z);
    glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), roll, Vec3(1, 0, 0));
    glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, Vec3(0, 1, 0));
    glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), yaw, Vec3(0, 0, 1));
    glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;
    return Vec3(rotationMatrix * glm::vec4(v, 1.0f));
}

Math::Vec3 Math::Translate(const Vec3 &v, const Vec3 &translation) noexcept
{
    return v + translation;
}

bool Math::IsVectorNearZero(const Vec3 &v) noexcept
{
    return (std::fabs(v.x) < Epsilon()) && (std::fabs(v.y) < Epsilon()) && (std::fabs(v.z) < Epsilon());
}

bool Math::IsAlmostEqual(float val1, float val2) noexcept
{
    return std::fabs(val1 - val2) < Epsilon();
}

bool Math::IsWithinRange(float val, float center, float radius) noexcept
{
    return val >= center - radius && val <= center + radius;
}

Math::Vec3 Math::Reflect(const Vec3 &v, const Vec3 &n) noexcept
{
    return v - 2 * Dot(v, n) * n;
}

Math::Vec3 Math::Refract(const Vec3 &uv, const Vec3 &n, float etaiOverEtat) noexcept
{
    float cosTheta = std::fmin(Dot(-uv, n), 1.0f);
    Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
    Vec3 rOutParallel = -std::sqrt(std::fabs(1.0f - Dot(rOutPerp, rOutPerp))) * n;
    return rOutPerp + rOutParallel;
}
