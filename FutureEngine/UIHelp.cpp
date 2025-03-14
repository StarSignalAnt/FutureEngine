#include "UIHelp.h"
#include "SmartDraw.h"
#include "GameFont.h"
#include "ShaderModule.h"
#include "Texture2D.h"

SmartDraw* m_Draw;
GameFont* m_UIFont;
SmartDraw* m_FontDraw;
Texture2D* m_RectTex;

void UIHelp::InitHelp() {

	m_Draw = new SmartDraw;
	m_UIFont = new GameFont("engine/ui/uifont.ttf",14);
	m_FontDraw = new SmartDraw;
	m_FontDraw->SetShaderModule(new ShaderModule("engine/shader/drawvs.glsl", "engine/shader/drawFont.glsl"));
	m_RectTex = new Texture2D("engine/ui/rect.png");

}

void UIHelp::DrawImage(glm::vec2 position, glm::vec2 size, Texture2D* texture, glm::vec4 color)
{
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_Draw->Begin();
	m_Draw->DrawDirect(position, size, color, texture);
	
	m_Draw->End();

}

float UIHelp::StrWidth(std::string text) {

	return m_UIFont->StrWidth(text);

}

float UIHelp::StrHeight(std::string text) {
	return m_UIFont->StrHeight(text);
}

void UIHelp::DrawCharacter(glm::vec2 position, glm::vec2 size, Texture2D* texture, glm::vec4 color)
{
//	return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//m_FontDraw->Begin();
	m_FontDraw->DrawDirect(position, size, color, texture);
	//m_FontDraw->End();


}


void UIHelp::DrawText(glm::vec2 position, std::string text, glm::vec4 color) {

	glClear(GL_DEPTH_BUFFER_BIT);
	m_FontDraw->Begin();
	m_UIFont->Render(position,text, color,1.0f);
	m_FontDraw->End();

}

void UIHelp::DrawRect(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	m_Draw->Begin();
	m_Draw->DrawDirect(pos, size, color,m_RectTex);
	m_Draw->End();
	glEnable(GL_DEPTH_TEST);
}