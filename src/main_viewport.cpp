#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Get the current angle
        float x = r * cosf(theta);                                        // Calculate the x component
        float y = r * sinf(theta);                                        // Calculate the y component
        glVertex2f(x + cx, y + cy);                                       // Output vertex
    }
    glEnd();
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(1900, 1200, "OpenGL with GLEW", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Set the viewport size
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Set up orthographic projection with aspect ratio correction
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspectRatio = (float)width / (float)height;
        glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw circles
        glColor3f(1.0f, 1.0f, 1.0f);         // Set circle color to white
        drawCircle(-0.5f, 0.5f, 0.3f, 100);  // Draw first circle
        drawCircle(0.5f, 0.5f, 0.3f, 100);   // Draw second circle
        drawCircle(-0.5f, -0.5f, 0.3f, 100); // Draw third circle
        drawCircle(0.5f, -0.5f, 0.3f, 100);  // Draw fourth circle
        drawCircle(-1.5, 0.5f, 0.3f, 100);   // Draw first circle
        drawCircle(1.5, 0.5f, 0.3f, 100);    // Draw second circle
        drawCircle(-1.5, -0.5f, 0.3f, 100);  // Draw third circle
        drawCircle(1.5, -0.5f, 0.3f, 100);   // Draw fourth circle

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
