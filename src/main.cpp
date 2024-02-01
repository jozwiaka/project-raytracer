#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

const int WIDTH = 800;
const int HEIGHT = 600;

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Ray {
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
};

struct Sphere {
    Vec3 center;
    float radius;

    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}
};

bool intersect(const Ray& ray, const Sphere& sphere, float& t) {
    Vec3 oc = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0f * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false; // No intersection
    } else {
        // Compute the smallest root that is greater than a small constant epsilon
        t = (-b - sqrt(discriminant)) / (2.0f * a);
        return t > 0.001f;
    }
}

Vec3 trace(const Ray& ray) {
    Sphere sphere(Vec3(0, 0, -5), 1.0f); // Sphere at (0, 0, -5) with radius 1

    float t;
    if (intersect(ray, sphere, t)) {
        // Intersection point
        Vec3 hitPoint = ray.origin + ray.direction * t;

        // Simple shading (color based on the normal vector)
        Vec3 normal = normalize(hitPoint - sphere.center);
        return Vec3(normal.x + 1, normal.y + 1, normal.z + 1) * 0.5f;
    }

    // Background color (black)
    return Vec3(0, 0, 0);
}

void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float px = (2.0f * x - WIDTH) / WIDTH;
            float py = (HEIGHT - 2.0f * y) / HEIGHT;

            Ray ray(Vec3(0, 0, 0), normalize(Vec3(px, py, -1)));

            Vec3 color = trace(ray);

            // Draw pixel
            glColor3f(color.x, color.y, color.z);
            glVertex2i(x, y);
        }
    }

    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Simple Raytracer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
