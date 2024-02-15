#include "Camera.h"
#include <cmath>

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, Image *image)
    : Pos(position),
      Forward(Math::Normalize(position - target)),
      Right(Math::Normalize(Math::Cross(upVector, Forward))),
      Up(Math::Normalize(Math::Cross(Forward, Right))),
      DefocusAngle(defocusAngle),
      VerticalFOV(verticalFOV),
      FocusDist(focusDist <= 0 ? Math::Length(target - position) : focusDist),
      m_Image(image)
{
    Init();
}

void Camera::Init()
{
    auto theta = Math::Radians(VerticalFOV);
    auto h = std::tan(theta / 2.0f);
    auto viewportHeight = 2.0f * h * FocusDist;
    auto viewportWidth = viewportHeight * m_Image->AspectRatioReal;

    Math::Vec3 viewportRight = viewportWidth * Right;
    Math::Vec3 viewportUp = viewportHeight * -Up;

    m_PixelDeltaRight = viewportRight / static_cast<float>(m_Image->Width);
    m_PixelDeltaUp = viewportUp / static_cast<float>(m_Image->Height);

    auto viewportUpperLeft = Pos - (FocusDist * Forward) - viewportRight / 2.0f - viewportUp / 2.0f;
    m_Pixel00Loc = viewportUpperLeft + 0.5f * (m_PixelDeltaRight + m_PixelDeltaUp);

    auto defocusRadius = FocusDist * std::tan(Math::Radians(DefocusAngle / 2.0f));
    m_DefocusDiskRight = Right * defocusRadius;
    m_DefocusDiskUp = Up * defocusRadius;
}

Ray Camera::GenerateRay(int i, int j) const
{
    auto pixelCenter = m_Pixel00Loc + (static_cast<float>(i) * m_PixelDeltaRight) + (static_cast<float>(j) * m_PixelDeltaUp);
    auto pixelSample = pixelCenter + PixelSampleSquare();

    auto rayOrigin = (DefocusAngle <= 0) ? Pos : DefocusDiskSample();
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
    return Pos + (p.x * m_DefocusDiskRight) + (p.y * m_DefocusDiskUp);
}