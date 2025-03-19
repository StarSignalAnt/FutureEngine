#include "UIHelp.h"
#include "SmartDraw.h"
#include "GameFont.h"
#include "ShaderModule.h"
#include "Texture2D.h"
#include "FutureApp.h"
#include "DrawInfo.h"

SmartDraw* m_Draw;
GameFont* m_UIFont;
SmartDraw* m_FontDraw;
SmartDraw* m_BlurDraw;
Texture2D* m_RectTex;
Texture2D* m_ColorBG;


void UIHelp::InitHelp() {

	m_Draw = new SmartDraw;
	m_UIFont = new GameFont("engine/ui/uifont.ttf",14);
	m_FontDraw = new SmartDraw;
	m_BlurDraw = new SmartDraw;
	m_BlurDraw->SetShaderModule(new ShaderModule("engine/shader/drawvs.glsl", "engine/shader/drawBlurFS.glsl"));
	m_FontDraw->SetShaderModule(new ShaderModule("engine/shader/drawvs.glsl", "engine/shader/drawFont.glsl"));
	m_RectTex = new Texture2D("engine/ui/rect.png");
	m_ColorBG = new Texture2D("engine/ui/colorBG6.jpg");

}

void UIHelp::DrawImageBlur(glm::vec2 position, glm::vec2 size, Texture2D* texture, glm::vec4 color,float blur)
{
	glEnable(GL_BLEND);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_BlurDraw->Begin();

	m_BlurDraw->GetShaderModule()->Bind();
	m_BlurDraw->GetShaderModule()->SetFloat("blurAmount", blur*500);
	m_BlurDraw->DrawDirect(position, size, color, texture);

	m_BlurDraw->End();

}

void UIHelp::DrawImage(glm::vec2 position, glm::vec2 size, Texture2D* texture, glm::vec4 color)
{
	glEnable(GL_BLEND);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_Draw->Begin();
	m_Draw->DrawDirect(position, size, color, texture);
	
	m_Draw->End();

}

float UIHelp::StrWidth(std::string text,float scale) {

	return m_UIFont->StrWidth(text,scale);

}

float UIHelp::StrHeight(std::string text,float scale) {
	return m_UIFont->StrHeight(text,scale);
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


void UIHelp::DrawText(glm::vec2 position, std::string text, glm::vec4 color,float scale) {

	glClear(GL_DEPTH_BUFFER_BIT);
	m_FontDraw->Begin();
	m_UIFont->Render(position,text, color,scale);
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

void UIHelp::DrawOutlineRect(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{

	DrawRect(pos, glm::vec2(size.x,1), color);
	DrawRect(pos, glm::vec2(1, size.y), color);
	DrawRect(pos + glm::vec2(0, size.y), glm::vec2(size.x, 1), color);
	DrawRect(pos + glm::vec2(size.x, 0), glm::vec2(1, size.y), color);
	return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	m_Draw->Begin();
	m_Draw->DrawDirect(pos, size, color, m_RectTex);
	m_Draw->End();
	glEnable(GL_DEPTH_TEST);
}

void UIHelp::DrawImageWithBG(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
{

	float yHigh = size.y / (float)FutureApp::m_Inst->GetHeight();
	float yPos = pos.y / (float)FutureApp::m_Inst->GetHeight();
	float xPos = pos.x / (float)FutureApp::m_Inst->GetWidth();
	float xHigh = xPos+size.x / (float)FutureApp::m_Inst->GetWidth();

	glEnable(GL_BLEND);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_BlurDraw->Begin();

	m_BlurDraw->GetShaderModule()->Bind();
	m_BlurDraw->GetShaderModule()->SetFloat("blurAmount", 0.4 * 500);
	auto info = m_BlurDraw->DrawDirect(pos, size, color,m_ColorBG);

	info->SetTexCoord(0, xPos, yPos);
	info->SetTexCoord(1, xHigh, yPos);
	info->SetTexCoord(2, xHigh, yHigh);
	info->SetTexCoord(3, xPos, yHigh);
	m_BlurDraw->End();



	return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	m_Draw->Begin();
//	auto info = m_Draw->DrawDirect(pos, size, color, m_ColorBG);
	info->SetTexCoord(0,xPos, yPos);
	info->SetTexCoord(1, xHigh, yPos);
	info->SetTexCoord(2, xHigh, yHigh);
	info->SetTexCoord(3, xPos, yHigh);
	m_Draw->End();


	glEnable(GL_DEPTH_TEST);

}