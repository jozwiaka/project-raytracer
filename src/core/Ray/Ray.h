#pragma once
#include <glm/glm.hpp>
class Ray
{
public:
    glm::vec3 Origin, Direction;

public:
    Ray(const glm::vec3 &origin, const glm::vec3 &direction);
};