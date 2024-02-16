#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"
#include "Image.h"
#include <memory>

class Camera
{
public:
    Math::Vec3 Pos;
    Math::Vec3 Target;
    Math::Vec3 UpVector;
    float DefocusAngle;
    float VerticalFOV;
    float FocusDist;

public:
    Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, std::shared_ptr<Image> image);
    void Init();
    Ray GenerateRay(int i, int j) const;

private:
    Math::Vec3 m_W, m_U, m_V;
    std::shared_ptr<Image> m_Image;
    Math::Vec3 m_Pixel00Loc;
    Math::Vec3 m_PixelDeltaU;
    Math::Vec3 m_PixelDeltaV;
    Math::Vec3 m_DefocusDiskU;
    Math::Vec3 m_DefocusDiskV;

private:
    Math::Vec3 DefocusDiskSample() const;
    Math::Vec3 PixelSampleSquare() const;
    Math::Vec3 PixelSampleDisk(float radius) const;
};