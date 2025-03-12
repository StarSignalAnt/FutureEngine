#pragma once
#include "GameObj.h"

class GameLight : public GameObj
{
public:

	GameLight() : m_Diffuse(glm::vec3(1, 1, 1)), m_Range(512) {};

	void SetRange(float range);
	float GetRange();


private:

	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	float m_Range;

};

