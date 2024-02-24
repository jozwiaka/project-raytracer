#include "Renderer.h"
#include <iostream>
#include <execution>

Renderer::Renderer(std::shared_ptr<Image> image, uint32_t numSamples, uint32_t maxDepth)
    : Img(image),
      NumSamples(numSamples),
      MaxDepth(maxDepth)
{
}

void Renderer::ConfigureViewport()
{
    glViewport(0, 0, Img->GetWidth(), Img->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Img->GetWidth(), Img->GetHeight(), 0, -1.0, 1.0); //(0,0) - top left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
    Img->OnResize(width, height);
    ConfigureViewport();
}

void Renderer::Display(const Camera &camera, const Scene &scene)
{
    Render(camera, scene);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (uint32_t y = 0; y < Img->GetHeight(); ++y)
    {
        for (uint32_t x = 0; x < Img->GetWidth(); ++x)
        {
            glColor3f(Img->Data[y][x].x, Img->Data[y][x].y, Img->Data[y][x].z);
            glVertex2f(x, y);
        }
    }
    glEnd();
    glFlush();
}

void Renderer::Render(const Camera &camera, const Scene &scene)
{
    m_ActiveCamera = &camera;
    m_ActiveScene = &scene;
    std::cout << "Rendering image " << Img->GetWidth() << "x" << Img->GetHeight() << "...\n";
    m_Timer.Start();

#define TP 0
#if TP
    std::vector<std::future<void>> futures;
    for (uint32_t y = 0; y < Img->GetHeight(); y += m_TileSize)
    {
        for (uint32_t x = 0; x < Img->GetWidth(); x += m_TileSize)
        {
            futures.emplace_back(m_ThreadPool.Enqueue(
                [this](uint32_t startX, uint32_t startY)
                {
                    for (uint32_t y = startY; y < startY + m_TileSize && y < Img->GetHeight(); ++y)
                    {
                        for (uint32_t x = startX; x < startX + m_TileSize && x < Img->GetWidth(); ++x)
                        {
                            PerPixel(x, y);
                        }
                    }
                },
                x, y));
        }
    }

    for (auto &future : futures)
    {
        future.get();
    }
#else
    std::for_each(std::execution::par, Img->GetVerticalIter().begin(), Img->GetVerticalIter().end(),
                  [this](uint32_t y)
                  {
                      std::for_each(std::execution::par, Img->GetHorizontalIter().begin(), Img->GetHorizontalIter().end(), [this, y](uint32_t x)
                                    { PerPixel(x, y); });
                  });
#endif

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
