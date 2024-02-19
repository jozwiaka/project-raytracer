#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"
#include "Image.h"
#include <memory>

class Camera
{
public:
    Camera(const Vec3 &position, const Vec3 &target, const Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, std::shared_ptr<Image> image);
    Ray GenerateRay(uint32_t i, uint32_t j) const;

    Vec3 GetPos() const;
    void SetPos(const Vec3 &newPos);

    Vec3 GetTarget() const;
    void SetTarget(const Vec3 &newTarget);

    Vec3 GetUpVector() const;
    void SetUpVector(const Vec3 &newUpVector);

    float GetDefocusAngle() const;
    void SetDefocusAngle(float newDefocusAngle);

    float GetVerticalFOV() const;
    void SetVerticalFOV(float newVerticalFOV);

    float GetFocusDist() const;
    void SetFocusDist(float newFocusDist);

    void Init();

private:
    Vec3 DefocusDiskSample() const;
    Vec3 PixelSampleSquare() const;
    Vec3 PixelSampleDisk(float radius) const;

private:
    Vec3 m_Pos;
    Vec3 m_Target;
    Vec3 m_UpVector;
    float m_DefocusAngle;
    float m_VerticalFOV;
    float m_FocusDist;

    Vec3 m_W, m_U, m_V;
    std::shared_ptr<Image> m_Image;
    Vec3 m_Pixel00Loc;
    Vec3 m_PixelDeltaU;
    Vec3 m_PixelDeltaV;
    Vec3 m_DefocusDiskU;
    Vec3 m_DefocusDiskV;
};