#include "StateDE1.h"
#include <iostream>
#include "SmartDraw.h"
#include "Texture2D.h"
#include "GameFont.h"
#include "UIHelp.h"

void StateDE1::InitState()
{
	// Initialize the state
	std::cout << "Initializing StateDE1" << std::endl;

	// Set up your game objects, UI, etc. here
	// For example:
	// m_Map1 = new GameMap(100, 100, 1, 32, 32);
	// m_Cam1 = new GameCam();
	// m_Light1 = new GameLight();
	m_Draw = new SmartDraw;
	// Load textures, create sprites, etc.
	m_Tex1 = new Texture2D("test/bg1.png");
	m_Font = new GameFont("engine/ui/uifont.ttf", 24);
}

void StateDE1::UpdateState(float delta)
{
	// Update game logic here

	// Handle input, update game objects, etc.
	// For example:
	// m_Cam1->Update(delta);
	// m_Map1->Update(delta);
	// m_Light1->Update(delta);
}

int a = 0;

void StateDE1::RenderState()
{
	// Render the game objects here
	// m_Map1->Render(m_Cam1);
	// m_Light1->Render();
	// m_Spr1->Render();
	a = a + 1;
	
	m_Draw->Begin();
	m_Draw->Draw(glm::vec2(200, 200), glm::vec2(200, 200), glm::vec4(1, 1, 1, 1),m_Tex1,a+45); // Replace nullptr with your texture
	m_Draw->Draw(glm::vec2(400, 400), glm::vec2(200, 200), glm::vec4(1, 1, 1, 1), m_Tex1, a+30);
	m_Draw->End();
	
	

	UIHelp::Begin();
	m_Font->Render(glm::vec2(20, 20), "This is a test of the text rendering", glm::vec4(1, 1, 1, 1), 1.0f);
	UIHelp::End();


}


void StateDE1::EndState()
{
	// Clean up resources here
	std::cout << "Ending StateDE1" << std::endl;
	// For example:
	// delete m_Map1;
	// delete m_Cam1;
	// delete m_Light1;
	// delete m_Spr1;
}

