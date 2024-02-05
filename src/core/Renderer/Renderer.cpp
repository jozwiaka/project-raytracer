#include <GL/glut.h>
#include "Renderer.h"
#include "Vec3.h"
#include "Material.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Image.h"

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Scene scene;
    Material redMaterial(Vec3(1, 0, 0));
    Material blueMaterial(Vec3(0, 0, 1));
    scene.AddObject(std::make_unique<Sphere>(Vec3(0, 0, -5), 1.0, redMaterial));
    scene.AddObject(std::make_unique<Sphere>(Vec3(2, 0, -7), 2.0, blueMaterial));
    scene.AddLight(std::make_unique<Light>(Vec3(0, 5, -5), Vec3(1, 1, 1)));

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
                // Lambertian reflection model
                Vec3 lightDirection = (scene.Lights[0]->Position - hitPoint).Normalize();
                float diffuseIntensity = std::max(0.0f, normal.Dot(lightDirection));
                Vec3 finalColor = material.Color * diffuseIntensity * scene.Lights[0]->Color;

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