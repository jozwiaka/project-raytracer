
#pragma once
#include "core.h"
#include <GLFW/glfw3.h>
#include <memory>

class MainWindow
{
public:
    MainWindow(std::shared_ptr<Image> &img, Camera &camera, Scene &scene, Renderer &renderer);
    bool Show();

private:
    bool Init();

private:
    std::shared_ptr<Image> m_Img;
    Camera m_Camera;
    Scene m_Scene;
    RendererOpenGL m_Renderer;
    GLFWwindow *m_Window;
};