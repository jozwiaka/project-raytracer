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

    while (!glfwWindowShouldClose(m_Window))
    {
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

    glfwSetWindowUserPointer(m_Window, &m_Renderer);

    glfwSetFramebufferSizeCallback(m_Window, WindowSizeChangedCallback);

    m_Renderer.ConfigureViewport();

    return true;
}

void MainWindow::WindowSizeChangedCallback(GLFWwindow *window, int width, int height)
{
    Renderer *renderer = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
    renderer->ResizeViewport(width, height);
}