#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"
#include "Image.h"

class Camera
{
public:
    Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, Image *image);
    Ray GenerateRay(int i, int j) const;

private:
    Math::Vec3 m_Pos;
    Math::Vec3 m_Forward, m_Right, m_Up;
    float m_DefocusAngle;
    float m_VerticalFOV;
    Image *m_Image;
    float m_FocusDist;
    Math::Vec3 m_Pixel00Loc;
    Math::Vec3 m_PixelDeltaRight;
    Math::Vec3 m_PixelDeltaUp;
    Math::Vec3 m_DefocusDiskRight;
    Math::Vec3 m_DefocusDiskUp;

private:
    Math::Vec3 DefocusDiskSample() const;
    Math::Vec3 PixelSampleSquare() const;
    Math::Vec3 PixelSampleDisk(float radius) const;
    void Init();
};