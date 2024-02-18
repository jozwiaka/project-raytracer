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
    Renderer(std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene, std::shared_ptr<Image> image, uint32_t numSamples, uint32_t maxDepth, uint32_t numThreads, uint32_t tileSize);
    bool DisplayLoop();
    void Display();
    void ConfigureViewport();

private:
    bool InitWindow();
    Color RayColor(const Ray &ray, uint32_t depth) const;
    void Render();

private:
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<Scene> m_Scene;
    std::shared_ptr<Image> m_Image;
    uint32_t m_NumSamples;
    uint32_t m_MaxDepth;
    ThreadPool m_ThreadPool;
    uint32_t m_TileSize;
    Timer m_Timer;
    GLFWwindow *m_Window;
};