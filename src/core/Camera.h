#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"
#include "Image.h"

class Camera
{
public:
    Math::Vec3 Pos;
    Math::Vec3 Forward, Right, Up;
    float DefocusAngle;
    float VerticalFOV;
    float FocusDist;

public:
    Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle, float verticalFOV, float focusDist, Image *image);
    Ray GenerateRay(int i, int j) const;

private:
    Image *m_Image;
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