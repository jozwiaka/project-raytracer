#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Math
{
public:
    static glm::vec3 Rot(const glm::vec3 &v, const glm::vec3 &rotDeg) noexcept;
};