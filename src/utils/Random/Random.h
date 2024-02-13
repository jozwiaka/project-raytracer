#pragma once

#include "Math.h"

class Random
{
public:
    static float RandomFloat();
    static float RandomFloat(float min, float max);
    static Math::Vec3 RandomVector();
    static Math::Vec3 RandomVector(float min, float max);
    static Math::Vec3 RandomInUnitSphere();
    static Math::Vec3 RandomUnitVector();
    static Math::Vec3 RandomOnHemisphere(const Math::Vec3 &normal);
    static Math::Vec3 RandomInUnitDisk();
};