#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
class DrawList;
class Texture2D;
class ShaderModule;

class SmartDraw
{
public:

	SmartDraw();
	void Begin();
	void Draw(glm::vec2 position, glm::vec2 size, glm::vec4 color, Texture2D* texture,float rotation=0.0f,float scale=1.0f);
	void End();
	DrawList* GetList(Texture2D* texture);
	float* GetData(DrawList* list);

private:

	std::vector<DrawList*> m_DrawLists;
	ShaderModule* m_SMSimple;
	float m_CurrentZ = 0.01f;
	glm::mat4 m_ProjectionMatrix;
	GLuint VAO, VBO, EBO;
	size_t indexCount;

	const GLuint MAX_VERTEX_SIZE = 54000000;
	const GLuint MAX_INDEX_SIZE = 9000000;
	float* pdata = nullptr;
	int pre_size = 0;

};

