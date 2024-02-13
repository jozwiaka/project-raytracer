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
    static float Infinity() noexcept;
    static float Epsilon() noexcept;
    static float Pi() noexcept;

    static float Dot(const Vec3 &v1, const Vec3 &v2) noexcept;
    static Vec3 Cross(const Vec3 &v1, const Vec3 &v2) noexcept;
    static float Length(const Vec3 &v) noexcept;
    static Vec3 Normalize(const Vec3 &v) noexcept;

    static Vec3 Rotate(const Vec3 &v, const Vec3 &rotationDeg) noexcept;
    static Vec3 RotateT(const Vec3 &v, const Vec3 &rotationDeg) noexcept;
    static Vec3 Translate(const Vec3 &v, const Vec3 &translation) noexcept;

    static bool IsVectorNearZero(const Vec3 &v) noexcept;
    static bool IsAlmostEqual(float val1, float val2) noexcept;
    static bool IsWithinRange(float val, float center, float radius) noexcept;

    static Vec3 Reflect(const Vec3 &v, const Vec3 &n) noexcept;
    static Vec3 Refract(const Vec3 &uv, const Vec3 &n, float etaiOverEtat) noexcept;

    static float Radians(float angle) noexcept;
};