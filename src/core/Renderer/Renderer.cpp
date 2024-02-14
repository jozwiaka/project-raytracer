#include "Renderer.h"
#include <iostream>

Renderer::Renderer(Camera *camera, Scene *scene, Image *image, int numSamples, int maxDepth, unsigned int numThreads, int tileSize)
    : m_Camera(camera),
      m_Scene(scene),
      m_Image(image),
      m_NumSamples(numSamples),
      m_MaxDepth(maxDepth),
      m_ThreadPool(numThreads),
      m_TileSize(tileSize),
      m_Window(nullptr)
{
}

bool Renderer::RenderLoop()
{
    if (!Init())
    {
        return false;
    }

    while (!glfwWindowShouldClose(m_Window))
    {
        Render();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    glfwTerminate();
    return true;
}

bool Renderer::Init()
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
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, m_Image->Width, m_Image->Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-m_Image->AspectRatioReal, m_Image->AspectRatioReal, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return true;
}

void Renderer::Render()
{
    std::vector<std::future<void>> futures;

    for (int y = 0; y < m_Image->Height; y += m_TileSize)
    {
        for (int x = 0; x < m_Image->Width; x += m_TileSize)
        {
            futures.emplace_back(m_ThreadPool.Enqueue(
                [this](int startX, int startY)
                {
                    this->RenderTile(startX, startY);
                },
                x, y));
        }
    }

    for (auto &future : futures)
    {
        future.get();
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (const auto &pixel : m_Image->GetPixels())
    {
        glColor3f(pixel.Col.x, pixel.Col.y, pixel.Col.z);
        glVertex2f(pixel.x, pixel.y);
    }
    m_Image->Clear();

    glEnd();
    glFlush();
}

void Renderer::RenderTile(int startX, int startY)
{
    for (int y = startY; y < startY + m_TileSize && y < m_Image->Height; ++y)
    {
        for (int x = startX; x < startX + m_TileSize && x < m_Image->Width; ++x)
        {
            float px = (2.0f * x - m_Image->Width) / m_Image->Width * m_Image->AspectRatioReal;
            float py = (m_Image->Height - 2.0f * y) / m_Image->Height;
            Color pixelColor = Color();

            // Collect color samples from sub-pixel locations
            for (int sy = 0; sy < m_NumSamples; ++sy)
            {
                for (int sx = 0; sx < m_NumSamples; ++sx)
                {
                    float spx = (2.0f * (x + (sx + 0.5f) / m_NumSamples) - m_Image->Width) / m_Image->Width * m_Image->AspectRatioReal;
                    float spy = (m_Image->Height - 2.0f * (y + (sy + 0.5f) / m_NumSamples)) / m_Image->Height;
                    Ray ray = m_Camera->GenerateRay(spx, spy);
                    pixelColor += RayColor(ray, m_MaxDepth);
                }
            }

            pixelColor /= (m_NumSamples * m_NumSamples);

            pixelColor = ColorManipulator::GammaCorrection(pixelColor);

            m_Image->AddPixel(px, py, pixelColor);
        }
    }
}

Color Renderer::RayColor(const Ray &ray, int depth) const
{
    if (depth <= 0)
    {
        return Color(); // black
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
