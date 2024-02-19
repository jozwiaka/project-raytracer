#include "core.h"
#include <memory>

int main()
{
    std::shared_ptr<Image> image;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Renderer> renderer;

    Example::Example_ComplexTest(image, camera, scene, renderer);

    if (!renderer->CreateWindowAndDisplayInLoop())
    {
        return -1;
    }
}
