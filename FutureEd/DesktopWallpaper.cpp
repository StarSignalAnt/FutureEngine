#include "DesktopWallpaper.h"
#include "UIHelp.h"
#include "Texture2D.h"

DesktopWallpaper::DesktopWallpaper(glm::vec2 position, glm::vec2 size) {

	m_Position = position;
	m_Size = size;
	m_Image = new Texture2D("platform/wallpapers/platform_defaultwp.jpg");
	m_DockType = DockType::m_Fill;

}

void DesktopWallpaper::Update(float delta) {

	UpdateChildren(delta);
}

void DesktopWallpaper::Render()
{


	UIHelp::DrawImage(GetRenderPosition(), GetSize(), m_Image, glm::vec4(1, 1, 1, 1));
	RenderChildren();

}

void DesktopWallpaper::OnMouseDown(int button) {

	Click(nullptr);

}