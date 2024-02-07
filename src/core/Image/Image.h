#pragma once
#include <vector>
#include <glm/glm.hpp>
class Image
{
public:
    std::vector<glm::vec3> Pixels;
    int Width, Height;

    Image(int width, int height);
    void SetPixel(int x, int y, const glm::vec3 &color);
};