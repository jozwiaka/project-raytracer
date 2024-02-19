#pragma once

#include "Math.h"

class Random
{
public:
    static float RandomFloat();
    static float RandomFloat(float min, float max);
    static Vec3 RandomVector();
    static Vec3 RandomVector(float min, float max);
    static Vec3 RandomInUnitSphere();
    static Vec3 RandomUnitVector();
    static Vec3 RandomOnHemisphere(const Vec3 &normal);
    static Vec3 RandomInUnitDisk();
};