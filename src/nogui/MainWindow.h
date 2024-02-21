
#pragma once
#include "core.h"
#include <GLFW/glfw3.h>
#include <memory>

class MainWindow
{
public:
    MainWindow(std::shared_ptr<Image> image, std::shared_ptr<Renderer> renderer);
    bool Show();
    static void WindowSizeChangedCallback(GLFWwindow *window, int width, int height);

private:
    bool Init();

private:
    std::shared_ptr<Image> m_Image;
    std::shared_ptr<Renderer> m_Renderer;
    GLFWwindow *m_Window;
};