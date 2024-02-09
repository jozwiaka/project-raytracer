#include "Camera.h"

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector)
    : Position(position),
      Forward(Math::Normalize((target - position))),
      Right(Math::Normalize(Math::Cross(Forward, upVector))),
      Up(Math::Normalize(Math::Cross(Right, Forward)))

{
}

Ray Camera::GenerateRay(float x, float y) const
{
    Math::Vec3 direction = Forward + Right * x + Up * y;
    return Ray(Position, direction);
}