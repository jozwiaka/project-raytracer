#include "ColorManipulator.h"

Color ColorManipulator::GammaCorrection(const Color &color)
{
    auto r = LinearToGamma(color.x);
    auto g = LinearToGamma(color.y);
    auto b = LinearToGamma(color.z);
    return Color(r, g, b);
}

float ColorManipulator::LinearToGamma(float linearComponent)
{
    return std::sqrt(linearComponent);
}
