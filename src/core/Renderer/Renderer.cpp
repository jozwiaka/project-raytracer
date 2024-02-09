// #define MULTITHREADING

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Cylinder.h"

#ifdef MULTITHREADING
#include <future>
#include <mutex>
#endif

#include <thread>
#include <chrono>

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Scene scene;
    Material redMaterial(Math::Vec3(1.0f, 0.0f, 0.0f));
    Material blueMaterial(Math::Vec3(0.0f, 0.0f, 1.0f));
    scene.BackgroundColor = Math::Color3(0.0f, 0.0f, 0.0f);
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, -1000, 0.0f), 1000, blueMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(3.0f, 2.0f, 0.0f), 2.0f, redMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0.0f, 1.0f, 0.0f), 1.0f, redMaterial));

    scene.AddObject(std::make_unique<Cylinder>(Math::Vec3(2.0f, 2.0f, 2.0f), 1.0f, 1.0f, Math::Vec3(0.0f, 0.0f, 0.0f), redMaterial));

    scene.AddLight(std::make_unique<Light>(Math::Vec3(0.0f, 3.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 1.0f)));
    Camera camera(Math::Vec3(0.0f, 5.0f, 10), Math::Vec3(0.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f));

    glBegin(GL_POINTS);

#ifdef MULTITHREADING
    const size_t MaxThreads = 100;
    std::vector<std::future<void>> threads;
    std::mutex mtx;
#endif
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            float px = (2.0f * x - Width) / Width;
            float py = (Height - 2.0f * y) / Height;
#ifdef MULTITHREADING
            threads.emplace_back(std::async(std::launch::async, [px, py, &camera, &scene]()
                                            {
#endif
                                                Ray ray = camera.GenerateRay(px, py);

                                                Math::Vec3 hitPoint, normal;
                                                Material material;
                                                if (scene.Intersect(ray, hitPoint, normal, material))
                                                {
                                                    Math::Vec3 finalColor = Math::Vec3(0.0f, 0.0f, 0.0f);

                                                    // Lambertian reflection model
                                                    for (const auto &light : scene.Lights)
                                                    {
                                                        Math::Vec3 lightDirection = Math::Normalize((light->Position - hitPoint));
                                                        float distance = Math::Length(light->Position - hitPoint);
                                                        float attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);
                                                        float diffuseIntensity = std::max(0.0f, Math::Dot(normal, lightDirection));
                                                        Math::Vec3 lightContribution = material.Color * diffuseIntensity * light->Color * attenuation;
                                                        finalColor += lightContribution;
                                                    }
                                                    finalColor = material.Color;

                                                    glColor3f(finalColor.x, finalColor.y, finalColor.z);
                                                }
                                                else
                                                {
                                                    glColor3f(scene.BackgroundColor.x, scene.BackgroundColor.y, scene.BackgroundColor.z);
                                                }

                                                glVertex2f(px, py);
#ifdef MULTITHREADING
                                            }));
#endif
        }
    }

#ifdef MULTITHREADING
    for (auto &thread : threads)
    {
        thread.wait();
    }
#endif

    glEnd();
    glFlush();

    // std::this_thread::sleep_for(std::chrono::seconds(1.0f));
}

void Renderer::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
}