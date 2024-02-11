#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

int main()
{
    // Camera camera;
    // Scene scene;
    // Renderer renderer{&camera, &scene};

    // if(!renderer.Init())
    // {
    //     return -1;
    // }
    // renderer.MainLoop()

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(Renderer::Width, Renderer::Height, "Raytracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    Renderer::Init();

    while (!glfwWindowShouldClose(window))
    {
        Renderer::Display();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
