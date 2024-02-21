#include "MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<Image> image, std::shared_ptr<Renderer> renderer)
    : m_Image(image), m_Renderer(renderer)
{
}

bool MainWindow::Show()
{
    if (!Init())
    {
        return false;
    }

    while (!glfwWindowShouldClose(m_Window))
    {
        m_Renderer->Display();
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

    m_Window = glfwCreateWindow(m_Image->GetWidth(), m_Image->GetHeight(), "Raytracer", NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return false;
        ;
    }

    glfwMakeContextCurrent(m_Window);

    glfwSetWindowUserPointer(m_Window, m_Renderer.get());

    glfwSetFramebufferSizeCallback(m_Window, WindowSizeChangedCallback);

    m_Renderer->ConfigureViewport();

    return true;
}

void MainWindow::WindowSizeChangedCallback(GLFWwindow *window, int width, int height)
{
    Renderer *renderer = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
    renderer->ResizeViewport(width, height);
}