#include "Renderer.h"
Renderer::Renderer(Camera *camera, Scene *scene, int width, float aspectRatio)
    : m_Camera(camera),
      m_Scene(scene),
      m_Width(width),
      m_AspectRatioIdeal(aspectRatio),
      m_Height(static_cast<int>(m_Width / m_AspectRatioIdeal)),
      m_AspectRatioReal(static_cast<float>(m_Width) / static_cast<float>(m_Height)),
      m_Window(nullptr)
{
}

bool Renderer::Init()
{
    if (!glfwInit())
    {
        return false;
    }

    m_Window = glfwCreateWindow(m_Width, m_Height, "Raytracer", NULL, NULL);
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

    glViewport(0, 0, m_Width, m_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-m_AspectRatioReal, m_AspectRatioReal, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return true;
}

void Renderer::MainLoop()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        Display();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    int numSamples = 2; // 4x antialiasing (2x2 grid)

    for (int y = 0; y < m_Height; ++y)
    {
        for (int x = 0; x < m_Width; ++x)
        {
            float px = (2.0f * x - m_Width) / m_Width * m_AspectRatioReal;
            float py = (m_Height - 2.0f * y) / m_Height;
            Math::Vec3 finalColor = Math::Vec3(0.0f, 0.0f, 0.0f);

            // Collect color samples from sub-pixel locations
            for (int sy = 0; sy < numSamples; ++sy)
            {
                for (int sx = 0; sx < numSamples; ++sx)
                {
                    float spx = (2.0f * (x + (sx + 0.5f) / numSamples) - m_Width) / m_Width * m_AspectRatioReal;
                    float spy = (m_Height - 2.0f * (y + (sy + 0.5f) / numSamples)) / m_Height;
                    Ray ray = m_Camera->GenerateRay(spx, spy);

                    Math::Vec3 hitPoint, normal;
                    std::shared_ptr<Material> material;
                    if (m_Scene->Intersect(ray, hitPoint, normal, material))
                    {
                        // Lambertian reflection model
                        // for (const auto &light : m_Scene->Lights)
                        // {
                        //     Math::Vec3 lightDirection = Math::Normalize((light->Position - hitPoint));
                        //     float distance = Math::Length(light->Position - hitPoint);
                        //     float attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);
                        //     float diffuseIntensity = std::max(0.0f, Math::Dot(normal, lightDirection));
                        //     Math::Vec3 lightContribution = material->Color * diffuseIntensity * light->Color * attenuation;
                        //     finalColor += lightContribution;
                        // }
                        finalColor += material->Color;
                    }
                    else
                    {
                        finalColor += m_Scene->BackgroundColor;
                    }
                }
            }

            finalColor /= (numSamples * numSamples);

            glColor3f(finalColor.x, finalColor.y, finalColor.z);
            glVertex2f(px, py);
        }
    }

    glEnd();
    glFlush();
}

Math::Vec3 Renderer::RayColor(const Ray &ray, int depth) const
{
    if (depth <= 0)
    {
        return Math::Vec3(0.0f, 0.0f, 0.0f); // black
    }

    // Object obj;

    auto unitDirection = Math::Normalize(ray.Direction);
    auto a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * Math::Vec3(1.0f, 1.0f, 1.0f) + a * Math::Vec3(0.5f, 0.7f, 1.0f);
}
