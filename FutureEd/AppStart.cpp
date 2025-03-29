#include "AppStart.h"
#include "Texture2D.h"
#include "UIHelp.h"
#include "AppMenu.h"
#include "IMainMenu.h"
#include "FPApp.h"

AppStart::AppStart(glm::vec2 position, glm::vec2 size) {

	m_AppStartImage = new Texture2D("platform/ui/FPIcon1.png");
	m_Color = glm::vec4(0.85, 0.85, 0.85, 0.7);
	m_Position = position;

	m_Size = size;
	SetIgnoreScissor(true);

}

void AppStart::Update(float deltta) {

}

void AppStart::Render() {

	UIHelp::DrawImage(GetRenderPosition(), GetSize(), m_AppStartImage, m_Color);

	RenderChildren();

}



void AppStart::OnMouseEnter() {

	m_Color = glm::vec4(1, 1, 1, 1);

}

void AppStart::OnMouseLeave() {

	m_Color = glm::vec4(0.85, 0.85, 0.85, 0.7);

}

void AppStart::OnMouseDown(int button) {

	if (m_Menu == nullptr) {

		m_Menu = new AppMenu(glm::vec2(-10, -350), glm::vec2(200, 340));
		
		auto term = new MenuItem("Terminal");
		auto utility = new MenuItem("Utility");
		auto system = new MenuItem("System");
		auto devel = new MenuItem("Development");
		auto game = new MenuItem("Game");
		auto internet = new MenuItem("Internet");
		auto media = new MenuItem("Media");
		auto misc = new MenuItem("Misc");
		auto ai = new MenuItem("AI");

		m_Menu->AddItem(term);
		m_Menu->AddItem(utility);
		m_Menu->AddItem(system);
		m_Menu->AddItem(ai);
		m_Menu->AddItem(devel);
		m_Menu->AddItem(game);
		m_Menu->AddItem(internet);
		m_Menu->AddItem(media);

		m_Menu->AddItem(misc);

		term->m_Extra = AppType::ATYPE_Terminal;
		utility->m_Extra = AppType::ATYPE_Utility;
		system->m_Extra = AppType::ATYPE_System;
		devel->m_Extra = AppType::ATYPE_Development;
		game->m_Extra = AppType::ATYPE_Game;
		internet->m_Extra = AppType::ATYPE_Internet;
		media->m_Extra = AppType::ATYPE_Media;
		misc->m_Extra = AppType::ATYPE_Misc;
		ai->m_Extra = AppType::ATYPE_AI;



		AddChild(m_Menu);


	}
	else {

		RemoveChild(m_Menu);
		m_Menu = nullptr;

	}

}