#include "Camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upVector)
    : Position(position),
      Forward(glm::normalize((target - position))),
      Right(glm::normalize(glm::cross(Forward, upVector))),
      Up(glm::normalize(glm::cross(Right, Forward)))

{
}

Ray Camera::GenerateRay(float x, float y) const
{
    glm::vec3 direction = Forward + Right * x + Up * y;
    return Ray(Position, direction);
}