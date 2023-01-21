#include "Camera.h"


namespace BRT
{
    //DefaultCamera 
    Camera::Camera()
        :
        m_Origin(0.0f),
        m_vpVerticalOffset(glm::vec3(0.0, 2.0f, 0.0)),
        m_vpHorizontalOffset(glm::vec3(2.0f * (16.f/9.f), 0.0, 0.0)),
        m_vpLowerLeftCorner(m_Origin - m_vpHorizontalOffset / 2.f - m_vpVerticalOffset / 2.f - glm::vec3(0, 0, 1.0f))

    {
    }
    Camera::Camera(double aspectRatio, const glm::vec2& viewportSize, const glm::vec3& origin, double focalLenght = 1.0)
        : 
        m_Origin(origin), 
        m_vpHorizontalOffset(glm::vec3(viewportSize.x, 0.0, 0.0)), 
        m_vpVerticalOffset(glm::vec3(0.0, viewportSize.y, 0.0)),
        m_vpLowerLeftCorner(m_Origin - m_vpHorizontalOffset / 2.f - m_vpVerticalOffset / 2.f - glm::vec3(0, 0, focalLenght))
    {
    }
}