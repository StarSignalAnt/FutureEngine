#include "SmartDraw.h"
#include "Texture2D.h"
#include "MathsOps.h"
#include "DrawList.h"
#include "DrawInfo.h"
#include "ShaderModule.h"
#include <glm/glm.hpp>
#include "FutureApp.h"
#include <glm/gtc/matrix_transform.hpp>
SmartDraw::SmartDraw()
{

	m_SM = new ShaderModule("engine/shader/drawVS.glsl", "engine/shader/drawFS.glsl");
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

void SmartDraw::Begin()
{

	for (auto list : m_DrawLists)
	{
		list->Free();
		delete list;
	}
	m_DrawLists.clear();
	
	m_CurrentZ = 0.01f;

//	m_SMSimple->Bind();
//	m_SMSimple->SetUniformMat4("u_Projection", m_ProjectionMatrix);

}

DrawInfo* SmartDraw::Draw(glm::vec2 position, glm::vec2 size, glm::vec4 color, Texture2D* texture, float rotation, float scale)
{

	auto list = GetList(texture);

	DrawInfo* info = new DrawInfo;

	float tx0, tx1, tx2, tx3;
	float ty0, ty1, ty2, ty3;

	tx0 = -size.x / 2;
	tx1 = size.x / 2;
	tx2 = size.x / 2;
	tx3 = -size.x / 2;

	ty0 = -size.y / 2;

	ty1 = -size.y / 2;
	ty2 = size.y / 2;
	ty3 = size.y / 2;

	auto v1 = MathsOps::TransformCoord(glm::vec2(tx0, ty0), rotation, scale);
	auto v2 = MathsOps::TransformCoord(glm::vec2(tx1, ty1), rotation, scale);
	auto v3 = MathsOps::TransformCoord(glm::vec2(tx2, ty2), rotation, scale);
	auto v4 = MathsOps::TransformCoord(glm::vec2(tx3, ty3), rotation, scale);

	info->SetCoord(0, position.x + v1.x, position.y + v1.y);
	info->SetCoord(1, position.x + v2.x, position.y + v2.y);
	info->SetCoord(2, position.x + v3.x, position.y + v3.y);
	info->SetCoord(3, position.x + v4.x, position.y + v4.y);




//	info->SetCoord(0, x0, y0);
//	info->SetCoord(1, x1, y1);
//	info->SetCoord(2, x2, y2);
//	info->SetCoord(3, x3, y3);


	info->SetTexCoord(0, 0, 0);
	info->SetTexCoord(1, 1, 0);
	info->SetTexCoord(2, 1, 1);
	info->SetTexCoord(3, 0, 1);
	
	info->SetColor(color);

	info->SetTexture(texture);

	info->SetZ(m_CurrentZ);

	m_CurrentZ += 0.0001f;

	list->Add(info);

	return info;


}


DrawInfo* SmartDraw::DrawDirect(glm::vec2 position, glm::vec2 size, glm::vec4 color, Texture2D* texture)
{

	auto list = GetList(texture);

	DrawInfo* info = new DrawInfo;



	

	info->SetCoord(0, position.x , position.y);
	info->SetCoord(1, position.x + size.x, position.y);
	info->SetCoord(2, position.x + size.x, position.y + size.y);
	info->SetCoord(3, position.x , position.y + size.y);




	//	info->SetCoord(0, x0, y0);
	//	info->SetCoord(1, x1, y1);
	//	info->SetCoord(2, x2, y2);
	//	info->SetCoord(3, x3, y3);


	info->SetTexCoord(0, 0, 0);
	info->SetTexCoord(1, 1, 0);
	info->SetTexCoord(2, 1, 1);
	info->SetTexCoord(3, 0, 1);

	info->SetColor(color);

	info->SetTexture(texture);

	info->SetZ(m_CurrentZ);

	m_CurrentZ += 0.0001f;

	list->Add(info);

	return info;


}

void SmartDraw::End()
{
	m_ProjectionMatrix = glm::ortho(0.0f, (float)FutureApp::m_Inst->GetWidth(), (float)FutureApp::m_Inst->GetHeight(), 0.0f, -1.0f, 1.0f);
	if (pdata == nullptr) {

		//pdata = (float*)malloc(100000 * 9 * 4)


	}
	if (VAO!=0)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}
	// Iterate over the draw lists
	for (auto list : m_DrawLists) {
		m_SM->Bind();


		m_SM->SetMat4("uProjection", m_ProjectionMatrix);

		auto tex = list->GetList()[0]->GetTexture();
		tex->Bind(0);
		auto norm = list->GetList()[0]->GetNormalTexture();
		if (norm != nullptr) {
			norm->Bind(1);
			m_SM->SetInt("feNormalMap", 1);
		}

		m_SM->SetInt("uTexture", 0);
	

		// Get packed vertex data
		float* data = GetData(list);
		size_t vertexCount = list->GetList().size() * 6; // 4 verts per quad
		size_t dataSize = vertexCount * 12 * sizeof(float); // Each vertex has 9 floats

		// Generate indices for triangle list (6 indices per quad)
		size_t quadCount = list->GetList().size();
		int indexCount = quadCount * 6;

		// Create VAO once if not created
		if (VAO == 0) {
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
		}


		// Create VBO if not created, and allocate buffer space with correct size
		if (VBO == 0) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_SIZE*2, nullptr, GL_DYNAMIC_DRAW);  // Allocate the buffer with the correct size
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
		}

		// Upload vertex data to VBO
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, data);




		// Define vertex attributes
		GLsizei stride = 12 * sizeof(float);

		// Position (vec3)


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);

		// TexCoord (vec2)
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Color (vec4)
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(9 * sizeof(float)));
		glEnableVertexAttribArray(3);
		// Draw the elements
		//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

		glDrawArrays(GL_TRIANGLES, 0, list->GetList().size() * 6);


		// Free the vertex data after use
	//	free(data);

		// Unbind texture and reset the shader program
		tex->Unbind(0);
		if (norm != nullptr) {
			norm->Unbind(1);
		}
	}

	// Unbind the VAO and shader
	glBindVertexArray(0);
	m_SM->Unbind();
}
DrawList* SmartDraw::GetList(Texture2D* texture)
{
	for (auto list : m_DrawLists)
	{
		if (list->GetTexture() == texture)
		{
			return list;
		}
	}
	auto list = new DrawList();
	list->SetTexture(texture);
	m_DrawLists.push_back(list);
	return list;
}

