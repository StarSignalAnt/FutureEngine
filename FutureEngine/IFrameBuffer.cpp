#include "IFrameBuffer.h"
#include "RenderTarget2D.h"
#include "UIHelp.h"
#include <glad/glad.h>

IFrameBuffer::IFrameBuffer(glm::vec2 position, glm::vec2 size) {

	m_RT = new RenderTarget2D(size.x,size.y);
	Set(position, size);

}

void IFrameBuffer::PreRender() {


	UIHelp::RemoveScissor();
	if (m_Size.x != m_RT->GetWidth() || m_Size.y != m_RT->GetHeight()) {
		m_RT = new RenderTarget2D(m_Size.x, m_Size.y);
	}
	m_RT->Bind();
	m_RT->Clear(glm::vec3(0,0,0));
	CallPreRender();
	m_RT->Unbind();

	PreRenderChildren();


	glClearColor(0.3, 0.3, 0.3, 1.0f);


}

void IFrameBuffer::Render() {


	auto pos = GetRenderPosition() + glm::vec2(0, m_Size.y);
	auto size = m_Size;
	size.y = -size.y;

	UIHelp::DrawImage(pos,size, m_RT->GetTexture(), m_Color);
	

}

void IFrameBuffer::Update(float delta) {


}