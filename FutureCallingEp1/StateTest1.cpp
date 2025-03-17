#include "StateTest1.h"
#include "MathsOps.h"
#include "GameCam.h"
#include "GameMap.h"
#include "GameTile.h"
#include "GameLight.h"
#include "GameInput.h"
#include "FutureApp.h"
#include "GameSprite.h"
#include "GameUI.h"
#include "GameAnimation.h"
#include "RenderTarget2D.h"
#include "IImage.h"
#include "IButton.h"
#include "GameVideo.h"
#include <iostream>
#include "IWindow.h"
#include "IControlGroup.h"
#include "IVideoPlayer.h"
#include "IFrameBuffer.h"
#include "UIHelp.h"
#include "IDocker.h"

// Adding a 
// context menu option to undock windows:

void StateTest1::InitState()
{
	m_Tex1 = new Texture2D("test/bg1.png");
	m_Tex2 = new Texture2D("test/test2.png");
	m_UI = new GameUI;
	
	/*
	IWindowDockHandler::GetInstance()->Initialize(m_UI->GetRoot());

	auto gameUI = m_UI;

	// Create the window dock (normally you would size this to fill most of your application area)
	IWindowDock* mainDock = new IWindowDock(
		glm::vec2(0, 0),  // Position
		glm::vec2(FutureApp::m_Inst->GetWidth(),FutureApp::m_Inst->GetHeight())  // Size
	);

	// Add the dock to your UI
	gameUI->GetRoot()->AddChild(mainDock);

	// Register the dock with the handler
	IWindowDockHandler::GetInstance()->RegisterDock(mainDock);

	// Create some example windows
	IWindow* window1 = new IWindow("Window 1", glm::vec2(100, 100), glm::vec2(400, 300));
	IWindow* window2 = new IWindow("Window 2", glm::vec2(200, 150), glm::vec2(400, 300));
	IWindow* window3 = new IWindow("Window 3", glm::vec2(300, 200), glm::vec2(400, 300));

	// Add windows to your UI
	gameUI->GetRoot()->AddChild(window1);
	gameUI->GetRoot()->AddChild(window2);
	gameUI->GetRoot()->AddChild(window3);

	// Optionally, pre-dock some windows
	mainDock->DockWindow(window1, DOCK_LEFT);

	//mainDock->DockWindow(window2, DOCK_LEFT);  // This will create a tab with window1
	mainDock->DockWindow(window3, DOCK_CENTER);




	return;
	*/

	auto norm1 = new Texture2D("test/norm4.png");
	auto norm2 = new Texture2D("test/norm3.png");
	m_Draw = new SmartDraw;

	m_Map1 = new GameMap(16, 16, 3, 128, 128);

	m_Tile1 = new GameTile;
	m_Tile1->AddFrame(m_Tex1, norm2);

	m_Tile2 = new GameTile;
	m_Tile2->AddFrame(m_Tex2, norm1);
	m_Tile2->Set(true, false, true);

	m_Tile1->Set(false, true, true);


	m_Map1->Fill(m_Tile1, 0);


	m_Map1->FIllBlock(m_Tile2, 2, 2, 4, 1, 0);
	m_Map1->FIllBlock(m_Tile2, 2, 5, 4, 1, 0);

	m_Cam1 = new GameCam;

	m_Light1 = new GameLight;

	m_Light1->SetPosition(glm::vec3(400, 450, 356.0f));

	m_Map1->AddLight(m_Light1);

	m_RT1 = new RenderTarget2D(1024, 768);

	int a = 5;
	//m_Cam1->SetPosition(glm::vec3(300,300, 0));

	m_Spr1 = new GameSprite;

	auto spr1 = new Texture2D("test/spr1.png");

	auto anim1 = new GameAnimation("Idle");
	anim1->AddFrame(spr1, nullptr);

	m_Spr1->AddAnimation(anim1);
	m_Spr1->PlayAnimation("Idle");

	m_Map1->AddSprite(m_Spr1);

	m_Spr1->SetPosition(glm::vec3(200, 350, 1));

	

	IImage* img1 = new IImage(glm::vec2(0,0), glm::vec2(FutureApp::m_Inst->GetWidth(),FutureApp::m_Inst->GetHeight()));
	img1->SetImage(m_Tex1);
	m_UI->GetRoot()->AddChild(img1);


	auto dock = new IDocker(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()));
	m_UI->GetRoot()->AddChild(dock);


	IButton* but1 = new IButton("Testing",glm::vec2(450, 200), glm::vec2(168, 80));
	//m_UI->GetRoot()->AddChild(but1);

	but1->SetOnClick([]() {
		//std::cout << "Button clicked! (Lambda function)" << std::endl;
		});
	but1->SetOnDoubleClick([]() {
		std::cout << "Double Click!" << std::endl;
		});

	auto win1 = new IWindow("Test Window", glm::vec2(100, 100), glm::vec2(300, 300));
	auto win2 = new IWindow("Other Window", glm::vec2(250, 200), glm::vec2(300, 300));
	m_UI->GetRoot()->AddChild(win1);
	m_UI->GetRoot()->AddChild(win2);
	auto wb1 = new IButton("Load Game", glm::vec2(20, 60), glm::vec2(130, 30));
	auto wb2 = new IButton("Save Game", glm::vec2(600, 600), glm::vec2(130, 30));


	win1->AddClientControl(wb1);
	win1->AddClientControl(wb2);


	auto vid = new IVideoPlayer("test/fcintro.mp4", glm::vec2(20, 20), glm::vec2(512, 512));
	
	//win1->GetClientArea()->SetCullChildren(false);

	auto fb = new IFrameBuffer(glm::vec2(20, 20), glm::vec2(512, 512));

	fb->SetOnPreRender([&]() {

		m_Draw->Begin();
		m_Draw->Draw(glm::vec2(256, 256), glm::vec2(512,512), glm::vec4(1, 1, 1, 1), m_Tex1, 0, 1.0f);
		m_Draw->End();

		});

	//m_UI->GetRoot()->AddChild(vid);
