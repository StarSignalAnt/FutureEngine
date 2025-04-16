#include "FSDesktop.h"
#include "FutureApp.h"
#include "SoundLib.h"
#include "GameUI.h"
#include "Texture2D.h"
#include "DesktopWallpaper.h"
#include "AppBar.h"
#include "TestApp1.h"
#include "FuturePlatform.h"
#include "IMainMenu.h"
#include "MessageBox.h"
#include "AppMapEditor.h"
#include "FutureTalk.h"

void FSDesktop::InitState() {

//	auto boot = FutureApp::m_Inst->SLib->loadSound("platform/audio/boot/bootsound.wav");
//	FutureApp::m_Inst->SLib->playSound(boot);

	m_UI = new GameUI;

	auto wallpaper = new DesktopWallpaper(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight() - 50));

	m_UI->GetRoot()->AddChild(wallpaper);

	auto app_bar = new AppBar(glm::vec2(0, FutureApp::m_Inst->GetHeight() - 30), glm::vec2(FutureApp::m_Inst->GetWidth(), 30));

	m_UI->GetRoot()->AddChild(app_bar);

	TestApp1* app = new TestApp1;

	FuturePlatform::RegisterAppBar(app_bar);
	FuturePlatform::RegisterWallpaper(wallpaper);
	//FuturePlatform::StartApp(app);


	FuturePlatform::RegisterApp(app);
	FuturePlatform::RegisterApp(new AppMapEditor);




	SetupDesktopMenu();

	wallpaper->SetOnClick([&](void * data) {

		GameUI::m_Inst->SetMainMenu(nullptr);

		});

	//
	m_UI->SetWindowSurface(wallpaper);


}


void FSDesktop::SetupDesktopMenu() {

	IMainMenu* main_menu = new IMainMenu;
	main_menu->SetAppTitle("Future Platform");

	auto os = new MenuItem("Future Platform");

	auto about = new MenuItem("About");
	auto exit = new MenuItem("Exit");

	os->AddItem(about);
	os->AddItem(exit);

	main_menu->AddItem(os);

	GameUI::m_Inst->SetMainMenu(main_menu);
	GameUI::m_Inst->SetDefualtMenu(main_menu);

	about->OnClick = [&]() {

		new MessageBox("Future Platform - Pre-Alpha W.I.P - Future Platform is an open-source platform for makings and apps and games that use the Future Engine for input/output.","Future Platform");

		};


}

void FSDesktop::UpdateState(float delta) {

	m_UI->UpdateUI(delta);

}

void FSDesktop::RenderState() {

	m_UI->RenderUI();

}

void FSDesktop::EndState() {

}