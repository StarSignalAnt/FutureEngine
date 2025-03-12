#pragma once
#include <glm/glm.hpp>

class GameCam
{
public:

	GameCam();
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetRotation() const { return m_Rotation; }
	void Turn(glm::vec3 rotation);
	void Move(glm::vec3 delta);

private:

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;


};

