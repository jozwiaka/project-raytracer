#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"
#include "Image.h"
#include <memory>

class Camera
{
public:
    Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, std::shared_ptr<Image> image);
    Ray GenerateRay(uint32_t i, uint32_t j) const;

    Math::Vec3 GetPos() const;
    void SetPos(const Math::Vec3 &newPos);

    Math::Vec3 GetTarget() const;
    void SetTarget(const Math::Vec3 &newTarget);

    Math::Vec3 GetUpVector() const;
    void SetUpVector(const Math::Vec3 &newUpVector);

    float GetDefocusAngle() const;
    void SetDefocusAngle(float newDefocusAngle);

    float GetVerticalFOV() const;
    void SetVerticalFOV(float newVerticalFOV);

    float GetFocusDist() const;
    void SetFocusDist(float newFocusDist);

    void Init();

private:
    Math::Vec3 DefocusDiskSample() const;
    Math::Vec3 PixelSampleSquare() const;
    Math::Vec3 PixelSampleDisk(float radius) const;

private:
    Math::Vec3 m_Pos;
    Math::Vec3 m_Target;
    Math::Vec3 m_UpVector;
    float m_DefocusAngle;
    float m_VerticalFOV;
    float m_FocusDist;

    Math::Vec3 m_W, m_U, m_V;
    std::shared_ptr<Image> m_Image;
    Math::Vec3 m_Pixel00Loc;
    Math::Vec3 m_PixelDeltaU;
    Math::Vec3 m_PixelDeltaV;
    Math::Vec3 m_DefocusDiskU;
    Math::Vec3 m_DefocusDiskV;
};