#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Cylinder.h"
#include "Math.h"
#include "Ray.h"
#include "HitRecord.h"

class Renderer
{
public:
    Renderer(Camera *camera, Scene *scene, int width, float aspectRatio);
    bool Init();
    void MainLoop();

private:
    Camera *m_Camera;
    Scene *m_Scene;
    int m_Width;
    float m_AspectRatioIdeal;
    int m_Height;
    float m_AspectRatioReal;
    GLFWwindow *m_Window;

private:
    void Display();
    Math::Vec3 RayColor(const Ray &ray, int depth) const;
};