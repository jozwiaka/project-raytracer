#pragma once
#include <glm/glm.hpp>
class Material
{
public:
    glm::vec3 Color;

public:
    Material() = default;
    Material(const glm::vec3 &color);
};