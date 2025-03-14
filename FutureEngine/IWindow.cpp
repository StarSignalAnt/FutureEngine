#include "IWindow.h"
#include "UIHelp.h"
#include "GameInput.h"
#include "FutureApp.h"
void IWindow::Update(float delta)
{
	UpdateChildren(delta);
}

void IWindow::Render()
{
	auto pos = GetRenderPosition();

	UIHelp::DrawRect(pos-glm::vec2(1,1), m_Size+glm::vec2(2,2), glm::vec4(1.0f, 1, 1, 1.0f));
	UIHelp::DrawRect(pos, m_Size, glm::vec4(0.25f, 0.25f, 0.25f, 1.0f));
	UIHelp::DrawRect(pos, glm::vec2(m_Size.x, 20), glm::vec4(1,1,1, 1.0f));
	UIHelp::DrawRect(pos, glm::vec2(m_Size.x, 19), glm::vec4(0.45f, 0.45f, 0.45f, 1.0f));

	UIHelp::DrawText(pos + glm::vec2(5, 3), m_Text, glm::vec4(1, 1, 1, 1));
//	UIHelp::DrawText(pos, m_Text, glm::vec4(1, 1, 1, 1));

	RenderChildren();
}

void IWindow::OnMouseDown(int button)
{
	m_Dragging = true;
}

void IWindow::OnMouseUp(int button)
{
	m_Dragging = false;
}

void IWindow::OnMouseDoubleClick()
{

	if (m_CurrentArea == AREA_TITLE) {
		if (m_Size.x < FutureApp::m_Inst->GetWidth() || m_Size.y < FutureApp::m_Inst->GetHeight())
		{
			m_MaximizeButton->Click();
		}
		else {
			m_MinimizeButton->Click();
		}
	}
}

void IWindow::OnMouseMove(glm::vec2 position, glm::vec2 delta)
{
	if (m_CurrentArea == AREA_TITLE) {
		if (m_Dragging) {
			m_Position += delta;
		}
	}
	if (m_CurrentArea == AREA_RESIZER)
	{
		if (m_Dragging) {
			m_Size += delta;
			if (m_Size.x < 220)
			{

				float v = m_Size.x - 220;
				m_Size.x = 220;
				m_Position.x += v;
			}
			if (m_Size.y < 64) {
				float v = m_Size.y - 64;
				m_Position.y += v;
				m_Size.y = 64;
			}
			AlignWindow();
		}
	}
}

bool IWindow::InBounds(glm::vec2 position)
{
	glm::vec2 root = GetRenderPosition();
	if (position.x > root.x && position.x < root.x + m_Size.x &&
		position.y > root.y && position.y < root.y + 20)
	{
		m_CurrentArea = AREA_TITLE;
		return true;
	}

	if (position.x > root.x + m_Size.x - 16 && position.x<root.x + m_Size.x &&
		position.y>root.y + m_Size.y - 16 && position.y < root.y + m_Size.y)
	{
		m_CurrentArea = AREA_RESIZER;
		return true;
	}

	return false;
}

void IWindow::InitWindow() {

	m_CloseButton = new IButton("X", glm::vec2(m_Size.x - 20, 0), glm::vec2(20, 19));
	m_MaximizeButton = new IButton("[]", glm::vec2(m_Size.x - 40, 0), glm::vec2(20, 19));
	m_MinimizeButton = new IButton("_", glm::vec2(m_Size.x - 60, 0), glm::vec2(20, 19));
	
	AddChild(m_CloseButton);
	AddChild(m_MaximizeButton);
	AddChild(m_MinimizeButton);

	m_MinimizeButton->SetOnClick([&]() {
		if (m_OriginalSize.x > 0 && m_OriginalSize.y > 0) {
			m_Position = m_OriginalPosition;
			m_Size = m_OriginalSize;
			AlignWindow();
		}
		//.m_Size = glm::vec2(m_Size.x, 20);
		});

	m_MaximizeButton->SetOnClick([&]() {


		auto pos = GetRenderPosition();
		if (pos.x > 0 || pos.y > 0 || m_Size.x < FutureApp::m_Inst->GetWidth() || m_Size.y < FutureApp::m_Inst->GetHeight())
		{
			m_OriginalPosition = m_Position;
			m_OriginalSize = m_Size;
			m_Position = glm::vec2(0, 0);
			m_Size = glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight());
			AlignWindow();
		}
		
//		//if(m_Position.x>0 || m_Position.y )

		});

	m_CloseButton->SetOnClick([&]() {

		m_RootControl->RemoveChild(this);

		});


}

void IWindow::AlignWindow() {

	m_CloseButton->Set(glm::vec2(m_Size.x - 20, 0));
	m_MaximizeButton->Set(glm::vec2(m_Size.x - 40, 0));
	m_MinimizeButton->Set(glm::vec2(m_Size.x - 60, 0));



}