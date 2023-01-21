#pragma once
#include"Ray.h"

namespace BRT
{
	class Camera
	{
    public:

        Camera();
        Camera(double aspectRatio, const glm::vec2& viewportSize, const glm::vec3& origin, double focalLenght );
       

        Ray GetRay(float  u, float v) const 
        {
            return { m_Origin, m_vpLowerLeftCorner + u * m_vpHorizontalOffset + v * m_vpVerticalOffset - m_Origin };
        }

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_vpHorizontalOffset;
        glm::vec3 m_vpVerticalOffset;
        glm::vec3 m_vpLowerLeftCorner;

	};
}