inline void SetVertexData(float* data, int& index, const glm::vec2& pos, float z, const glm::vec2& texCoord, const glm::vec4& color,const glm::vec3& real) {
	data[index++] = pos.x;
	data[index++] = pos.y;
	data[index++] = z;
	data[index++] = texCoord.x;
	data[index++] = texCoord.y;
	data[index++] = color.r;
	data[index++] = color.g;
	data[index++] = color.b;
	data[index++] = color.a;
	data[index++] = real.x;
	data[index++] = real.y;
	data[index++] = real.z;
}

float* SmartDraw::GetData(DrawList* list) {
	// Each info will now require 6 vertices instead of 4
	int size = list->GetList().size() * 9 * 9 * sizeof(float);  // 6 vertices per quad, 9 floats per vertex

	float* data = nullptr;
	if (size > pre_size) {
		pre_size = size;
		if (data != nullptr) {
			free(data);
		}
		pdata = (float*)malloc(size);
		data = pdata;
	}
	else {
		data = pdata;
	//	pre_size = size;
	}

	//float* data = pdata;// (float*)malloc(size);


	int index = 0;

	for (auto info : list->GetList()) {
		// Retrieve the coordinates of the 4 corners of the quad
		auto pos0 = info->GetCoord(0);
		auto pos1 = info->GetCoord(1);
		auto pos2 = info->GetCoord(2);
		auto pos3 = info->GetCoord(3);

		// Common Z coordinate and texture coordinates, color values
		float z = info->GetZ();
		auto texCoord0 = info->GetTexCoord(0);
		auto texCoord1 = info->GetTexCoord(1);
		auto texCoord2 = info->GetTexCoord(2);
		auto texCoord3 = info->GetTexCoord(3);
		auto color = info->GetColor();

		auto real0 = info->GetRealCoord(0);
		auto real1 = info->GetRealCoord(1);
		auto real2 = info->GetRealCoord(2);
		auto real3 = info->GetRealCoord(3);

		// First triangle (using vertices 0, 1, 2)
		SetVertexData(data, index, pos0, z, texCoord0, color,real0);
		SetVertexData(data, index, pos1, z, texCoord1, color,real1);
		SetVertexData(data, index, pos2, z, texCoord2, color,real2);

		// Second triangle (using vertices 2, 3, 0)
		SetVertexData(data, index, pos2, z, texCoord2, color,real2);
		SetVertexData(data, index, pos3, z, texCoord3, color,real3);
		SetVertexData(data, index, pos0, z, texCoord0, color,real0);
	}

	return data;
}

void SmartDraw::SetShaderModule(ShaderModule* module) {

	m_SM = module;

}