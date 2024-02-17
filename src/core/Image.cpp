#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

void Image::SaveAsPNG() const
{
  if (m_Pixels.empty())
  {
    // std::cerr << "Error: Cannot save empty image." << std::endl;
    return;
  }

  std::vector<unsigned char> imageData(Width * Height * 3); // 3 channels (RGB)

  // Fill buffer with pixel data
  for (const Pixel &pixel : m_Pixels)
  {
    int index = (pixel.y * Width + pixel.x) * 3;
    imageData[index] = static_cast<unsigned char>(pixel.Col.x * 255);
    imageData[index + 1] = static_cast<unsigned char>(pixel.Col.y * 255);
    imageData[index + 2] = static_cast<unsigned char>(pixel.Col.z * 255);
  }

  static size_t i = 0;
  std::string filename = "../../output/frames/frame_" + std::to_string(++i) + ".png";
  // Write pixel data to PNG file
  if (!stbi_write_png(filename.c_str(), Width, Height, 3, imageData.data(), Width * 3))
  {
    return;
  }
}
