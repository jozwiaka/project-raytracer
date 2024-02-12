#include "ColorManipulator.h"

Color ColorManipulator::GammaCorrection(const Color &color)
{
    auto r = LinearToGamma(color.x);
    auto g = LinearToGamma(color.y);
    auto b = LinearToGamma(color.z);
    return Color(r, g, b);
    // static const auto intensity = Interval(0.000, 0.999);
}

float ColorManipulator::LinearToGamma(float linearComponent)
{
    return std::sqrt(linearComponent);
}
