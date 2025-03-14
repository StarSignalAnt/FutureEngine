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



void StateTest1::InitState()
{

	m_Tex1 = new Texture2D("test/test1.png");
	m_Tex2 = new Texture2D("test/test2.png");
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

	m_UI = new GameUI;

	IImage* img1 = new IImage(glm::vec2(100, 100), glm::vec2(300, 300));
	img1->SetImage(m_Tex1);
	m_UI->GetRoot()->AddChild(img1);

	IButton* but1 = new IButton("Testing",glm::vec2(450, 200), glm::vec2(168, 80));
	m_UI->GetRoot()->AddChild(but1);

	but1->SetOnClick([]() {
		//std::cout << "Button clicked! (Lambda function)" << std::endl;
		});
	but1->SetOnDoubleClick([]() {
		std::cout << "Double Click!" << std::endl;
		});

	auto win1 = new IWindow("Test Window", glm::vec2(100, 100), glm::vec2(300, 300));

	m_UI->GetRoot()->AddChild(win1);

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
