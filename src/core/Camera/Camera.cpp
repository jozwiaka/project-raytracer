#include "Camera.h"

Camera::Camera(const Vec3 &position, const Vec3 &target, const Vec3 &upVector)
    : Position(position),
      Forward((target - position).Normalize()),
      Right(Forward.Cross(upVector).Normalize()),
      Up(Right.Cross(Forward).Normalize())

{
}

Ray Camera::GenerateRay(float x, float y) const
{
    Vec3 direction = Forward + Right * x + Up * y;
    return Ray(Position, direction);
}