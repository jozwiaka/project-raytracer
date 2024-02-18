#include "Renderer.h"
#include <iostream>
#include <execution>
// #include <GL/glew.h>

Renderer::Renderer(std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene, std::shared_ptr<Image> image, uint32_t numSamples, uint32_t maxDepth, uint32_t numThreads, uint32_t tileSize)
    : m_Camera(camera),
      m_Scene(scene),
      m_Image(image),
      m_NumSamples(numSamples),
      m_MaxDepth(maxDepth),
      m_ThreadPool(numThreads),
      m_TileSize(tileSize),
      m_Timer(),
      m_Window(nullptr)
{
}

bool Renderer::DisplayLoop()
{
    if (!InitWindow())
    {
        return false;
    }

    ConfigureViewport();

    while (!glfwWindowShouldClose(m_Window))
    {
        Display();
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

    m_Window = glfwCreateWindow(m_Image->Width, m_Image->Height, "Raytracer", NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    // if (glewInit() != GLEW_OK)
    // {
    //     glfwTerminate();
    //     return false;
    // }
    return true;
}

void Renderer::ConfigureViewport()
{
    glViewport(0, 0, m_Image->Width, m_Image->Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_Image->Width, 0, m_Image->Height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::Display()
{
    Render();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (uint32_t y = 0; y < m_Image->Height; ++y)
    {
        for (uint32_t x = 0; x < m_Image->Width; ++x)
        {
            glColor3f(m_Image->Data[y][x].x, m_Image->Data[y][x].y, m_Image->Data[y][x].z);
            glVertex2f(x, m_Image->Height - 1 - y);
        }
    }
    glEnd();
    glFlush();
}

void Renderer::Render()
{
    m_Camera->Update();
    m_Image->Resize();

    std::cout << "Rendering...\n";
    m_Timer.Start();
#define TP 1
#if TP
    std::vector<std::future<void>> futures;
    for (uint32_t y = 0; y < m_Image->Height; y += m_TileSize)
    {
        for (uint32_t x = 0; x < m_Image->Width; x += m_TileSize)
        {
            futures.emplace_back(m_ThreadPool.Enqueue(
                [this](uint32_t startX, uint32_t startY)
                {
                    for (uint32_t y = startY; y < startY + m_TileSize && y < m_Image->Height; ++y)
                    {
                        for (uint32_t x = startX; x < startX + m_TileSize && x < m_Image->Width; ++x)
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
    std::for_each(std::execution::par, m_Image->VerticalIter.begin(), m_Image->VerticalIter.end(),
                  [this](uint32_t y)
                  {
                      std::for_each(std::execution::par, m_Image->HorizontalIter.begin(), m_Image->HorizontalIter.end(), [this, y](uint32_t x)
                                    {
                    Color pixelColor = Color();
                    for (uint32_t sample = 0; sample < m_NumSamples; ++sample)
                    {
                        Ray ray = m_Camera->GenerateRay(x, y);
                        pixelColor += RayColor(ray, m_MaxDepth);
                    }
                    pixelColor /= m_NumSamples;
                    pixelColor = ColorManipulator::GammaCorrection(pixelColor);
                    m_Image->Data[y][x] = pixelColor; });
                  });
#endif

    std::cout << "Done. Time = " << m_Timer.Stop() << std::endl;

    m_Image->SaveAsPNG();
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
