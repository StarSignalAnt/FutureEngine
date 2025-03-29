#include "AppMenu.h"
#include "UIHelp.h"
#include "IMainMenu.h"
#include "IButton.h"
#include "FutureApp.h"
#include "IVerticalMenu.h"
#include "FPApp.h"
#include "FuturePlatform.h"

AppMenu::AppMenu(glm::vec2 position, glm::vec2 size) {

	m_Position = position;
	m_Size = size;

	auto stop = new IButton("Exit", glm::vec2(m_Size.x-105, m_Size.y - 25), glm::vec2(100, 20));
	AddChild(stop);
	stop->SetOnClick([&](void* data) {

		FutureApp::m_Inst->PopState();

		});
	SetIgnoreScissor(true);

}

void AppMenu::Update(float delta) {

}

void AppMenu::Render() {


	UIHelp::DrawOutlineRect(GetRenderPosition() + glm::vec2(-1, -1), GetSize() + glm::vec2(2, 2), glm::vec4(1, 1, 1, 1));
	UIHelp::DrawImageWithBG(GetRenderPosition(), GetSize(), glm::vec4(1, 1, 1, 0.75));

	int dy = 100;

	for (auto item : m_Items) {


		UIHelp::DrawOutlineRect(GetRenderPosition() + glm::vec2(0, dy - 5), glm::vec2(m_Size.x, UIHelp::StrHeight(item->m_Name, 1.3) + 10), glm::vec4(1, 1, 1, 1));

		if (item == m_OverItem) {

			UIHelp::DrawRect(GetRenderPosition() + glm::vec2(1, dy - 4), glm::vec2(m_Size.x-2, UIHelp::StrHeight(item->m_Name, 1.3) + 8), glm::vec4(0.3,0.3,0.3, 0.75));
			item->m_DrawX = 0;
			item->m_DrawY = dy - 4;

		}

		UIHelp::DrawText(GetRenderPosition() + glm::vec2(10, dy), item->m_Name, glm::vec4(1, 1, 1, 1),1.15);


		dy = dy + UIHelp::StrHeight(item->m_Name,1.3) + 10;

	}

	RenderChildren();
}

void AppMenu::AddItem(MenuItem* item) {

	m_Items.push_back(item);

}

void AppMenu::OnMouseMove(glm::vec2 position, glm::vec2 delta) {

	int dy = 100;

	m_OverItem = nullptr;

	for (auto item : m_Items) {


	//	UIHelp::DrawOutlineRect(GetRenderPosition() + glm::vec2(0, dy - 5), glm::vec2(m_Size.x, UIHelp::StrHeight(item->m_Name, 1.3) + 10), glm::vec4(1, 1, 1, 1));
//		UIHelp::DrawText(GetRenderPosition() + glm::vec2(10, dy), item->m_Name, glm::vec4(1, 1, 1, 1), 1.3);

		if (position.y >= dy - 5 && position.y <= (dy - 5) + UIHelp::StrHeight(item->m_Name, 1.3) + 10)
		{
			m_OverItem = item;
		}

		dy = dy + UIHelp::StrHeight(item->m_Name, 1.3) + 10;

	}


}

void AppMenu::OnMouseDown(int button) {

	if (m_ActiveMenu) {

		RemoveChild(m_ActiveMenu);
		m_ActiveMenu = nullptr;

	}

	if (m_OverItem == nullptr) return;
	auto apps = FuturePlatform::GetAppsOfType((AppType)m_OverItem->m_Extra);
	if (apps.size() == 0) return;


	m_ActiveMenu = new IVerticalMenu();

	int cy = 5;

	for (auto app : apps) {

		cy = cy + UIHelp::StrHeight(app->GetName()) + 10;
		MenuItem* item = new MenuItem(app->GetName());
		m_ActiveMenu->AddItem(item);
		item->m_Data = app;
		item->OnSelect = [&](MenuItem* item) {

			FuturePlatform::StartApp((FPApp*)item->m_Data);

			};

	}

	m_ActiveMenu->Set(glm::vec2(m_Size.x + 5,-1), glm::vec2(250,m_Size.y));

	

	AddChild(m_ActiveMenu);


}