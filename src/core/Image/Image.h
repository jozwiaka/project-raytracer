#pragma once

class Image
{
public:
    int Width;
    float AspectRatioIdeal;
    int Height;
    float AspectRatioReal;

public:
    Image(int width, float aspectRatio);
};
