#include "Camera.h"
#include <cmath>

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, Image *image)
    : m_Pos(position),
      m_Forward(Math::Normalize(position - target)),
      m_Right(Math::Normalize(Math::Cross(upVector, m_Forward))),
      m_Up(Math::Normalize(Math::Cross(m_Forward, m_Right))),
      m_DefocusAngle(defocusAngle),
      m_VerticalFOV(verticalFOV),
      m_FocusDist(focusDist <= 0 ? Math::Length(target - position) : focusDist),
      m_Image(image)
{
    Init();
}

void Camera::Init()
{
    auto theta = Math::Radians(m_VerticalFOV);
    auto h = std::tan(theta / 2.0f);
    auto viewportHeight = 2.0f * h * m_FocusDist;
    auto viewportWidth = viewportHeight * m_Image->AspectRatioReal;

    Math::Vec3 viewportRight = viewportWidth * m_Right;
    Math::Vec3 viewportUp = viewportHeight * -m_Up;

    m_PixelDeltaRight = viewportRight / static_cast<float>(m_Image->Width);
    m_PixelDeltaUp = viewportUp / static_cast<float>(m_Image->Height);

    auto viewportUpperLeft = m_Pos - (m_FocusDist * m_Forward) - viewportRight / 2.0f - viewportUp / 2.0f;
    m_Pixel00Loc = viewportUpperLeft + 0.5f * (m_PixelDeltaRight + m_PixelDeltaUp);

    auto defocusRadius = m_FocusDist * std::tan(Math::Radians(m_DefocusAngle / 2.0f));
    m_DefocusDiskRight = m_Right * defocusRadius;
    m_DefocusDiskUp = m_Up * defocusRadius;
}

Ray Camera::GenerateRay(int i, int j) const
{
    auto pixelCenter = m_Pixel00Loc + (static_cast<float>(i) * m_PixelDeltaRight) + (static_cast<float>(j) * m_PixelDeltaUp);
    auto pixelSample = pixelCenter + PixelSampleSquare();

    auto rayOrigin = (m_DefocusAngle <= 0) ? m_Pos : DefocusDiskSample();
    auto rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}

Math::Vec3 Camera::PixelSampleSquare() const
{
    auto px = -0.5f + Random::RandomFloat();
    auto py = -0.5f + Random::RandomFloat();
    return (px * m_PixelDeltaRight) + (py * m_PixelDeltaUp);
}

Math::Vec3 Camera::PixelSampleDisk(float radius) const
{
    auto p = radius * Random::RandomInUnitDisk();
    return (p.x * m_PixelDeltaRight) + (p.y * m_PixelDeltaUp);
}

Math::Vec3 Camera::DefocusDiskSample() const
{
    auto p = Random::RandomInUnitDisk();
    return m_Pos + (p.x * m_DefocusDiskRight) + (p.y * m_DefocusDiskUp);
}