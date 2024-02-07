// #define MULTITHREADING

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Image.h"

#ifdef MULTITHREADING
#include <future>
#include <mutex>
#endif

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Scene scene;
    Material redMaterial(glm::vec3(1, 0, 0));
    Material blueMaterial(glm::vec3(0, 0, 1));
    // scene.AddObject(std::make_unique<Cuboid>(glm::vec3(-2, 0, -7), glm::vec3(2, 2, 2), glm::vec3(10, 10, 0), blueMaterial));
    // scene.AddObject(std::make_unique<Sphere>(glm::vec3(2, 0, -7), 2.0, blueMaterial));
    // scene.AddObject(std::make_unique<Sphere>(glm::vec3(0, 0, -5), 1.0, redMaterial));
    scene.AddObject(std::make_unique<Cuboid>(glm::vec3(0, 0, -5), glm::vec3(2, 2, 2), glm::vec3(20, 20, 20), redMaterial));

    // scene.AddLight(std::make_unique<Light>(glm::vec3(5, 0, -3), glm::vec3(1, 1, 1)));
    // scene.AddLight(std::make_unique<Light>(glm::vec3(-5, 0, -3), glm::vec3(1, 1, 1)));
    // scene.AddLight(std::make_unique<Light>(glm::vec3(0, 5, -3), glm::vec3(1, 1, 1)));
    // scene.AddLight(std::make_unique<Light>(glm::vec3(0, -5, -3), glm::vec3(1, 1, 1)));
    scene.AddLight(std::make_unique<Light>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

    Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    Image image(Width, Height);

    glBegin(GL_POINTS);

    const size_t X = 800;
    const size_t Y = 800;
#ifdef MULTITHREADING
    const size_t MaxThreads = 100;
    std::vector<std::future<void>> threads;
    std::mutex mtx;
#endif
    for (int y = 0; y < Y; ++y)
    {
        for (int x = 0; x < X; ++x)
        {
            float px = (2.0f * x - X) / X;
            float py = (Y - 2.0f * y) / Y;
#ifdef MULTITHREADING
            threads.emplace_back(std::async(std::launch::async, [px, py, &camera, &scene]()
                                            {
#endif
                                                Ray ray = camera.GenerateRay(px, py);

                                                glm::vec3 hitPoint, normal;
                                                Material material;
                                                if (scene.Intersect(ray, hitPoint, normal, material))
                                                {
                                                    glm::vec3 finalColor = glm::vec3(0.0f, 0.0f, 0.0f);

                                                    // Lambertian reflection model
                                                    for (const auto &light : scene.Lights)
                                                    {
                                                        glm::vec3 lightDirection = glm::normalize((light->Position - hitPoint));
                                                        float distance = glm::length(light->Position - hitPoint);
                                                        float attenuation = 1 / (1 + 0.1 * distance + 0.01 * distance * distance);
                                                        float diffuseIntensity = std::max(0.0f, glm::dot(normal, lightDirection));
                                                        glm::vec3 lightContribution = material.Color * diffuseIntensity * light->Color * attenuation;
                                                        finalColor += lightContribution;
                                                    }

                                                    glColor3f(finalColor.x, finalColor.y, finalColor.z);
                                                }
                                                else
                                                {
                                                    glColor3f(0, 0, 0);
                                                }

                                                glVertex2f(px, py);
// image.SetPixel(x, y, material.Color);
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