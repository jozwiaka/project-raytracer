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
#include "Random.h"
#include "Interval.h"
#include "Color.h"
#include "ColorManipulator.h"
#include "Image.h"

class Renderer
{
public:
    Renderer(Camera *camera, Scene *scene, Image *image, int maxDepth);
    bool RenderLoop();

private:
    Camera *m_Camera;
    Scene *m_Scene;
    Image *m_Image;
    int m_MaxDepth;
    GLFWwindow *m_Window;

private:
    bool Init();
    void Display();
    Color RayColor(const Ray &ray, int depth) const;
};