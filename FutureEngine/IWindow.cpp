#include "IWindow.h"
#include "UIHelp.h"
#include "GameInput.h"
#include "FutureApp.h"
#include "IControlGroup.h"
#include "IVerticalScroller.h"
#include "IHorizontalScroller.h"
#include <iostream>
#include "Texture2D.h"

void IWindow::Update(float delta)
{
	UpdateChildren(delta);
}

void IWindow::Render()
{
	auto pos = GetRenderPosition();

	m_TitleBG->Grab(pos.x, pos.y);
	m_ClientBG->Grab(pos.x,pos.y + 20);




//	UIHelp::DrawRect(pos-glm::vec2(1,1), m_Size+glm::vec2(2,2), glm::vec4(1.0f, 1, 1, 1.0f));
	UIHelp::DrawImageBlur(pos + glm::vec2(0,20+(m_Size.y-20)), glm::vec2(m_Size.x, -(m_Size.y-21)), m_ClientBG, glm::vec4(1, 1, 1, 1), 1.9);

	UIHelp::DrawRect(pos+glm::vec2(0,20), m_Size+glm::vec2(0,-21), glm::vec4(0.678 * 0.3, 0.847 * 0.3, 0.902 * 0.3, 0.7f));
//	UIHelp::DrawRect(pos, glm::vec2(m_Size.x, 20), glm::vec4(1,1,1, 1.0f));
// 
	//UIHelp::DrawImage(pos, glm::vec2(m_Size.x, 25),m_TitleBarImage, glm::vec4(0.678*1.8, 0.847*1.8, 0.902*1.8, 1));
	
	
	UIHelp::DrawImageBlur(pos + glm::vec2(0, 20), glm::vec2(m_Size.x, -20), m_TitleBG, glm::vec4(1,1,1,1),1.3);

	UIHelp::DrawRect(pos, glm::vec2(m_Size.x, 20), glm::vec4(0.678*0.8, 0.847*0.8 , 0.902*0.8, 0.65f));
	

	auto tpos = pos;
	pos.x += m_Size.x / 2;
	pos.y += 20 / 2;
	pos.x -= UIHelp::StrWidth(m_Text) / 2;
	pos.y -= UIHelp::StrHeight(m_Text) / 2;
	UIHelp::DrawText(pos+glm::vec2(3,3), m_Text, glm::vec4(0,0,0, 1));
	UIHelp::DrawText(pos, m_Text, glm::vec4(1,1,1, 1));
	//UIHelp::DrawText(pos + glm::vec2(m_Size.x - 15, m_Size.y - 15),"X", glm::vec4(1, 1, 1, 1));
//	UIHelp::DrawText(pos, m_Text, glm::vec4(1, 1, 1, 1));

	RenderChildren();
}

void IWindow::OnMouseDown(int button)
{
	m_Dragging = true;
	GameInput::m_Dragging = this;

}
void IWindow::OnMouseUp(int button)
{
	m_Dragging = false;
	GameInput::m_Dragging = nullptr;
}

void IWindow::OnMouseDoubleClick()
{

	if (m_CurrentArea == AREA_TITLE) {
		if (m_Size.x < FutureApp::m_Inst->GetWidth() || m_Size.y < FutureApp::m_Inst->GetHeight() || m_Position.x>0 || m_Position.y>0)
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
		
	}
}

bool IWindow::InBounds(glm::vec2 position)
{
	glm::vec2 root = GetRenderPosition();
	if (position.x > root.x && position.x < root.x + m_Size.x &&
		position.y > root.y && position.y < root.y + 25)
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

	m_CurrentArea = AREA_CLIENT;
	
	if (position.x > root.x & position.x < root.x + m_Size.x - 18)
	{
		if (position.y > root.y && position.y < root.y + m_Size.y - 18) {
			return true;
		}
	}
	return false;
	//return IControl::InBounds(position);


	return false;
}

