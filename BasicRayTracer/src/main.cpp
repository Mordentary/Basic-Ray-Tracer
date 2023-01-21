#include<iostream>
#include"glm/glm.hpp"
#include"stb_image_write.h"
#include"Core/Ray.h"
#include"Core/HittableList.h"
#include"Core/Sphere.h"
#include"Core/Utility.h"
#include"Core/Camera.h"

namespace BRT
{
    

    // Screen

    const float ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 1280;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
    const int SAMPLES_PER_PIXEL = 16;
    const int MAX_DEPTH = 6;


    // Camera and Viewport

    float viewport_height = 2.0;
    float viewport_width = ASPECT_RATIO * viewport_height;
    float focal_length = 1.0;

    glm::vec3 CameraOrigin  { 0, 0, 0 };
    glm::vec3 VP_Horizontal {viewport_width, 0, 0};
    glm::vec3 VP_Vertical   { 0, viewport_height, 0 };

    glm::vec3 ViewportBottomLeftCorner = CameraOrigin - VP_Horizontal / 2.f - VP_Vertical / 2.f - glm::vec3(0, 0, focal_length);



    glm::vec3 RayColor(const Ray& ray, const HittableList& world, int rayDepth)
    {
        if (rayDepth <= 0)
            return { 0, 0, 0 };
        HitInfo info;
        if (world.Hit(ray, 0, infinity, info)) {

            glm::vec3 target = info.Point + info.Normal + random_in_unit_sphere();
            return 0.5f * RayColor(Ray{ info.Point, target - info.Point }, world, rayDepth - 1);

          //  return 0.5f * (info.Normal + glm::vec3(1, 1, 1));
        }
        glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
        float t = 0.5 * (unitDirection.y + 1.0);
        return float(1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
    }

    void WriteColor(unsigned char* data, uint32_t index, glm::vec3& color) 
    {

        // Divide the color by the number of samples.
        auto scale = 1.0 / SAMPLES_PER_PIXEL;
        color.r *= scale;
        color.g *= scale;
        color.b *= scale;

        data[index] = static_cast<char>(256 * glm::clamp(color.r, 0.0f, 0.999f));         // Red channel
        data[index + 1] = static_cast<char>(256 * glm::clamp(color.g, 0.0f, 0.999f));    // Green channel
        data[index + 2] = static_cast<char>(256 * glm::clamp(color.b, 0.0f, 0.999f));    // Blue channel
    }
}

int main()
{
   
    BRT::HittableList world;
    world.AddObject(BRT::CreateShared<BRT::Sphere>(glm::vec3(0, 0, -1), 0.5));
    world.AddObject(BRT::CreateShared<BRT::Sphere>(glm::vec3(0, -100.5, -1), 100));


    BRT::Camera camera;
    // Render
    std::cout << "Resolution:" << BRT::WIDTH << " X " << BRT::HEIGHT << "\n";

     unsigned char* data = new unsigned char[BRT::HEIGHT * BRT::WIDTH * 3];

     //std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
    // Generate the gradient
     for (int i = 0; i < BRT::HEIGHT * BRT::WIDTH * 3; i += 3)
     {
         int x = (i % (BRT::WIDTH * 3) / 3);
         int y = (i / (BRT::WIDTH * 3));

         glm::vec3 pixelColor(0, 0, 0);
         for (int s = 0; s < BRT::SAMPLES_PER_PIXEL; ++s) 
         {
             auto u = (x + BRT::RandomDouble()) / (BRT::WIDTH  - 1);
             auto v = (y + BRT::RandomDouble()) / (BRT::HEIGHT - 1);
             BRT::Ray ray = camera.GetRay(u, v);
             pixelColor += BRT::RayColor(ray, world, BRT::MAX_DEPTH);
         }
         BRT::WriteColor(data, i, pixelColor);

         int percentage = 100 * i / (BRT::HEIGHT * BRT::WIDTH * 3);

         std::cerr << "\rLoading: " << percentage << "%" << std::flush;
     }

     std::cerr << "\nRendering complete!\n";

    stbi_flip_vertically_on_write(true);

    int result = stbi_write_jpg("outputs/jpg_test_.jpg", BRT::WIDTH, BRT::HEIGHT, 3, data, 100);

    if (!result) {
        std::cout << "WRITE ERROR!!";
    }

    delete[] data;

    return 0;
}
