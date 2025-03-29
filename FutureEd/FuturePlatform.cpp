#include "FuturePlatform.h"
#include "FSLogin.h"
#include "FPApp.h"
#include "DesktopWallpaper.h"
#include <Windows.h>
#include <iostream>
#include "AppBar.h"
#include "GameUI.h"
#include "GpuTalk.h"

AppBar* FuturePlatform::m_AppBar = nullptr;
std::vector<FPApp*> FuturePlatform::m_RunningApps;
std::vector<FPApp*> FuturePlatform::m_Apps;
DesktopWallpaper* FuturePlatform::m_Wallpaper;
GpuTalk* FuturePlatform::m_Talk = nullptr;


FuturePlatform::FuturePlatform() {

	SetApp(1024, 768, "Future Platform (open-source) - Star Signal Games");
	PushState(new FSLogin);
	Run();
	

}

void FuturePlatform::BeginTalk() {

 m_Talk = new GpuTalk("models/mistral-7b-instruct-v0.1.Q8_0.gguf");

}

std::string FuturePlatform::Ask(std::string text) {
	return m_Talk->Ask(text);

}

std::string FuturePlatform::Ask(std::string directive, std::string text) {

	return m_Talk->AskWithContext(directive, text);

}




void FuturePlatform::StartApp(FPApp* application) {

	m_RunningApps.push_back(application);
	application->Start();
	auto win = application->GetStartWindow();
	//m_Wallpaper->AddChild((IControl*)win);
	GameUI::m_Inst->GetWindowSurface()->AddChild((IControl*)win);
	m_AppBar->RegisterWindow(win,application);



}

void FuturePlatform::RegisterAppBar(AppBar* bar) {

	m_AppBar = bar;

}

void FuturePlatform::RegisterWallpaper(DesktopWallpaper* wallpaper) {

	m_Wallpaper = wallpaper;

}

void FuturePlatform::RegisterApp(FPApp* app) {

	m_Apps.push_back(app);

}

void FuturePlatform::RegisterApp(std::string name) {

	name = "apps/" + name + "/" + name + ".dll";

	HMODULE hModule = LoadLibraryA(name.c_str());
	if (!hModule) {
		std::cout << "Failed to load DLL. Error: " << GetLastError() << std::endl;
		return;
	}
	std::cout << "Loaded app library:" + name << std::endl;

	typedef void* (*GenericFunction)();

	GenericFunction func = (GenericFunction)GetProcAddress(hModule, "GetFutureApp");

	FPApp* app = (FPApp*)func();

	m_Apps.push_back(app);

}

std::vector<FPApp*> FuturePlatform::GetAppsOfType(AppType type) {

	std::vector<FPApp*> apps;

	for (auto app : m_Apps) {

		if (app->GetType() == type) {
			apps.push_back(app);
		}

	}
	
	return apps;

}