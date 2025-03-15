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


	if (m_RenderBody || m_Over) {
		UIHelp::DrawImage(GetRenderPosition(), m_Size, m_Image, m_Color);
	}
	UIHelp::DrawText(pos,m_Text,glm::vec4(1,1,1,1));

	RenderChildren();
}

void IButton::LoadResources() {

	m_Image = new Texture2D("engine/ui/buttonframe.png");
	m_Color = glm::vec4(0.678 * 1.8, 0.847 * 1.8, 0.902 * 1.8, 1);
}

void IButton::OnMouseEnter()
{
	m_Color = glm::vec4(0.678 * 2, 0.847 * 2, 0.902 * 2, 1);
	m_Over = true;
}

void IButton::OnMouseLeave()
{
	m_Color = glm::vec4(0.678 * 1.8, 0.847 * 1.8, 0.902 * 1.8, 1);
	m_Over = false;
}


void IButton::OnMouseDown(int button)
{
	m_Color = glm::vec4(0.678 * 2.2, 0.847 * 2.2, 0.902 * 2.2, 1);
	m_Dragging = true;
	Click();

}

void IButton::OnMouseUp(int button)
{
	m_Dragging = false;
	m_Color = glm::vec4(0.678 * 2, 0.847 * 2, 0.902 * 2, 1);
}

void IButton::OnMouseDoubleClick()
{

	DoubleClick();
}

void IButton::OnMouseMove(glm::vec2 position, glm::vec2 delta) {

	if (m_Dragging) {

		Move(delta);

	}

}