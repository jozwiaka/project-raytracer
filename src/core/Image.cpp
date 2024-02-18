#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <filesystem>
#include <sstream>

// Image::Image()
//     : m_Width(1200),
//       m_Height(static_cast<uint32_t>(m_Width / (16.0f / 9.0f))) {}

Image::Image(uint32_t width, float aspectRatio)
    : m_Width(width),
      m_Height(static_cast<uint32_t>(m_Width / aspectRatio))
{
  Init();
  if (std::filesystem::exists(m_TmpDir))
  {
    std::filesystem::remove_all(m_TmpDir);
  }
  std::filesystem::create_directory(m_TmpDir);
}

uint32_t Image::GetWidth() const
{
  return m_Width;
}

uint32_t Image::GetHeight() const
{
  return m_Height;
}

float Image::GetAspectRatio() const
{
  return m_AspectRatio;
}

void Image::Init()
{
  Data.resize(m_Height);
  for (auto &row : Data)
  {
    row.resize(m_Width);
  }
  HorizontalIter.resize(m_Width);
  VerticalIter.resize(m_Height);
  for (uint32_t i = 0; i < m_Width; ++i)
  {
    HorizontalIter[i] = i;
  }
  for (uint32_t i = 0; i < m_Height; ++i)
  {
    VerticalIter[i] = i;
  }
  m_AspectRatio = static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

void Image::Resize(uint32_t width, uint32_t height)
{
  if (m_Width == width && m_Height == height)
  {
    return;
  }
  Init();
}

void Image::SaveAsPNG() const
{
  if (Data.empty())
  {
    return;
  }

  std::vector<unsigned char> imageData(m_Width * m_Height * m_Channels);

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
  if (!stbi_write_png(ss.str().c_str(), m_Width, m_Height, m_Channels, imageData.data(), m_Width * m_Channels))
  {
    return;
  }
}
