#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

const int width = 800;
const int height = 600;

struct Vec3 {
    float x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
        // Addition operator
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication operator
    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }
};

struct Ray {
    Vec3 origin, direction;
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
};

struct Sphere {
    Vec3 center;
    float radius;
    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}
};

std::vector<Sphere> spheres;

Vec3 normalize(const Vec3& v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vec3(v.x / length, v.y / length, v.z / length);
}

bool intersect(const Ray& ray, const Sphere& sphere, float& t) {
    Vec3 oc = ray.origin - sphere.center;
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    float c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;  // No intersection
    }

    float t1 = (-b + std::sqrt(discriminant)) / (2.0f * a);
    float t2 = (-b - std::sqrt(discriminant)) / (2.0f * a);

    t = std::min(t1, t2);
    return true;
}

Vec3 trace(const Ray& ray, int depth) {
    if (depth == 0) {
        return Vec3(0, 0, 0);  // Black for simplicity
    }

    float t;
    int hitIndex = -1;

    for (int i = 0; i < spheres.size(); ++i) {
        if (intersect(ray, spheres[i], t)) {
            hitIndex = i;
        }
    }

    if (hitIndex == -1) {
        return Vec3(0, 0, 0);  // Black background
    }

    Vec3 hitPoint = ray.origin + ray.direction * t;
    Vec3 normal = normalize(hitPoint - spheres[hitIndex].center);

    // Simple shading
    float intensity = std::max(0.0f, normal.x * ray.direction.x + normal.y * ray.direction.y + normal.z * ray.direction.z);
    return Vec3(1, 1, 1) * intensity;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            // Map pixel coordinates to NDC
            float ndcX = (2.0f * x) / width - 1.0f;
            float ndcY = 1.0f - (2.0f * y) / height;

            Ray ray(Vec3(0, 0, 0), normalize(Vec3(ndcX, ndcY, -1)));

            Vec3 color = trace(ray, 5);

            glColor3f(color.x, color.y, color.z);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    }

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Simple Raytracer");

    init();

    spheres.push_back(Sphere(Vec3(0, 0, -5), 1.0)); // Example Sphere

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
