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
		UIHelp::DrawOutlineRect(GetRenderPosition()+glm::vec2(-1,-1), m_Size+glm::vec2(2,2), glm::vec4(0.5, 0.5, 0.5, 1.0));
		UIHelp::DrawRect(GetRenderPosition(), m_Size, m_Color);
	}
	if (m_Image != nullptr) {
		UIHelp::DrawImage(GetRenderPosition(), GetSize(), m_Image, glm::vec4(1,1,1,1));
	}
	else {
		UIHelp::DrawText(pos, m_Text, glm::vec4(1, 1, 1, 1));
	}
	RenderChildren();
}

void IButton::LoadResources() {

//	m_Image = new Texture2D("engine/ui/buttonframe.png");
	m_Color = glm::vec4(0.1,0.1,0.1, 1);
}

void IButton::OnMouseEnter()
{
	m_Color = glm::vec4(0.15,0.15,0.15, 1);
	m_Over = true;
}

void IButton::OnMouseLeave()
{
	m_Color = glm::vec4(0.1,0.1,0.1, 1);
	m_Over = false;
}


void IButton::OnMouseDown(int button)
{
	m_Color = glm::vec4(0.3,0.3,0.3, 1);
	m_Dragging = true;
	Click(m_Data);

}

void IButton::OnMouseUp(int button)
{
	m_Dragging = false;
	m_Color = glm::vec4(0.15,0.15,0.15, 1);
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