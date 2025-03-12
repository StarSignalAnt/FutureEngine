#include "GameCam.h"
#include "MathsOps.h"

GameCam::GameCam() {

	m_Position = glm::vec3(0, 0, 1);
	m_Rotation = glm::vec3(0, 0, 0);

}

void GameCam::SetPosition(glm::vec3 position) {
	m_Position = position;
}

void GameCam::SetPosition(glm::vec2 position) {
	m_Position = glm::vec3(position, 1);
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

void GameCam::Move(glm::vec2 delta) {
	m_Position += glm::vec3(delta, 0);
}

void GameCam::MoveLocal(glm::vec2 delta) {
	
	auto realMove = MathsOps::TransformCoord(delta,360.0- m_Rotation.y, 1.0f);
	
	realMove = realMove / m_Position.z;
	Move(realMove);



}

void GameCam::Zoom(float delta) {

	m_Position.z = m_Position.z + delta * m_Position.z;

}
