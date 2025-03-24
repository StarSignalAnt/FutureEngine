#pragma once
#include <glm/glm.hpp>

class Texture2D;

class RenderTarget2D
{
public:
	RenderTarget2D(unsigned int width, unsigned int height);
	//	~RenderTarget2D();
	void Bind();
	void Unbind();
	void Clear(glm::vec3 col);
	void SetTexture(Texture2D* texture);
	Texture2D* GetTexture();
	unsigned int GetFrameBuffer();
	unsigned int GetDepthBuffer();
	unsigned int GetWidth();
	unsigned int GetHeight();
	void Free();

private:

	unsigned int m_TextureID;
	unsigned int m_FrameBuffer;
	unsigned int m_DepthBuffer;
	unsigned int m_Width;
	unsigned int m_Height;

};
