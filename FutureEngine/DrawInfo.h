#pragma once
#include "glm/common.hpp"
#include <glm/glm.hpp>  // Basic types (vec3, mat3, etc.)

class Texture2D;

class DrawInfo
{
public:

	DrawInfo() {
		m_X = new float[4];
		m_Y = new float[4];
		m_TexX = new float[4];
		m_TexY = new float[4];
	}
	void SetCoord(int coord, float x, float y);
	void SetTexCoord(int coord, float x, float y);
	void SetColor(float r, float g, float b, float a);
	void SetColor(glm::vec4 color);
	void SetTexture(Texture2D* texture);
	void SetZ(float z);
	glm::vec2 GetCoord(int coord) {
		//x = *m_X;
		//y = *m_Y;
		return glm::vec2(m_X[coord], m_Y[coord]);
	}
	glm::vec2 GetTexCoord(int coord) {
		//x = *m_TexX;
		//y = *m_TexY;
		return glm::vec2(m_TexX[coord], m_TexY[coord]);
	}
	glm::vec4 GetColor() {
		return m_Color;
	}
	Texture2D* GetTexture() {
		return m_Texture;
	}
	float GetZ() {
		return m_Z;
	}
	~DrawInfo() {
	
	}
	void Free();

private:

	float* m_X;
	float* m_Y;
	float* m_TexX;
	float* m_TexY;
	float m_Z = 0.0f;
	glm::vec4 m_Color;
	Texture2D* m_Texture;



};

