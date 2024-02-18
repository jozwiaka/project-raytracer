#pragma once

#include <GLFW/glfw3.h>
#include "utils.h"
#include "Material.h"
#include "Scene.h"
#include "ObjectSphere.h"
#include "ObjectCuboid.h"
#include "Camera.h"
#include "ObjectCylinder.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Random.h"
#include "Color.h"
#include "ColorManipulator.h"
#include "Image.h"
#include <future>
#include <thread>
#include <memory>
class Renderer
{
public:
    Renderer(std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene, std::shared_ptr<Image> image, int numSamples, int maxDepth, unsigned int numThreads, int tileSize);
    bool RenderLoop();
    void Render();
    void ConfigureViewport();

private:
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<Scene> m_Scene;
    std::shared_ptr<Image> m_Image;
    int m_NumSamples;
    int m_MaxDepth;
    ThreadPool m_ThreadPool;
    int m_TileSize;
    Timer m_Timer;
    GLFWwindow *m_Window;

private:
    bool InitWindow();
    Color RayColor(const Ray &ray, int depth) const;
    void WriteImagePixels();
    void WriteTilePixels(int startX, int startY);
};