#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <filesystem>
#include <sstream>

Image::Image(uint32_t width, float aspectRatio)
    : m_Width(width),
      m_Height(static_cast<uint32_t>(m_Width / aspectRatio))
{
  Init();
  SetUpTmpDir();
}

Image::~Image()
{
  if (std::filesystem::exists(m_TmpDir))
  {
    std::filesystem::remove_all(m_TmpDir);
  }
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

std::vector<uint32_t> &Image::GetVerticalIter()
{
  return m_VerticalIter;
}

std::vector<uint32_t> &Image::GetHorizontalIter()
{
  return m_HorizontalIter;
}

void Image::Init()
{
  Data.resize(m_Height);
  for (auto &row : Data)
  {
    row.resize(m_Width);
  }
  m_HorizontalIter.resize(m_Width);
  m_VerticalIter.resize(m_Height);
  for (uint32_t i = 0; i < m_Width; ++i)
  {
    m_HorizontalIter[i] = i;
  }
  for (uint32_t i = 0; i < m_Height; ++i)
  {
    m_VerticalIter[i] = i;
  }
  m_AspectRatio = static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

void Image::Resize(uint32_t width, uint32_t height)
{
  if (m_Width == width && m_Height == height)
  {
    return;
  }
  m_Width = width;
  m_Height = height;
  Init();
}

void Image::Save() const
{
  static size_t frameIndex = 0;

  if (Data.empty() || frameIndex > 100)
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

  std::stringstream ss;
  ss << m_TmpDir << "frame_" << ++frameIndex << ".png";
  if (!stbi_write_png(ss.str().c_str(), m_Width, m_Height, m_Channels, imageData.data(), m_Width * m_Channels))
  {
    return;
  }
}

void Image::SetUpTmpDir()
{
  m_TmpDir = "../images/rendered/tmp/";
  if (std::filesystem::exists(m_TmpDir))
  {
    std::filesystem::remove_all(m_TmpDir);
  }
  std::filesystem::create_directories(m_TmpDir);
}
