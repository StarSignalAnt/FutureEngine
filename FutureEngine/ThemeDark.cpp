#include "ThemeDark.h"
#include "Texture2D.h"

void ThemeDark::SetupTheme() {

	m_Background = glm::vec4(0.1, 0.1, 0.1, 1);
	m_Foreground = glm::vec4(0.5, 0.5, 0.5, 1.0);
	m_Button = new Texture2D("engine/ui/buttonframe.png");
	m_ScrollButton = new Texture2D("engine/ui/softrect.png");
	m_WindowTitleBar = glm::vec4(0.05, 0.05, 0.05, 1.0f);
	m_WindowBlur = true;
	m_WindowAlpha = 0.65;

}