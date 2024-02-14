#include "Image.h"

Image::Image(int width, float aspectRatio)
    : Width(width),
      AspectRatioIdeal(aspectRatio),
      Height(static_cast<int>(Width / AspectRatioIdeal)),
      AspectRatioReal(static_cast<float>(Width) / static_cast<float>(Height))
{
  Pixels.reserve(Width * Height);
}