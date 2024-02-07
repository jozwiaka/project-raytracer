#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class FileIO
{
public:
    static bool writePPM(const std::string &filename, const std::vector<glm::vec3> &pixels, int width, int height)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: Couldn't open file for writing - " << filename << std::endl;
            return false;
        }

        file << "P3\n"
             << width << " " << height << "\n255\n";

        for (const auto &pixel : pixels)
        {
            int r = static_cast<int>(pixel.x * 255);
            int g = static_cast<int>(pixel.y * 255);
            int b = static_cast<int>(pixel.z * 255);

            file << r << " " << g << " " << b << "\n";
        }

        file.close();
        return true;
    }

    static bool readPPM(const std::string &filename, std::vector<glm::vec3> &pixels, int &width, int &height)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: Couldn't open file for reading - " << filename << std::endl;
            return false;
        }

        std::string magic;
        file >> magic;
        if (magic != "P3")
        {
            std::cerr << "Error: Not a valid PPM file - " << filename << std::endl;
            return false;
        }

        file >> width >> height;
        int maxColor;
        file >> maxColor;

        pixels.resize(width * height);

        for (auto &pixel : pixels)
        {
            int r, g, b;
            file >> r >> g >> b;

            pixel.x = static_cast<float>(r) / 255.0f;
            pixel.y = static_cast<float>(g) / 255.0f;
            pixel.z = static_cast<float>(b) / 255.0f;
        }

        file.close();
        return true;
    }
};

// int main() {
//     // Example usage to write and read a PPM file
//     const int width = 800;
//     const int height = 600;
//     const std::string filename = "output.ppm";

//     // Creating an image (glm::vec3 values represent RGB color)
//     std::vector<glm::vec3> pixels(width * height, glm::vec3(1, 0, 0));  // Red image

//     // Writing the image to a PPM file
//     if (FileIO::writePPM(filename, pixels, width, height)) {
//         std::cout << "Image written to " << filename << std::endl;
//     } else {
//         std::cerr << "Failed to write image." << std::endl;
//         return 1;
//     }

//     // Reading the image from the PPM file
//     std::vector<glm::vec3> loadedPixels;
//     int loadedWidth, loadedHeight;

//     if (FileIO::readPPM(filename, loadedPixels, loadedWidth, loadedHeight)) {
//         std::cout << "Image read from " << filename << " with dimensions: " << loadedWidth << "x" << loadedHeight << std::endl;
//     } else {
//         std::cerr << "Failed to read image." << std::endl;
//         return 1;
//     }

//     return 0;
// }
