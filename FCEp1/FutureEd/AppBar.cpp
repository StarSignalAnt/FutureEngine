#include "AppBar.h"
#include "UIHelp.h"
#include "AppStart.h"
#include "AppButton.h"
#include "IWindow.h"
#include "FPApps.h"

AppBar::AppBar(glm::vec2 position, glm::vec2 size) {

	m_Position = position;
	m_Size = size;

	m_AppStart = new AppStart(glm::vec2(16, -10), glm::vec2(64, 40));

	m_DockType = DockType::m_Down;

	AddChild(m_AppStart);
	SetIgnoreScissor(true);

}

void AppBar::Update(float delta) {

}

void AppBar::Render() {

	UIHelp::DrawImageWithBG(GetRenderPosition(), GetSize(), glm::vec4(1, 1, 1, 1));

	UIHelp::DrawRect(GetRenderPosition() + glm::vec2(98, 0), glm::vec2(2, m_Size.y), glm::vec4(1, 1, 1, 1));

	RenderChildren();

}
int AppBar::NextX() {


	int x = 120;
	for (auto window : m_Windows) {

		x = x + UIHelp::StrWidth(window->GetText()) + 60;

	}

	return x;
}

void AppBar::RegisterWindow(IWindow* window,FPApp* app) {

	
	auto button = new AppButton;
	
	int bx =  NextX();

	button->Set(glm::vec2(bx, 5), glm::vec2(UIHelp::StrWidth(window->GetText())+45, m_Size.y - 10));
	button->SetText(window->GetText());
	button->SetWindow(window);
	button->SetImage(app->GetIcon());

	AddChild(button);
	//m_Window = window;
	m_Windows.push_back(window);

}