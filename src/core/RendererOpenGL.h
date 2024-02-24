#pragma once

#include "Renderer.h"

class RendererOpenGL : public Renderer
{
public:
    RendererOpenGL(const Renderer &renderer);
    virtual void OnResize(uint32_t width, uint32_t height) override;
    virtual void Render(const Camera &camera, const Scene &scene) override;
    void ConfigureViewport();
};