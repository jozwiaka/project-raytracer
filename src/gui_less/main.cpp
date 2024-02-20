#include "core.h"
#include <memory>

int main()
{
    auto [image, camera, scene, renderer] = Example::ThreeSpheresTest();

    if (!renderer->CreateWindowAndDisplayInLoop())
    {
        return -1;
    }
}
