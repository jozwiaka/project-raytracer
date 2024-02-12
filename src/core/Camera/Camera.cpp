#include "Camera.h"

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector)
    : m_Position(position),
      m_Forward(Math::Normalize(target - position)),
      m_Right(Math::Normalize(Math::Cross(m_Forward, upVector))),
      m_Up(Math::Normalize(Math::Cross(m_Right, m_Forward)))

{
}

Ray Camera::GenerateRay(float x, float y) const
{
    Math::Vec3 direction = m_Forward + m_Right * x + m_Up * y;
    return Ray(m_Position, direction);
}