#include "MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer)
    : m_Img(img), m_Camera(camera), m_Scene(scene), m_Renderer(renderer)
{
}

bool MainWindow::Show()
{
    if (!Init())
    {
        return false;
    }

    int width, height;
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwGetWindowSize(m_Window, &width, &height);

        m_Renderer.OnResize(width, height);
        m_Camera.OnResize(width, height);

        m_Renderer.Render(m_Camera, m_Scene);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    glfwTerminate();
    return true;
}

bool MainWindow::Init()
{
    if (!glfwInit())
    {
        return false;
    }

    m_Window = glfwCreateWindow(m_Img->GetWidth(), m_Img->GetHeight(), "Raytracer", NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    return true;
}
