#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <filesystem>
#include <sstream>

Image::Image(uint32_t width, float aspectRatio)
    : Width(width),
      Height(static_cast<uint32_t>(Width / aspectRatio))
{
  Resize();
  if (std::filesystem::exists(m_TmpDir))
  {
    std::filesystem::remove_all(m_TmpDir);
  }
  std::filesystem::create_directory(m_TmpDir);
}

void Image::Resize()
{
  Data.resize(Height);
  for (auto &row : Data)
  {
    row.resize(Width);
  }
  HorizontalIter.resize(Width);
  VerticalIter.resize(Height);
  for (uint32_t i = 0; i < Width; ++i)
  {
    HorizontalIter[i] = i;
  }
  for (uint32_t i = 0; i < Height; ++i)
  {
    VerticalIter[i] = i;
  }
  AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
}

void Image::SaveAsPNG()
{
  if (Data.empty())
  {
    return;
  }

  std::vector<unsigned char> imageData(Width * Height * m_Channels);

  uint32_t i = 0;
  for (const auto &row : Data)
  {
    for (const auto &pixel : row)
    {
      uint32_t index = i++ * m_Channels;
      imageData[index] = static_cast<unsigned char>(pixel.x * 255);
      imageData[index + 1] = static_cast<unsigned char>(pixel.y * 255);
      imageData[index + 2] = static_cast<unsigned char>(pixel.z * 255);
    }
  }

  static size_t frameIndex = 0;
  std::stringstream ss;
  ss << m_TmpDir << "frame_" << ++frameIndex << ".png";
  if (!stbi_write_png(ss.str().c_str(), Width, Height, m_Channels, imageData.data(), Width * m_Channels))
  {
    return;
  }
}
