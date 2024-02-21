#include "core.h"
#include "MainWindow.h"

int main()
{
    auto [image, camera, scene, renderer] = Initializer::ThreeSpheresTest();

    auto window = MainWindow(image, renderer);
    window.Show();
}
