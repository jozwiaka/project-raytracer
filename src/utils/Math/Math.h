#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Math
{
public:
    using Vec3 = glm::vec3;
    using Point3 = glm::vec3;
    using Rotation3 = glm::vec3;
    using Color3 = glm::vec3;

public:
    static float Dot(const glm::vec3 &v1, const glm::vec3 &v2) noexcept;
    static glm::vec3 Cross(const glm::vec3 &v1, const glm::vec3 &v2) noexcept;
    static float Length(const glm::vec3 &v) noexcept;
    static glm::vec3 Normalize(const glm::vec3 &v) noexcept;
    static glm::vec3 Rotate(const glm::vec3 &v, const glm::vec3 &rotationDeg) noexcept;
    static glm::vec3 Translate(const glm::vec3 &v, const glm::vec3 &translation) noexcept;
    static glm::vec3 Transform(const glm::vec3 &v, const glm::vec3 &translation, const glm::vec3 &rotationDeg) noexcept;
    static bool IsAlmostEqual(float val1, float val2) noexcept;
    static bool IsWithinRange(float val, float center, float radius) noexcept;
    // static float GenerateRandomNumber() noexcept;
};