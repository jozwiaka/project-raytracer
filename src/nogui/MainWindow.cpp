#include "MainWindow.h"

MainWindow::MainWindow()
{
    Initializer::ThreeSpheresTest(m_Img, m_Camera, m_Scene, m_Renderer);
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
        m_Img->OnResize(width, height);
        m_Renderer.OnResize(width, height);
        m_Camera.OnResize(width, height);

        m_Renderer.Display(m_Camera, m_Scene);
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
