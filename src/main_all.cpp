#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <memory>

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

    Vec3 operator*(const Vec3& other) const {
        return Vec3(x * other.x, y * other.y, z * other.z);
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

class Material {
public:
    Vec3 color;
    Material() = default;
    Material(const Vec3& color) : color(color) {}
};

class Light {
public:
    Vec3 position;
    Vec3 color;

    Light(const Vec3& position, const Vec3& color) : position(position), color(color) {}
};

class Object {
public:
    Vec3 position;
    Material material;

    Object(const Vec3& position, const Material& material) : position(position), material(material) {}

    virtual bool intersect(const Ray& ray, float& t, Vec3& hitPoint, Vec3& normal) const = 0;
};

class Sphere : public Object {
public:
    float radius;

    Sphere(const Vec3& position, float radius, const Material& material)
        : Object(position, material), radius(radius) {}

    bool intersect(const Ray& ray, float& t, Vec3& hitPoint, Vec3& normal) const override {
        Vec3 oc = ray.origin - position;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
            float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
            t = (t1 < t2) ? t1 : t2;

            hitPoint = ray.origin + ray.direction * t;
            normal = (hitPoint - position).normalize();

            return true;
        }

        return false;
    }
};

class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Light> lights;

    void addObject(std::unique_ptr<Object> object) {
        objects.push_back(std::move(object));
    }

    void addLight(const Light& light) {
        lights.push_back(light);
    }

    bool intersect(const Ray& ray, Vec3& hitPoint, Vec3& normal, Material& material) const {
        float tClosest = std::numeric_limits<float>::infinity();
        bool hit = false;

        for (const auto& object : objects) {
            float t;
            Vec3 objectHitPoint, objectNormal;

            if (object->intersect(ray, t, objectHitPoint, objectNormal) && t < tClosest) {
                tClosest = t;
                hit = true;

                hitPoint = objectHitPoint;
                normal = objectNormal;
                material = object->material;
            }
        }

        return hit;
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

class Image {
public:
    std::vector<Vec3> pixels;
    int width, height;

    Image(int width, int height) : width(width), height(height), pixels(width * height) {}

    void setPixel(int x, int y, const Vec3& color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y * width + x] = color;
        }
    }
};

class Renderer {
public:
    static const int width = 800;
    static const int height = 600;

    static void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        Scene scene;

        Material redMaterial(Vec3(1, 0, 0));
        Material blueMaterial(Vec3(0, 0, 1));

        scene.addObject(std::make_unique<Sphere>(Vec3(0, 0, -5), 1.0, redMaterial));
        scene.addObject(std::make_unique<Sphere>(Vec3(2, 0, -7), 2.0, blueMaterial));

        Light light(Vec3(0, 5, -5), Vec3(1, 1, 1));
        scene.addLight(light);

        Camera camera(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0));

        Image image(width, height);

        glBegin(GL_POINTS);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float px = (2.0f * x - width) / width;
                float py = (height - 2.0f * y) / height;

                Ray ray = camera.generateRay(px, py);

                Vec3 hitPoint, normal;
                Material material;
                if (scene.intersect(ray, hitPoint, normal, material)) {
                    // Lambertian reflection model
                    Vec3 lightDirection = (light.position - hitPoint).normalize();
                    float diffuseIntensity = std::max(0.0f, normal.dot(lightDirection));
                    Vec3 finalColor = material.color * diffuseIntensity * light.color;

                    glColor3f(finalColor.x, finalColor.y, finalColor.z);
                } else {
                    glColor3f(0, 0, 0);
                }

                glVertex2f(px, py);
                image.setPixel(x, y, material.color);
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
