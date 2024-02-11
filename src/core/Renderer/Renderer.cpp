#include "Renderer.h"

Renderer::Renderer(Camera *camera, Scene *scene, int width, float aspectRatio)
    : m_Camera(camera),
      m_Scene(scene),
      m_Width(width),
      m_AspectRatioIdeal(aspectRatio),
      m_Height(static_cast<int>(m_Width / m_AspectRatioIdeal)),
      m_AspectRatioReal(static_cast<float>(m_Width) / static_cast<float>(m_Height))
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

    for (int y = 0; y < m_Height; ++y)
    {
        for (int x = 0; x < m_Width; ++x)
        {
            float px = (2.0f * x - m_Width) / m_Width * m_AspectRatioReal;
            float py = (m_Height - 2.0f * y) / m_Height;
            Ray ray = m_Camera->GenerateRay(px, py);

            Math::Vec3 hitPoint, normal;
            Material material;
            if (m_Scene->Intersect(ray, hitPoint, normal, material))
            {
                Math::Vec3 finalColor = Math::Vec3(0.0f, 0.0f, 0.0f);

                // Lambertian reflection model
                for (const auto &light : m_Scene->Lights)
                {
                    Math::Vec3 lightDirection = Math::Normalize((light->Position - hitPoint));
                    float distance = Math::Length(light->Position - hitPoint);
                    float attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);
                    float diffuseIntensity = std::max(0.0f, Math::Dot(normal, lightDirection));
                    Math::Vec3 lightContribution = material.Color * diffuseIntensity * light->Color * attenuation;
                    finalColor += lightContribution;
                }
                finalColor = material.Color;

                glColor3f(finalColor.x, finalColor.y, finalColor.z);
            }
            else
            {
                glColor3f(m_Scene->BackgroundColor.x, m_Scene->BackgroundColor.y, m_Scene->BackgroundColor.z);
            }

            glVertex2f(px, py);
        }
    }

    glEnd();
    glFlush();
}
