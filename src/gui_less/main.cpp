#include "core.h"
#include <memory>

int main()
{
    constexpr float aspectRatio = 16.0f / 9.0f;
    constexpr uint32_t width = 1200;
    auto image = std::make_shared<Image>(width, aspectRatio);

    constexpr auto cameraPosition = Math::Vec3(13.0f, 2.0f, 3.0f);
    constexpr auto cameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
    constexpr auto cameraUpVector = Math::Vec3(0.0f, 1.0f, 0.0f);
    constexpr float defocusAngle = 0.6f;
    constexpr float verticalFOV = 20.0f;
    constexpr float focusDist = 10.0f;
    auto camera = std::make_shared<Camera>(cameraPosition, cameraTarget, cameraUpVector, defocusAngle, verticalFOV, focusDist, image);

    auto scene = std::make_shared<Scene>();
    scene->SetUpExampleScene();

    constexpr uint32_t numSamples = 10;
    constexpr uint32_t maxDepth = 20;
    // uint32_t numThreads = std::thread::hardware_concurrency();
    constexpr uint32_t numThreads = 1000;
    constexpr uint32_t tileSize = 20;
    auto renderer = std::make_shared<Renderer>(camera, scene, image, numSamples, maxDepth, numThreads, tileSize);

    if (!renderer->CreateWindowAndDisplayInLoop())
    {
        return -1;
    }
}