//	win1->AddClientControl(fb);

	vid->Play();


//	m_Vid1 = new GameVideo("test/fcintro.mp4");
//	m_Vid1->Play();

}


bool click = false;

void StateTest1::UpdateState(float delta)
{

	/*
	if (GameInput::Buttons[MOUSE_BUTTON_LEFT] && click == false)
	{
		if (m_Playing) {
			m_Vid1->Pause();
			m_Playing = false;
		}
		else {
			m_Vid1->Resume();
			m_Playing = true;
		}
		click = true;
	}
	else if (GameInput::Buttons[MOUSE_BUTTON_LEFT] == false) {
		click = false;
	}
	*/

	m_Ang += 10.0f * delta;

	//m_Vid1->Update();

	m_UI->UpdateUI(delta);

	
	return;
	if (GameInput::Buttons[MOUSE_BUTTON_RIGHT]) {
		m_Cam1->MoveLocal(glm::vec2(GameInput::MouseDelta.x, GameInput::MouseDelta.y));
		//m_Cam1->SetPosition(glm::vec2(GameInput::
	}
	if (GameInput::Buttons[MOUSE_BUTTON_MIDDLE])
	{
		m_Cam1->Turn(glm::vec3(0, (GameInput::MouseDelta.x), 0 ));
	}

	m_Cam1->Zoom(GameInput::MouseDelta.z * 0.05f);
	m_Spr1->Turn(glm::vec3(0, 10*delta, 0));
	//m_Cam1->Turn(glm::vec3(0, 10.0f*delta, 0));
//	m_Cam1->Move(glm::vec3(30.0f * delta,0,0));
}


int ax = 0;
int ay = 0;

void StateTest1::RenderState()
{

	//auto frame = m_Vid1->GetFrame();
//	if (frame != nullptr) {
//		m_Draw->Begin();
//		m_Draw->DrawDirect(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()), glm::vec4(1, 1, 1, 1), frame);
//		m_Draw->End();
	//}


	m_UI->RenderUI();
	if (m_UI->GetDraggingWindow() != nullptr) {

		UIHelp::DrawText(glm::vec2(5, 5), "Dragging window:" + m_UI->GetDraggingWindow()->GetText(), glm::vec4(0, 1, 0, 1));
		if (m_UI->GetBeneathWindow() != nullptr) {
			UIHelp::DrawText(glm::vec2(5, 35), "Beneath:" + m_UI->GetBeneathWindow()->GetText(), glm::vec4(0, 1, 0, 1));
		}

	}
	else {
		UIHelp::DrawText(glm::vec2(5, 5), "Not dragging a window.", glm::vec4(1, 0, 0, 1));
	}

	return;
	ax = ax + 1;
	if (ax > 800) {
		ax = 0;
	//	ay = ay + 1;
	}
	
	//m_RT1->Bind();
	//m_RT1->Clear();
	m_Map1->RenderMap(m_Cam1);
	//m_RT1->Unbind();



	return;
	m_Draw->Begin();
	m_Draw->DrawDirect(glm::vec2(0,FutureApp::m_Inst->GetHeight()), glm::vec2(FutureApp::m_Inst->GetWidth(),-FutureApp::m_Inst->GetHeight()), glm::vec4(1, 1, 1, 1), m_RT1->GetTexture());
	m_Draw->End();



	return;
	m_Draw->Begin();
	ax = 0;
	ay = 200;

	for (int i = 0; i < 100; i++) {
	//	ax = MathsOps::RndFloat(0, 800);
	//
	// 	ay = MathsOps::RndFloat(0, 600);
		m_Draw->Draw(glm::vec2(ax, ay), glm::vec2(220, 220), glm::abs(glm::vec4(1, 1, 1, 1)), m_Tex2, m_Ang * 2);

		ax = ax + 128;
		m_Draw->Draw(glm::vec2(ax, ay), glm::vec2(220, 220), glm::abs(glm::vec4(1, 1, 1, 1)), m_Tex1, m_Ang);
		ax = ax + 128;
	

	}


	m_Draw->End();

}

void StateTest1::EndState()
{
}
