#include "FSDesktop.h"
#include "FutureApp.h"
#include "SoundLib.h"
#include "GameUI.h"
#include "Texture2D.h"
#include "DesktopWallpaper.h"
#include "AppBar.h"
#include "TestApp1.h"
#include "FuturePlatform.h"

void FSDesktop::InitState() {

	auto boot = FutureApp::m_Inst->SLib->loadSound("platform/audio/boot/bootsound.wav");
	FutureApp::m_Inst->SLib->playSound(boot);

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




}

void FSDesktop::UpdateState(float delta) {

	m_UI->UpdateUI(delta);

}

void FSDesktop::RenderState() {

	m_UI->RenderUI();

}

void FSDesktop::EndState() {

}