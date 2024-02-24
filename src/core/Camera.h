#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"
#include "Image.h"
#include <memory>

class Camera
{
public:
    std::shared_ptr<Image> Img;
    Vec3 Pos;
    Vec3 Target;
    Vec3 UpVector;
    float DefocusAngle;
    float VerticalFOV;
    float FocusDist;

public:
    Camera() = default;
    Camera(const Vec3 &position, const Vec3 &target, const Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, std::shared_ptr<Image> image);
    Ray GenerateRay(uint32_t i, uint32_t j) const;

    void Init();

private:
    Vec3 DefocusDiskSample() const;
    Vec3 PixelSampleSquare() const;
    Vec3 PixelSampleDisk(float radius) const;

private:
    Vec3 m_W, m_U, m_V;
    Vec3 m_Pixel00Loc;
    Vec3 m_PixelDeltaU;
    Vec3 m_PixelDeltaV;
    Vec3 m_DefocusDiskU;
    Vec3 m_DefocusDiskV;
};