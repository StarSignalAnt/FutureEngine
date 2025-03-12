#include "GameCam.h"

GameCam::GameCam() {

	m_Position = glm::vec3(0, 0, 1);
	m_Rotation = glm::vec3(0, 0, 0);

}

void GameCam::SetPosition(glm::vec3 position) {
	m_Position = position;
}

void GameCam::SetRotation(glm::vec3 rotation) {
	m_Rotation = rotation;
}

void GameCam::Turn(glm::vec3 rotation) {
	m_Rotation += rotation;
}

void GameCam::Move(glm::vec3 delta) {
	m_Position += delta;
}