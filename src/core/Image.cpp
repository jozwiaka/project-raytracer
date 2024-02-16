#include "Image.h"

Image::Image(int width, float aspectRatio)
    : Width(width),
      AspectRatioIdeal(aspectRatio),
      Height(static_cast<int>(Width / AspectRatioIdeal)),
      AspectRatioReal(static_cast<float>(Width) / static_cast<float>(Height))
{
  m_Pixels.reserve(Width * Height);
}

void Image::AddPixel(float x, float y, const Color &color)
{
  std::unique_lock<std::mutex> lock(m_Mtx);
  if (m_Pixels.size() < m_Pixels.capacity())
  {
    m_Pixels.emplace_back(x, y, color);
  }
}

std::vector<Pixel> Image::GetPixels() const
{
  return m_Pixels;
}

void Image::Clear()
{
  std::unique_lock<std::mutex> lock(m_Mtx);
  m_Pixels.clear();
}
