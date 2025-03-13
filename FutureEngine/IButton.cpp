#include "IButton.h"
#include "Texture2D.h"
#include "UIHelp.h"

void IButton::Update(float delta)
{

	UpdateChildren(delta);
}

void IButton::Render()
{

	UIHelp::DrawImage(GetRenderPosition(), m_Size, m_Image, m_Color);
	UIHelp::DrawText(GetRenderPosition(), "This is a test!", m_Color);

	RenderChildren();
}

void IButton::LoadResources() {

	m_Image = new Texture2D("engine/ui/buttonframe.png");

}

void IButton::OnMouseEnter()
{
	m_Color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
}

void IButton::OnMouseLeave()
{
	m_Color = glm::vec4(1, 1, 1, 1);
}

void IButton::OnMouseDown(int button)
{
	m_Color = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
}

void IButton::OnMouseUp(int button)
{
	m_Color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
}