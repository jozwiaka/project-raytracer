#include "Renderer.h"
Renderer::Renderer(Camera *camera, Scene *scene, Image *image, int maxDepth)
    : m_Camera(camera),
      m_Scene(scene),
      m_Image(image),
      m_MaxDepth(maxDepth),
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
        Display();
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

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    int numSamples = 2; // 4x antialiasing (2x2 grid)

    for (int y = 0; y < m_Image->Height; ++y)
    {
        for (int x = 0; x < m_Image->Width; ++x)
        {
            float px = (2.0f * x - m_Image->Width) / m_Image->Width * m_Image->AspectRatioReal;
            float py = (m_Image->Height - 2.0f * y) / m_Image->Height;
            Color pixelColor = Color();

            // Collect color samples from sub-pixel locations
            for (int sy = 0; sy < numSamples; ++sy)
            {
                for (int sx = 0; sx < numSamples; ++sx)
                {
                    float spx = (2.0f * (x + (sx + 0.5f) / numSamples) - m_Image->Width) / m_Image->Width * m_Image->AspectRatioReal;
                    float spy = (m_Image->Height - 2.0f * (y + (sy + 0.5f) / numSamples)) / m_Image->Height;
                    Ray ray = m_Camera->GenerateRay(spx, spy);
                    pixelColor += RayColor(ray, m_MaxDepth);
                }
            }

            pixelColor /= (numSamples * numSamples);

            pixelColor = ColorManipulator::GammaCorrection(pixelColor);

            glColor3f(pixelColor.x, pixelColor.y, pixelColor.z);
            glVertex2f(px, py);
        }
    }

    glEnd();
    glFlush();
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
