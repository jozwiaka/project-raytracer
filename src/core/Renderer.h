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
#include "ThreadPool.h"
#include <future>
#include <thread>
class Renderer
{
public:
    Renderer(Camera *camera, Scene *scene, Image *image, int numSamples, int maxDepth, unsigned int numThreads, int tileSize);
    bool RenderLoop();

private:
    Camera *m_Camera;
    Scene *m_Scene;
    Image *m_Image;
    int m_NumSamples;
    int m_MaxDepth;
    ThreadPool m_ThreadPool;
    int m_TileSize;
    GLFWwindow *m_Window;

private:
    bool Init();
    void Render();
    Color RayColor(const Ray &ray, int depth) const;
    void RenderTile(int startX, int startY);
};