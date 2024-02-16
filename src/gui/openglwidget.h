#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <memory>
#include "core.h"
#include <iostream>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLWidget(std::shared_ptr<Renderer> renderer, QWidget *parent = nullptr)
        : QOpenGLWidget(parent), m_Renderer(renderer) {}

    void paintGL() override
    {
        Render();
    }

protected:
    void initializeGL() override
    {
        initializeOpenGLFunctions();
        if (!m_Renderer->Init())
        {
            std::cerr << "Failed to initialize renderer!" << std::endl;
            return;
        }
    }

private:
    void Render()
    {
        makeCurrent();
        m_Renderer->Render();
        doneCurrent();
    }

    std::shared_ptr<Renderer> m_Renderer;
};
