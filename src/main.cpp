#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

class Vec3 {
public:
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(float scalar) const {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3 cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        float len = length();
        if (len > 0) {
            return *this / len;
        }
        return *this;
    }
};

class Ray {
public:
    Vec3 origin, direction;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction.normalize()) {}
};

class Sphere {
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}

    bool intersect(const Ray& ray, float& t) const {
        Vec3 oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
            float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
            t = (t1 < t2) ? t1 : t2;
            return true;
        }

        return false;
    }
};

class Camera {
public:
    Vec3 position;
    Vec3 forward, right, up;

    Camera(const Vec3& position, const Vec3& target, const Vec3& upVector) {
        this->position = position;
        forward = (target - position).normalize();
        right = forward.cross(upVector).normalize();
        up = right.cross(forward).normalize();
    }

    Ray generateRay(float x, float y) const {
        Vec3 direction = forward + right * x + up * y;
        return Ray(position, direction);
    }
};

class Scene {
public:
    std::vector<Sphere> spheres;

    void addSphere(const Sphere& sphere) {
        spheres.push_back(sphere);
    }

    bool intersect(const Ray& ray, Vec3& hitPoint, Vec3& normal) const {
        float tClosest = std::numeric_limits<float>::infinity();
        bool hit = false;

        for (const auto& sphere : spheres) {
            float t;
            if (sphere.intersect(ray, t) && t < tClosest) {
                tClosest = t;
                hit = true;

                hitPoint = ray.origin + ray.direction * t;
                normal = (hitPoint - sphere.center).normalize();
            }
        }

        return hit;
    }
};

class Renderer {
public:
    static const int width = 800;
    static const int height = 600;

    static void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        Scene scene;
        scene.addSphere(Sphere(Vec3(0, 0, -5), 1.0));

        Camera camera(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0));

        glBegin(GL_POINTS);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float px = (2.0f * x - width) / width;
                float py = (height - 2.0f * y) / height;

                Ray ray = camera.generateRay(px, py);

                Vec3 hitPoint, normal;
                if (scene.intersect(ray, hitPoint, normal)) {
                    glColor3f(1, 1, 1);
                } else {
                    glColor3f(0, 0, 0);
                }

                glVertex2f(px, py);
            }
        }

        glEnd();

        glFlush();
    }

    static void init() {
        glClearColor(0, 0, 0, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1, 1, -1, 1);
    }
};

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(Renderer::width, Renderer::height);
    glutCreateWindow("Raytracer");
    Renderer::init();
    glutDisplayFunc(Renderer::display);
    glutMainLoop();

    return 0;
}
