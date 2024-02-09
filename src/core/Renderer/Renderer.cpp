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

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Scene scene;
    Material redMaterial(Math::Vec3(1, 0, 0));
    Material blueMaterial(Math::Vec3(0, 0, 1));
    scene.BackgroundColor = Math::Color3(0, 0, 0);
    // scene.AddObject(std::make_unique<Cuboid>(Math::Vec3(-2, 0, -7), Math::Vec3(2, 2, 2), Math::Vec3(10, 10, 0), blueMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(2, 0, -7), 2.0, blueMaterial));
    scene.AddObject(std::make_unique<Sphere>(Math::Vec3(0, 0, -5), 1.0, redMaterial));
    // scene.AddObject(std::make_unique<Cuboid>(Math::Vec3(0, 0, -3), Math::Vec3(1, 1, 1), Math::Vec3(20, 20, 20), redMaterial));
    scene.AddObject(std::make_unique<Cylinder>(Math::Vec3(0, 0, -3), 1, 2, Math::Vec3(10, 10, 10), redMaterial));

    scene.AddLight(std::make_unique<Light>(Math::Vec3(5, 0, -3), Math::Vec3(1, 1, 1)));
    scene.AddLight(std::make_unique<Light>(Math::Vec3(-5, 0, -3), Math::Vec3(1, 1, 1)));
    scene.AddLight(std::make_unique<Light>(Math::Vec3(0, 5, -3), Math::Vec3(1, 1, 1)));
    scene.AddLight(std::make_unique<Light>(Math::Vec3(0, -5, -3), Math::Vec3(1, 1, 1)));
    scene.AddLight(std::make_unique<Light>(Math::Vec3(0, 0, 0), Math::Vec3(1, 1, 1)));

    Camera camera(Math::Vec3(0, 0, 0), Math::Vec3(0, 0, -1), Math::Vec3(0, 1, 0));

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
                                                        float attenuation = 1 / (1 + 0.1 * distance + 0.01 * distance * distance);
                                                        float diffuseIntensity = std::max(0.0f, Math::Dot(normal, lightDirection));
                                                        Math::Vec3 lightContribution = material.Color * diffuseIntensity * light->Color * attenuation;
                                                        finalColor += lightContribution;
                                                    }

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
}

void Renderer::Init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}