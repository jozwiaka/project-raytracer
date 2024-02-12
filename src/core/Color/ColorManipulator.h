#pragma once

#include "Math.h"
#include "Interval.h"
#include "Color.h"
#include <cmath>

class ColorManipulator
{
public:
    static Color GammaCorrection(const Color &color);

private:
    static float LinearToGamma(float linearComponent);
};