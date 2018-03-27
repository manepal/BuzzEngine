#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>

#include "Window.h"

const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const float FOV = 45.0f;
namespace BUZZ
{
	Camera::Camera() :
		m_position(glm::vec3(0.0f, 0.0f, 10.0f)),
		m_target(glm::vec3(0.0f)),
		m_up(WORLD_UP),
		m_fov(FOV)
	{
	}

	Camera::~Camera()
	{
	}

	const glm::vec3& Camera::getPosition() const
	{
		return m_position;
	}

	const glm::vec3& Camera::getTarget() const
	{
		return m_target;
	}

	const glm::vec2 & Camera::convertToWorldSpace(float x, float y)
	{
		float zoom = m_fov / FOV;

		x = x * zoom + m_position.x;
		y = y * zoom + m_position.y;

		return glm::vec2(x, y);
	}

	const glm::mat4& Camera::getViewMatrix() const
	{
		return glm::lookAt(m_position, m_target, m_up);
	}

	const glm::mat4& Camera::getPerspective() const
	{
		return glm::perspective(m_fov, Window::getInstance()->getWidth() / (float)Window::getInstance()->getHeight(), 0.1f, 100.0f);
	}

	const glm::mat4 & Camera::getOrtho()
	{
		static float x = Window::getInstance()->getWidth() / 2.0f;
		static float y = Window::getInstance()->getHeight() / 2.0f;

		float zoom = m_fov / FOV;

		return glm::ortho(-x * zoom, x * zoom, -y * zoom, y * zoom, 0.1f, 100.0f);
		//return glm::ortho(-x, x, -y, y, 0.1f, 100.0f);
	}



	void Camera::move(float x, float y)
	{
		m_position.x += x;
		m_position.y += y;

		updateCameraVectors();
	}

	void Camera::zoom(float zoom)
	{
		m_fov += zoom;
	}

	void Camera::setPosition(const glm::vec3 & position)
	{
		m_position = position;
		// update the camera vector to calculate new target
		updateCameraVectors();
	}

	void Camera::setFOV(float fov)
	{
		m_fov = fov;
	}

	void Camera::updateCameraVectors()
	{
		m_target = glm::vec3(m_position.x, m_position.y, 0.0f);
	}
}