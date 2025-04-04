#include "FutureTalk.h"
#include <glm/glm.hpp>
#include "FuturePlatform.h"
#include "IWindow.h"
#include <iostream>
#include "IMainMenu.h"
#include "IImage.h"
#include "Texture2D.h"
#include "IVideoPlayer.h"
#include "FPApps.h"
#include "ITextArea.h"
#include "ITextEdit.h"
#include "IControlGroup.h"
FutureTalk::FutureTalk() {

	SetName("Future Talk");
	m_AppType = AppType::ATYPE_AI;
}

void FutureTalk::InitApp() {

	int b = 5;
	IWindow* win = new IWindow("Future Talk", glm::vec2(200, 200), glm::vec2(610, 300));
	auto quest = new ITextEdit(glm::vec2(5, 5), glm::vec2(600, 30));

	auto text = new ITextArea(glm::vec2(5, 40), glm::vec2(600, 400));
	win->AddClientControl(quest);
	win->AddClientControl(text);

	m_StartWindow = win;
	SetIcon(new Texture2D("apps/mapeditor/icon.png"));
	m_Question = quest;
	m_Answer = text;

	//auto res = FuturePlatform::Ask("What is the purpose of a gpu");
//	std::cout << res << std::endl;
	quest->SetOnEnter([&](void* data) {

	

		});

	//text->AddText(res);
	win->GetClientArea()->SetCullChildren(true);



}