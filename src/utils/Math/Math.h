#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Math
{
public:
    static glm::vec3 Rot(const glm::vec3 &vec, const glm::vec3 &rotationDeg) noexcept;
    static bool IsAlmostEqual(float val1, float val2) noexcept;
};