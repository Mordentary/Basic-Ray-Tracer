#pragma once
#include"Hittable.h"

namespace BRT 
{
	class Sphere : public Hittable
	{

    public:
        Sphere() = default;
        Sphere(const glm::vec3& center, double rad) : m_Center(center), m_Radius(rad) {};

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& info) const override;


    private:
        glm::vec3 m_Center;
        double m_Radius;
	};
}

