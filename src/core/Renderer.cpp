#include "Renderer.h"
#include <iostream>
#include <execution>

void Renderer::OnResize(uint32_t width, uint32_t height)
{
    Img->OnResize(width, height);
}

void Renderer::Render(const Camera &camera, const Scene &scene)
{
    m_ActiveCamera = &camera;
    m_ActiveScene = &scene;
    std::cout << "Rendering image " << Img->GetWidth() << "x" << Img->GetHeight() << "...\n";
    m_Timer.Start();
    std::for_each(std::execution::par, Img->GetVerticalIter().begin(), Img->GetVerticalIter().end(),
                  [this](uint32_t y)
                  {
                      std::for_each(std::execution::par, Img->GetHorizontalIter().begin(), Img->GetHorizontalIter().end(), [this, y](uint32_t x)
                                    { PerPixel(x, y); });
                  });
    std::string timeEllapsedStr = m_Timer.Stop();
    std::cout << "Done. Time = " << timeEllapsedStr << std::endl;
    Img->Save();
}

void Renderer::PerPixel(uint32_t x, uint32_t y)
{
    Color pixelColor = Color();
    for (uint32_t sample = 0; sample < NumSamples; ++sample)
    {
        Ray ray = m_ActiveCamera->GenerateRay(x, y);
        pixelColor += RayColor(ray, MaxDepth);
    }
    pixelColor /= NumSamples;
    pixelColor = ColorManipulator::GammaCorrection(pixelColor);
    Img->Data[y][x] = pixelColor;
}

Color Renderer::RayColor(const Ray &ray, uint32_t depth) const
{
    if (depth <= 0)
    {
        return Color();
    }

    HitRecord rec;
    if (m_ActiveScene->Intersect(ray, Interval(0.001f, Math::Infinity()), rec))
    {
        Ray scattered;
        Color attenuation;
        Color colorFromEmission = rec.Mat->Emitted(rec.U, rec.V, rec.Point);
        if (!rec.Mat->Scatter(ray, rec, attenuation, scattered))
        {
            return colorFromEmission;
        }

        Color colorFromScatter = attenuation * RayColor(scattered, depth - 1);
        return colorFromEmission + colorFromScatter;
    }

    // Background
    auto unitDirection = Math::Normalize(ray.Direction);
    auto a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}
