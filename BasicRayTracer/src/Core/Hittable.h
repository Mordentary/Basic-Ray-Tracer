#pragma once
#include "Ray.h"


namespace BRT
{

	struct HitInfo {
		glm::vec3 Point;
		glm::vec3 Normal;
		double IntersectionTime;
		bool IsNormalOutward;

		inline void SetFaceNormal(const Ray& r, const glm::vec3& outward_normal) {
			IsNormalOutward = glm::dot(r.GetDirection(), outward_normal) < 0;
			Normal = IsNormalOutward ? outward_normal : -outward_normal;
		}
	};

	class Hittable
	{
	public:
		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& info) const = 0;
	};

}