#include<iostream>
#include"glm/glm.hpp"
#include"stb_image_write.h"
#include"Core/Ray.h"



namespace BRT
{

    const float ASPECT_RATIO = 16.0 / 9.0;
    const int WIDTH = 1280;
    const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

    // Camera

    float viewport_height = 2.0;
    float viewport_width = ASPECT_RATIO * viewport_height;
    float focal_length = 1.0;

    glm::vec3 CameraOrigin  { 0, 0, 0 };
    glm::vec3 VP_Horizontal {viewport_width, 0, 0};
    glm::vec3 VP_Vertical   { 0, viewport_height, 0 };

    glm::vec3 ViewportBottomLeftCorner = CameraOrigin - VP_Horizontal / 2.f - VP_Vertical / 2.f - glm::vec3(0, 0, focal_length);

    float RayVsSphere(const glm::vec3& center, double radius, const Ray& ray) 
    {
        glm::vec3 oc = ray.GetOrigin() -    center;
        auto a = std::pow(glm::length(ray.GetDirection()),2);
        auto half_b = glm::dot(oc, ray.GetDirection());
        auto c = std::pow(glm::length(oc), 2) - radius * radius;
        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) {
            return -1.0;
        }
        else {
            return (-half_b - sqrt(discriminant)) / a;
        }
    }

    glm::vec3 RayColor(const Ray& ray)
    {
        glm::vec3 sphereCenter = glm::vec3(0, 0, -1);
        float t = RayVsSphere(sphereCenter, 0.5, ray);
        if (t > 0.0f) 
        {
            glm::vec3 N = glm::normalize(ray.PointAtDistance(t) - sphereCenter);
            return 0.5f * glm::vec3(N.x + 1, N.y + 1, N.z + 1);
        }

        glm::vec3 UnitDir = glm::normalize(ray.GetDirection());
        t = 0.5 * (UnitDir.y + 1.0);
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
         int x = (i % (BRT::WIDTH * 3) / 3);
         int y = (i / (BRT::WIDTH * 3));

         float u = float(x) / (BRT::WIDTH - 1);
         float v = float(y) / (BRT::HEIGHT - 1);

         BRT::Ray ray(BRT::CameraOrigin, BRT::ViewportBottomLeftCorner + ((float)u * BRT::VP_Horizontal + (float)v * BRT::VP_Vertical) - BRT::CameraOrigin);
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
