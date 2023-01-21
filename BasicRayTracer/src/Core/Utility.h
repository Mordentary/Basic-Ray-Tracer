#pragma once
#include<random>

namespace BRT
{

    //Constans
    const double infinity = std::numeric_limits<double>::infinity();

    inline double RandomDouble(double min, double max) {
        std::uniform_real_distribution<double> distribution(min, max);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double RandomDouble() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }


    inline static glm::vec3 RandomVector() {
        return { RandomDouble(), RandomDouble(), RandomDouble() };
    }

    inline static glm::vec3 RandomVector(double min, double max) {
        return { RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max) };
    }


    glm::vec3 random_in_unit_sphere() {
        while (true) {
            glm::vec3 point = RandomVector(-1, 1);
            if (glm::length(point) >= 1) continue;
            return point;
        }
    }
}