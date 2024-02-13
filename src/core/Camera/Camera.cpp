#include "Camera.h"
#include <cmath>

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV)
    : m_Position(position),
      m_Forward(Math::Normalize(target - position)),
      m_Right(Math::Normalize(Math::Cross(m_Forward, upVector))),
      m_Up(Math::Normalize(Math::Cross(m_Right, m_Forward))),
      m_DefocusAngle(defocusAngle),
      m_VerticalFOV(verticalFOV),
      m_FocusDist(Math::Length(target - position))
{
}

Ray Camera::GenerateRay(float x, float y) const
{
    Math::Vec3 direction = m_Forward + m_Right * x + m_Up * y;
    auto defocusOffset = m_DefocusAngle <= 0 ? Math::Vec3() : DefocusDiskSample();
    float scale = 1 - Math::Dot(direction, m_Forward) / (Math::Length(direction) * Math::Length(m_Forward));
    defocusOffset *= scale;
    return Ray(m_Position + defocusOffset, direction - defocusOffset);
}

Math::Vec3 Camera::DefocusDiskSample() const
{
    auto p = Random::RandomInUnitDisk();
    // defAng = 2*arctan(D/2f) = 2*arctan(2*R/2f) => R = f * tan(defAngle/2)
    float defocusRadius = m_FocusDist * std::tan(Math::Radians(m_DefocusAngle / 2));
    Math::Vec3 defocusDiskRight = m_Right * defocusRadius;
    Math::Vec3 defocusDiskUp = m_Up * defocusRadius;

    return p.x * defocusDiskRight + p.y * defocusDiskUp;
}
