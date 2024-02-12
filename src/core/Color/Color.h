#pragma once

#include "Math.h"
#include "Interval.h"

using Color = Math::Vec3;

class ColorManipulator
{
public:
    static Color GammaCorrection(const Color &color);

private:
    static float LinearToGamma(float linearComponent);
};