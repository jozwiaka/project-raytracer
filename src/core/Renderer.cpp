#include "Renderer.h"
#include <iostream>
#include <execution>

Renderer::Renderer(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene, uint32_t numSamples, uint32_t maxDepth, uint32_t numThreads, uint32_t tileSize)
    : m_Image(image),
      m_Camera(camera),
      m_Scene(scene),
      m_NumSamples(numSamples),
      m_MaxDepth(maxDepth),
      m_ThreadPool(numThreads),
      m_TileSize(tileSize),
      m_Timer(),
      m_Window(nullptr)
{
}

bool Renderer::CreateWindowAndDisplayInLoop(bool save)
{
    if (!InitWindow())
    {
        return false;
    }

    ConfigureViewport();

    while (!glfwWindowShouldClose(m_Window))
    {
        Display(save);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    glfwTerminate();
    return true;
}

bool Renderer::InitWindow()
{
    if (!glfwInit())
    {
        return false;
    }

    m_Window = glfwCreateWindow(m_Image->GetWidth(), m_Image->GetHeight(), "Raytracer", NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    return true;
}

void Renderer::ConfigureViewport()
{
    glViewport(0, 0, m_Image->GetWidth(), m_Image->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_Image->GetWidth(), 0, m_Image->GetHeight(), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::ResizeViewport(uint32_t width, uint32_t height)
{
    m_Image->Resize(width, height);
    m_Camera->Init();
    ConfigureViewport();
}

void Renderer::ResizeWindow(uint32_t width, uint32_t height)
{
    ResizeViewport(width, height);
    InitWindow();
}

void Renderer::Display(bool save)
{
    Render();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (uint32_t y = 0; y < m_Image->GetHeight(); ++y)
    {
        for (uint32_t x = 0; x < m_Image->GetWidth(); ++x)
        {
            glColor3f(m_Image->Data[y][x].x, m_Image->Data[y][x].y, m_Image->Data[y][x].z);
            glVertex2f(x, m_Image->GetHeight() - 1 - y);
        }
    }
    glEnd();
    glFlush();
    if (save)
    {
        m_Image->Save();
    }
}

void Renderer::Render()
{
    std::cout << "Rendering...\n";
    m_Timer.Start();

#define TP 1
#if TP
    std::vector<std::future<void>> futures;
    for (uint32_t y = 0; y < m_Image->GetHeight(); y += m_TileSize)
    {
        for (uint32_t x = 0; x < m_Image->GetWidth(); x += m_TileSize)
        {
            futures.emplace_back(m_ThreadPool.Enqueue(
                [this](uint32_t startX, uint32_t startY)
                {
                    for (uint32_t y = startY; y < startY + m_TileSize && y < m_Image->GetHeight(); ++y)
                    {
                        for (uint32_t x = startX; x < startX + m_TileSize && x < m_Image->GetWidth(); ++x)
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
    std::for_each(std::execution::par, m_Image->GetVerticalIter().begin(), m_Image->GetVerticalIter().end(),
                  [this](uint32_t y)
                  {
                      std::for_each(std::execution::par, m_Image->GetHorizontalIter().begin(), m_Image->GetHorizontalIter().end(), [this, y](uint32_t x)
                                    { PerPixel(x, y); });
                  });
#endif

    std::string timeEllapsedStr = m_Timer.Stop();
    std::cout << "Done. Time = " << timeEllapsedStr << std::endl;
}

void Renderer::PerPixel(uint32_t x, uint32_t y)
{
    Color pixelColor = Color();
    for (uint32_t sample = 0; sample < m_NumSamples; ++sample)
    {
        Ray ray = m_Camera->GenerateRay(x, y);
        pixelColor += RayColor(ray, m_MaxDepth);
    }
    pixelColor /= m_NumSamples;
    pixelColor = ColorManipulator::GammaCorrection(pixelColor);
    m_Image->Data[y][x] = pixelColor;
}

Color Renderer::RayColor(const Ray &ray, uint32_t depth) const
{
    if (depth <= 0)
    {
        return Color();
    }

    HitRecord rec;
    if (m_Scene->Intersect(ray, Interval(0.001f, Math::Infinity()), rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.Mat->Scatter(ray, rec, attenuation, scattered))
        {
            return attenuation * RayColor(scattered, depth - 1);
        }
        return Color();
    }

    // Background
    auto unitDirection = Math::Normalize(ray.Direction);
    auto a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}
