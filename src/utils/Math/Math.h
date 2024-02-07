#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Math
{
public:
    static glm::vec3 Rotate(const glm::vec3 &vec, const glm::vec3 &rotationDeg) noexcept;
    static glm::vec3 Translate(const glm::vec3 &vec, const glm::vec3 &translation) noexcept;
    static glm::vec3 Transform(const glm::vec3 &vec, const glm::vec3 &translation, const glm::vec3 &rotationDeg) noexcept;
    static bool IsAlmostEqual(float val1, float val2) noexcept;
    static bool IsWithinRange(float val, float center, float radius) noexcept;
};