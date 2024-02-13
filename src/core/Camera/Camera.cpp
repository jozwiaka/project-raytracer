#include "Camera.h"
#include <cmath>

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle)
    : m_Position(position),
      m_Forward(Math::Normalize(target - position)),
      m_Right(Math::Normalize(Math::Cross(m_Forward, upVector))),
      m_Up(Math::Normalize(Math::Cross(m_Right, m_Forward))),
      m_DefocusAngle(Math::Radians(defocusAngle))

{
}

Ray Camera::GenerateRay(float x, float y) const
{
    auto defocusOffset = m_DefocusAngle <= 0 ? Math::Vec3() : DefocusDiskSample();
    Math::Vec3 direction = m_Forward + m_Right * x + m_Up * y;
    return Ray(m_Position + defocusOffset, direction);
}

Math::Vec3 Camera::DefocusDiskSample() const
{
    auto p = Random::RandomInUnitDisk();

    return p * m_DefocusAngle;
}
