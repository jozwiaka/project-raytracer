#include "Camera.h"
#include <cmath>

Camera::Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, std::shared_ptr<Image> image)
    : m_Pos(position),
      m_Target(target),
      m_UpVector(upVector),
      m_DefocusAngle(defocusAngle),
      m_VerticalFOV(verticalFOV),
      m_FocusDist(focusDist <= 0 ? Math::Length(target - m_Pos) : focusDist),
      m_Image(image)
{
    Init();
}

void Camera::Init()
{
    m_W = Math::Normalize(m_Pos - m_Target);
    m_U = Math::Normalize(Math::Cross(m_UpVector, m_W));
    m_V = Math::Normalize(Math::Cross(m_W, m_U));

    auto theta = Math::Radians(m_VerticalFOV);
    auto h = std::tan(theta / 2.0f);
    auto viewportHeight = 2.0f * h * m_FocusDist;
    auto viewportWidth = viewportHeight * m_Image->GetAspectRatio();

    Math::Vec3 viewportU = viewportWidth * m_U;
    Math::Vec3 viewportV = viewportHeight * -m_V;

    m_PixelDeltaU = viewportU / static_cast<float>(m_Image->GetWidth());
    m_PixelDeltaV = viewportV / static_cast<float>(m_Image->GetHeight());

    auto viewportVperLeft = m_Pos - (m_FocusDist * m_W) - viewportU / 2.0f - viewportV / 2.0f;
    m_Pixel00Loc = viewportVperLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

    auto defocusRadius = m_FocusDist * std::tan(Math::Radians(m_DefocusAngle / 2.0f));
    m_DefocusDiskU = m_U * defocusRadius;
    m_DefocusDiskV = m_V * defocusRadius;
}

Math::Vec3 Camera::GetPos() const
{
    return m_Pos;
}

void Camera::SetPos(const Math::Vec3 &newPos)
{
    if (newPos == m_Pos)
    {
        return;
    }
    m_Pos = newPos;
    Init();
}

Math::Vec3 Camera::GetTarget() const
{
    return m_Target;
}

void Camera::SetTarget(const Math::Vec3 &newTarget)
{
    if (newTarget == m_Target)
    {
        return;
    }
    m_Target = newTarget;
    Init();
}

Math::Vec3 Camera::GetUpVector() const
{
    return m_UpVector;
}

void Camera::SetUpVector(const Math::Vec3 &newUpVector)
{
    if (newUpVector == m_UpVector)
    {
        return;
    }
    m_UpVector = newUpVector;
    Init();
}

float Camera::GetDefocusAngle() const
{
    return m_DefocusAngle;
}

void Camera::SetDefocusAngle(float newDefocusAngle)
{
    if (newDefocusAngle == m_DefocusAngle)
    {
        return;
    }
    m_DefocusAngle = newDefocusAngle;
    Init();
}

float Camera::GetVerticalFOV() const
{
    return m_VerticalFOV;
}

void Camera::SetVerticalFOV(float newVerticalFOV)
{
    if (newVerticalFOV == m_VerticalFOV)
    {
        return;
    }
    m_VerticalFOV = newVerticalFOV;
    Init();
}

float Camera::GetFocusDist() const
{
    return m_FocusDist;
}

void Camera::SetFocusDist(float newFocusDist)
{
    if (newFocusDist == m_FocusDist)
    {
        return;
    }
    m_FocusDist = newFocusDist;
    Init();
}

Ray Camera::GenerateRay(uint32_t i, uint32_t j) const
{
    auto pixelCenter = m_Pixel00Loc + (static_cast<float>(i) * m_PixelDeltaU) + (static_cast<float>(j) * m_PixelDeltaV);
    auto pixelSample = pixelCenter + PixelSampleSquare();

    auto rayOrigin = (m_DefocusAngle <= 0) ? m_Pos : DefocusDiskSample();
    auto rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}

Math::Vec3 Camera::PixelSampleSquare() const
{
    auto px = -0.5f + Random::RandomFloat();
    auto py = -0.5f + Random::RandomFloat();
    return (px * m_PixelDeltaU) + (py * m_PixelDeltaV);
}

Math::Vec3 Camera::PixelSampleDisk(float radius) const
{
    auto p = radius * Random::RandomInUnitDisk();
    return (p.x * m_PixelDeltaU) + (p.y * m_PixelDeltaV);
}

Math::Vec3 Camera::DefocusDiskSample() const
{
    auto p = Random::RandomInUnitDisk();
    return m_Pos + (p.x * m_DefocusDiskU) + (p.y * m_DefocusDiskV);
}