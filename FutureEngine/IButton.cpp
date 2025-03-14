#include "IButton.h"
#include "Texture2D.h"
#include "UIHelp.h"

void IButton::Update(float delta)
{

	UpdateChildren(delta);
}

void IButton::Render()
{

	auto pos = GetRenderPosition();

	pos.x = pos.x + m_Size.x / 2 - UIHelp::StrWidth(m_Text) / 2;
	pos.y = pos.y + m_Size.y / 2 - UIHelp::StrHeight(m_Text) / 2;


	UIHelp::DrawImage(GetRenderPosition(), m_Size, m_Image, m_Color);
	UIHelp::DrawText(pos,m_Text, m_Color);

	RenderChildren();
}

void IButton::LoadResources() {

	m_Image = new Texture2D("engine/ui/buttonframe.png");

}

void IButton::OnMouseEnter()
{
	m_Color = glm::vec4(1.3f, 1.3f, 1.3f, 1.0f);
}

void IButton::OnMouseLeave()
{
	m_Color = glm::vec4(1, 1, 1, 1);
}

void IButton::OnMouseDown(int button)
{
	m_Color = glm::vec4(1.3f, 1.6f, 1.6f, 1.0f);
}

void IButton::OnMouseUp(int button)
{
	m_Color = glm::vec4(1.3f,1.3f,1.3f, 1.0f);
}