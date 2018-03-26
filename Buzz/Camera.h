#ifndef CAMERA_H
#define CAMERA_H


#include <glm\glm.hpp>

namespace BUZZ
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getPerspective() const;
		const glm::mat4& getOrtho();

		void move(float x, float y);
		void zoom(float zoom);

		// getters
		const glm::vec3& getPosition() const;
		const glm::vec3& getTarget() const;

		const glm::vec2& convertToWorldSpace(float x, float y);

		// setters
		void setPosition(const glm::vec3& position);
		void setFOV(float fov);

	private:
		glm::vec3 m_position;
		glm::vec3 m_target;
		glm::vec3 m_up;

		float m_fov;

		void updateCameraVectors();
	};
}


#endif // CAMERA_H