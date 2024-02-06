#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Vec3.h"
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Image.h"

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Scene scene;
    Material redMaterial(Vec3(1, 0, 0));
    Material blueMaterial(Vec3(0, 0, 1));
    // scene.AddObject(std::make_unique<Cuboid>(Vec3(0, 0, -5), 1.0, redMaterial));

    // scene.AddObject(std::make_unique<Sphere>(Vec3(0, 0, -5), 1.0, redMaterial));
    // scene.AddObject(std::make_unique<Sphere>(Vec3(2, 0, -7), 2.0, blueMaterial));
    scene.AddLight(std::make_unique<Light>(Vec3(0, 0, 0), Vec3(1, 1, 1)));
    // scene.AddLight(std::make_unique<Light>(Vec3(0, -5, -5), Vec3(1, 1, 1)));

    Camera camera(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0));

    Image image(Width, Height);

    glBegin(GL_POINTS);
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            float px = (2.0f * x - Width) / Width;
            float py = (Height - 2.0f * y) / Height;

            Ray ray = camera.GenerateRay(px, py);

            Vec3 hitPoint, normal;
            Material material;
            if (scene.Intersect(ray, hitPoint, normal, material))
            {
                Vec3 finalColor = Vec3(0.0f, 0.0f, 0.0f);

                // Lambertian reflection model
                for (const auto &light : scene.Lights)
                {
                    Vec3 lightDirection = (light->Position - hitPoint).Normalize();
                    float distance = (light->Position - hitPoint).Length();
                    float attenuation = 1 / (1 + 0.1 * distance + 0.01 * distance * distance);
                    float diffuseIntensity = std::max(0.0f, normal.Dot(lightDirection));
                    Vec3 lightContribution = material.Color * diffuseIntensity * light->Color * attenuation;
                    finalColor += lightContribution;
                }

                glColor3f(finalColor.x, finalColor.y, finalColor.z);
            }
            else
            {
                glColor3f(0, 0, 0);
            }

            glVertex2f(px, py);
            image.SetPixel(x, y, material.Color);
        }
    }

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