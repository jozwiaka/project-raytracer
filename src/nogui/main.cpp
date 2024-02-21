#include "core.h"

int main()
{
    auto [image, camera, scene, renderer] = Initializer::ThreeSpheresTest();

    if (!renderer->CreateWindowAndDisplayInLoop())
    {
        return -1;
    }
}
