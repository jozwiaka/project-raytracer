#pragma once
#include <glm/glm.hpp>
class Light
{
public:
    glm::vec3 Position;
    glm::vec3 Color;

public:
    Light(const glm::vec3 &position, const glm::vec3 &color);
};