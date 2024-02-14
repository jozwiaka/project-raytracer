#include "Camera.h"
#include <cmath>

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, Image *image)
    : m_Pos(position),
      m_Forward(Math::Normalize(position - target)),
      m_Right(Math::Normalize(Math::Cross(upVector, m_Forward))),
      m_Up(Math::Normalize(Math::Cross(m_Forward, m_Right))),
      m_DefocusAngle(defocusAngle),
      m_VerticalFOV(verticalFOV),
      m_Image(image),
      m_FocusDist(Math::Length(target - position))
{
    Init();
}

void Camera::Init()
{
    auto theta = Math::Radians(m_VerticalFOV);
    auto h = std::tan(theta / 2.0f);
    auto viewportHeight = 2.0f * h * m_FocusDist;
    auto viewportWidth = viewportHeight * m_Image->AspectRatioReal;

    Math::Vec3 viewportU = viewportWidth * m_Right;
    Math::Vec3 viewportV = viewportHeight * -m_Up;

    PixelDeltaU = viewportU / static_cast<float>(m_Image->Width);
    PixelDeltaV = viewportV / static_cast<float>(m_Image->Height);

    auto viewportUpperLeft = m_Pos - (m_FocusDist * m_Forward) - viewportU / 2.0f - viewportV / 2.0f;
    Pixel00Loc = viewportUpperLeft + 0.5f * (PixelDeltaU + PixelDeltaV);

    auto defocusRadius = m_FocusDist * std::tan(Math::Radians(m_DefocusAngle / 2.0f));
    DefocusDiskU = m_Right * defocusRadius;
    DefocusDiskV = m_Up * defocusRadius;
}

Ray Camera::GenerateRay(int i, int j) const
{
    auto pixelCenter = Pixel00Loc + (static_cast<float>(i) * PixelDeltaU) + (static_cast<float>(j) * PixelDeltaV);
    auto pixelSample = pixelCenter + PixelSampleSquare();

    auto rayOrigin = (m_DefocusAngle <= 0) ? m_Pos : DefocusDiskSample();
    auto rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}

Math::Vec3 Camera::PixelSampleSquare() const
{
    auto px = -0.5f + Random::RandomFloat();
    auto py = -0.5f + Random::RandomFloat();
    return (px * PixelDeltaU) + (py * PixelDeltaV);
}

Math::Vec3 Camera::PixelSampleDisk(float radius) const
{
    auto p = radius * Random::RandomInUnitDisk();
    return (p.x * PixelDeltaU) + (p.y * PixelDeltaV);
}

Math::Vec3 Camera::DefocusDiskSample() const
{
    auto p = Random::RandomInUnitDisk();
    return m_Pos + (p.x * DefocusDiskU) + (p.y * DefocusDiskV);
}