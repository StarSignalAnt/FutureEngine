#include "UIHelp.h"
#include "SmartDraw.h"
#include "GameFont.h"
#include "ShaderModule.h"

SmartDraw* m_Draw;
GameFont* m_UIFont;
SmartDraw* m_FontDraw;

void UIHelp::InitHelp() {

	m_Draw = new SmartDraw;
	m_UIFont = new GameFont("engine/ui/uifont.ttf",22);
	m_FontDraw = new SmartDraw;
	m_FontDraw->SetShaderModule(new ShaderModule("engine/shader/drawvs.glsl", "engine/shader/drawFont.glsl"));

}

void UIHelp::DrawImage(glm::vec2 position, glm::vec2 size, Texture2D* texture, glm::vec4 color)
{
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_Draw->Begin();
	m_Draw->DrawDirect(position, size, color, texture);
	
	m_Draw->End();

}

void UIHelp::DrawCharacter(glm::vec2 position, glm::vec2 size, Texture2D* texture, glm::vec4 color)
{
//	return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_FontDraw->Begin();
	m_FontDraw->DrawDirect(position, size, color, texture);
	m_FontDraw->End();


}


void UIHelp::DrawText(glm::vec2 position, std::string text, glm::vec4 color) {

	glClear(GL_DEPTH_BUFFER_BIT);
	m_UIFont->Render(position,text, color);

}