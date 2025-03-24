#include "RenderTarget2D.h"

#include "Texture2D.h"

#include <glad/glad.h>
#include <iostream>
#include "FutureApp.h"


RenderTarget2D::RenderTarget2D(unsigned int width,unsigned int height) {

	m_Width = width;
	m_Height = height;
	glGenFramebuffers(1, &m_FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);
	glGenRenderbuffers(1, &m_DepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}



void RenderTarget2D::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
	FutureApp::m_Inst->SetBind(this);
}

void RenderTarget2D::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	FutureApp::FutureApp::m_Inst->SetBind(nullptr);
}

void RenderTarget2D::Clear(glm::vec3 color) {
	glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderTarget2D::SetTexture(Texture2D* texture) {
    m_TextureID = texture->GetID();
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);
}

Texture2D* RenderTarget2D::GetTexture() {
    return new Texture2D(m_TextureID, m_Width, m_Height);
}

unsigned int RenderTarget2D::GetFrameBuffer() {
    return m_FrameBuffer;
}

unsigned int RenderTarget2D::GetDepthBuffer() {
    return m_DepthBuffer;
}

unsigned int RenderTarget2D::GetWidth() {
    return m_Width;
}

unsigned int RenderTarget2D::GetHeight() {
    return m_Height;
}


void RenderTarget2D::Free() {

	glDeleteFramebuffers(1, &m_FrameBuffer);
	glDeleteRenderbuffers(1,&m_DepthBuffer);

}