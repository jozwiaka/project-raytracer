#pragma once

class Image
{
public:
    float Width;
    float AspectRatioIdeal;
    float Height;
    float AspectRatioReal;

public:
    Image(int width, float aspectRatio);
};
