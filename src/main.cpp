#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(Renderer::Width, Renderer::Height, "Raytracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    Renderer::Init();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        Renderer::Display();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
