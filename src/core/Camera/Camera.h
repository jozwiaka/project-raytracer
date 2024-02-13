#pragma once

#include "Ray.h"
#include "Math.h"
#include "Random.h"

class Camera
{
public:
    Camera(const Math::Vec3 &position, const Math::Vec3 &target, const Math::Vec3 &upVector, float defocusAngle);
    Ray GenerateRay(float x, float y) const;

private:
    Math::Vec3 m_Position;
    Math::Vec3 m_Forward, m_Right, m_Up;
    float m_DefocusAngle;
    float m_FocusDist;

private:
    Math::Vec3 DefocusDiskSample() const;
};