void IWindow::InitWindow() {

	m_CloseButton = new IButton("X", glm::vec2(m_Size.x - 20, 0), glm::vec2(20, 24));
	m_MaximizeButton = new IButton("[]", glm::vec2(m_Size.x - 40, 0), glm::vec2(20, 24));
	m_MinimizeButton = new IButton("_", glm::vec2(m_Size.x - 60, 0), glm::vec2(20, 24));
	m_ClientArea = new IControlGroup(glm::vec2(1, 21), glm::vec2(m_Size.x - 1, m_Size.y - 1));
	m_YScroller = new IVerticalScroller(glm::vec2(m_Size.x - 10, 21), glm::vec2(10, m_Size.y - 31));
	m_XScroller = new IHorizontalScroller(glm::vec2(0, m_Size.y - 10), glm::vec2(m_Size.x - 13, 10));
	m_Resizer = new IButton(".", glm::vec2(m_Size.x-10,m_Size.y-10),glm::vec2(10,10));
	m_CloseButton->SetRenderBody(false);

	m_TitleBG = new Texture2D(m_Size.x, 20);
	m_ClientBG = new Texture2D(m_Size.x, m_Size.y - 20);

	m_MaximizeButton->SetRenderBody(false);
	m_MinimizeButton->SetRenderBody(false);
	AddChild(m_CloseButton);
	AddChild(m_MaximizeButton);
	AddChild(m_MinimizeButton);
	AddChild(m_ClientArea);
	AddChild(m_YScroller);
	AddChild(m_XScroller);
	AddChild(m_Resizer);

	m_Resizer->SetOnMoved([&](glm::vec2 delta) {

		//if (m_Dragging) {
			m_Size += delta;
			if (m_Size.x < 220)
			{

				float v = m_Size.x - 220;
				m_Size.x = 220;
				m_Position.x += v;
			}
			if (m_Size.y < 128) {
				float v = m_Size.y - 128;
				m_Position.y += v;
				m_Size.y = 128;
			}
			AlignWindow();
		//}

		});

	

	m_ClientArea->SetCullChildren(true);
	m_YScroller->SetOnScrolled([&](float y) {

		m_ClientArea->SetOffset(glm::vec2(m_ClientArea->GetOffset().x, -y));

		});

	m_XScroller->SetOnScrolled([&](float x) {

		m_ClientArea->SetOffset(glm::vec2(-x, m_ClientArea->GetOffset().y));

		});

	//m_ClientArea->SetOffset(glm::vec2(0, 200));



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

	m_TitleBarImage = new Texture2D("engine/ui/windowTitle.png");

}

void IWindow::AlignWindow() {

	m_CloseButton->Set(glm::vec2(m_Size.x - 20, 0));
	m_MaximizeButton->Set(glm::vec2(m_Size.x - 40, 0));
	m_MinimizeButton->Set(glm::vec2(m_Size.x - 60, 0));

	m_ClientArea->Set(glm::vec2(1, 26), glm::vec2(m_Size.x - 22, m_Size.y - 27));
	RemoveChild(m_YScroller);
	m_TitleBG->Free();
	m_TitleBG = new Texture2D(m_Size.x, 20);
	m_ClientBG->Free();
	m_ClientBG = new Texture2D(m_Size.x, m_Size.y - 20);

	m_Resizer->Set(glm::vec2(m_Size.x - 10, m_Size.y - 10), glm::vec2(10, 10));


	auto sv = m_YScroller->GetScrollPosition();
	m_YScroller = new IVerticalScroller(glm::vec2(m_Size.x - 10, 21), glm::vec2(10, m_Size.y - 31));
	
	AddChild(m_YScroller);
	int m_Height = m_ClientArea->GetMaxHeight();

	m_YScroller->SetContentHeight(m_Height);


	m_YScroller->SetOnScrolled([&](float y) {

		m_ClientArea->SetOffset(glm::vec2(m_ClientArea->GetOffset().x, -y));

		});


	m_YScroller->SetScrollPosition(sv);

	RemoveChild(m_XScroller);
	auto sh = m_XScroller->GetScrollPosition();
	m_XScroller = new IHorizontalScroller(glm::vec2(0, m_Size.y - 10), glm::vec2(m_Size.x - 13, 10));

	AddChild(m_XScroller);
	int m_Width = m_ClientArea->GetMaxWidth();

	m_XScroller->SetContentWidth(m_Width);


	m_XScroller->SetOnScrolled([&](float x) {

		m_ClientArea->SetOffset(glm::vec2(-x, m_ClientArea->GetOffset().y));

		});

	m_XScroller->SetScrollPosition(sh);
	//m_YScroller->SetScrollPosition(0);
	//float sy = -m_ClientArea->GetOffset().y;
	
	

	//std::cout << "OS:" << m_ClientArea->GetOffset().y << std::endl;

	//if(m_ClientArea->GetOffset().




}

void IWindow::AddClientControl(IControl* control) {

	m_ClientArea->AddChild(control);
	
	int m_Height = m_ClientArea->GetMaxHeight();

	m_YScroller->SetContentHeight(m_Height);
	m_XScroller->SetContentWidth(m_ClientArea->GetMaxWidth());

}

void IWindow::AfterSet() {

	AlignWindow();

}