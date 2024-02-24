#include "core.h"
#include "MainWindow.h"
#include <memory>

int main()
{
    std::shared_ptr<Image> img;
    Camera camera;
    Scene scene;
    Renderer renderer;

    Initializer::ThreeSpheresTest(img, camera, scene, renderer);

    auto window = MainWindow(img, camera, scene, renderer);
    window.Show();
}
