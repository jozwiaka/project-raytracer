#pragma once

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
#include <GLFW/glfw3.h>

class Renderer
{
public:
    std::shared_ptr<Image> Img;
    uint32_t NumSamples;
    uint32_t MaxDepth;

public:
    Renderer() = default;
    Renderer(std::shared_ptr<Image> image, uint32_t numSamples, uint32_t maxDepth);
    void Render(const Camera &camera, const Scene &scene);
    void Display(const Camera &camera, const Scene &scene);
    void ConfigureViewport();
    void ResizeViewport(uint32_t width, uint32_t height);

private:
    void PerPixel(uint32_t x, uint32_t y);
    Color RayColor(const Ray &ray, uint32_t depth) const;

private:
    Timer m_Timer;
    const Camera *m_ActiveCamera = nullptr;
    const Scene *m_ActiveScene = nullptr;
};