#include "Camera.h"
#include <cmath>

Camera::Camera(const Vec3 &position, const Vec3 &target, const Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, std::shared_ptr<Image> image)
    : Pos(position),
      Target(target),
      UpVector(upVector),
      DefocusAngle(defocusAngle),
      VerticalFOV(verticalFOV),
      FocusDist(focusDist <= 0 ? Math::Length(target - Pos) : focusDist),
      Img(image)
{
    Init();
}

void Camera::Init()
{
    m_W = Math::Normalize(Pos - Target);
    m_U = Math::Normalize(Math::Cross(UpVector, m_W));
    m_V = Math::Normalize(Math::Cross(m_W, m_U));

    auto theta = Math::Radians(VerticalFOV);
    auto h = std::tan(theta / 2.0f);
    auto viewportHeight = 2.0f * h * FocusDist;
    auto viewportWidth = viewportHeight * Img->GetAspectRatio();

    Vec3 viewportU = viewportWidth * m_U;
    Vec3 viewportV = viewportHeight * -m_V;

    m_PixelDeltaU = viewportU / static_cast<float>(Img->GetWidth());
    m_PixelDeltaV = viewportV / static_cast<float>(Img->GetHeight());

    auto viewportVperLeft = Pos - (FocusDist * m_W) - viewportU / 2.0f - viewportV / 2.0f;
    m_Pixel00Loc = viewportVperLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

    auto defocusRadius = FocusDist * std::tan(Math::Radians(DefocusAngle / 2.0f));
    m_DefocusDiskU = m_U * defocusRadius;
    m_DefocusDiskV = m_V * defocusRadius;
}

Ray Camera::GenerateRay(uint32_t i, uint32_t j) const
{
    auto pixelCenter = m_Pixel00Loc + (static_cast<float>(i) * m_PixelDeltaU) + (static_cast<float>(j) * m_PixelDeltaV);
    auto pixelSample = pixelCenter + PixelSampleSquare();

    auto rayOrigin = (DefocusAngle <= 0) ? Pos : DefocusDiskSample();
    auto rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}

Vec3 Camera::PixelSampleSquare() const
{
    auto px = -0.5f + Random::RandomFloat();
    auto py = -0.5f + Random::RandomFloat();
    return (px * m_PixelDeltaU) + (py * m_PixelDeltaV);
}

Vec3 Camera::PixelSampleDisk(float radius) const
{
    auto p = radius * Random::RandomInUnitDisk();
    return (p.x * m_PixelDeltaU) + (p.y * m_PixelDeltaV);
}

Vec3 Camera::DefocusDiskSample() const
{
    auto p = Random::RandomInUnitDisk();
    return Pos + (p.x * m_DefocusDiskU) + (p.y * m_DefocusDiskV);
}