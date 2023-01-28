#include "Sphere.h"
#include <glm/gtx/norm.hpp>


namespace BRT
{
    bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitInfo& info) const 
    {
        glm::vec3 oc = ray.GetOrigin() - m_Center;
        double a = std::pow(glm::length(ray.GetDirection()), 2);
        double half_b = glm::dot(oc, ray.GetDirection());
        double c = glm::length2(oc) - m_Radius * m_Radius;
        double discriminant = half_b * half_b - a * c;

      
        if (discriminant < 0) return false;
        double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (-half_b - sqrtd) / a;
        if (root < tMin || tMax < root) {
            root = (-half_b + sqrtd) / a;
            if (root < tMin || tMax < root)
                return false;
        }

        info.IntersectionTime = root;
        info.Point = ray.PointAtDistance(root);
        info.Normal = (info.Point - m_Center) / (float)m_Radius;
        info.SetFaceNormal(ray, info.Normal);
        info.Material = m_Material;

        return true;
    }


}