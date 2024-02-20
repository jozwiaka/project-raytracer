#include "core.h"
#include <memory>

int main()
{

    auto [image, camera, scene, renderer] = Example::SetUp(1);

    if (!renderer->CreateWindowAndDisplayInLoop())
    {
        return -1;
    }
}
