#include "Image.h"

Image::Image(int width, int height) : Width(width), Height(height), Pixels(width * height) {}

void Image::SetPixel(int x, int y, const Vec3 &color)
{
    if (x >= 0 && x < Width && y >= 0 && y < Height)
    {
        Pixels[y * Width + x] = color;
    }
}