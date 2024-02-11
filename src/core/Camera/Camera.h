#pragma once

#include "Ray.h"
#include "Math.h"

class Camera
{
public:
    Camera(const Math::Point3 &position, const Math::Point3 &target, const Math::Vec3 &upVector);
    Ray GenerateRay(float x, float y) const;

private:
    Math::Point3 m_Position;
    Math::Vec3 m_Forward, m_Right, m_Up;
};