#include<iostream>
#include"glm/glm.hpp"
#include"stb_image_write.h"
#include"Core/Ray.h"



namespace BRT
{



    const float ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 400;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

    // Camera

    float viewport_height = 2.0;
    float viewport_width = ASPECT_RATIO * viewport_height;
    float focal_length = 1.0;

    glm::vec3 CameraOrigin{ 0, 0, 0 };
    glm::vec3 horizontal {viewport_width, 0, 0};
    glm::vec3 vertical      { 0, viewport_height, 0 };

    glm::vec3 lower_left_corner = CameraOrigin - horizontal / 2.f - vertical / 2.f - glm::vec3(0, 0, focal_length);

    glm::vec3 RayColor(const Ray& ray)
    {
        glm::vec3 unit_direction =  glm::normalize(ray.GetDirection());
        auto t = 0.5 * (unit_direction.y + 1.0);
        return glm::mix(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.5, 0.7, 1.0), t);
    }

    void WriteColor(unsigned char* data, uint32_t index, glm::vec3 color) 
    {
        data[index] = static_cast<char>(color.r * 255 );         // Red channel
        data[index + 1] = static_cast<char>(color.g * 255 );    // Green channel
        data[index + 2] = static_cast<char>(color.b * 255 );    // Blue channel
    }
}

int main()
{
   

    // Render
    std::cout << "Resolution:" << BRT::WIDTH << " X " << BRT::HEIGHT << "\n";

     unsigned char* data = new unsigned char[BRT::HEIGHT * BRT::WIDTH * 3];

     //std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
    // Generate the gradient
     for (int i = 0; i < BRT::HEIGHT * BRT::WIDTH * 3; i += 3)
     {
         int x = i % (BRT::WIDTH * 3) / 3;
         int y = i / (BRT::WIDTH * 3);

         BRT::Ray ray(BRT::CameraOrigin, BRT::lower_left_corner + (float)x * BRT::horizontal + (float)y * BRT::vertical - BRT::CameraOrigin);
         glm::vec3 pixelColor = BRT::RayColor(ray);
         BRT::WriteColor(data, i, pixelColor);
     }


    stbi_flip_vertically_on_write(true);

    int result = stbi_write_jpg("outputs/jpg_test_.jpg", BRT::WIDTH, BRT::HEIGHT, 3, data, 100);

    if (!result) {
        std::cout << "WRITE ERROR!!";
    }

    delete[] data;

    return 0;
}
