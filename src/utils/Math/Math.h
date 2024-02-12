#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <limits>
class Math
{
public:
    using Vec3 = glm::vec3;

public:
    static constexpr float Infinity = std::numeric_limits<float>::infinity();

public:
    // Vector
    static float Dot(const Vec3 &v1, const Vec3 &v2) noexcept;
    static Vec3 Cross(const Vec3 &v1, const Vec3 &v2) noexcept;
    static float Length(const Vec3 &v) noexcept;
    static Vec3 Normalize(const Vec3 &v) noexcept;

    // Transformation
    static Vec3 Rotate(const Vec3 &v, const Vec3 &rotationDeg) noexcept;
    static Vec3 Translate(const Vec3 &v, const Vec3 &translation) noexcept;
    static Vec3 Transform(const Vec3 &v, const Vec3 &translation, const Vec3 &rotationDeg) noexcept;

    // Comparison
    static bool IsAlmostEqual(float val1, float val2) noexcept;
    static bool IsWithinRange(float val, float center, float radius) noexcept;
};