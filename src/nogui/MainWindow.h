
#pragma once
#include "core.h"
#include <GLFW/glfw3.h>
#include <memory>

class MainWindow
{
public:
    MainWindow();
    bool Show();

private:
    bool Init();

private:
    std::shared_ptr<Image> m_Img;
    Camera m_Camera;
    Scene m_Scene;
    Renderer m_Renderer;
    GLFWwindow *m_Window;
};