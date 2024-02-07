#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Forward, Right, Up;

public:
    Camera(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upVector);
    Ray GenerateRay(float x, float y) const;
};