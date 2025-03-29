#include "AppButton.h"
#include "UIHelp.h"
#include "IWindow.h"
#include "GameUI.h"
#include "UITheme.h"
#include "RenderTarget2D.h"

void AppButton::Update(float delta) {

}

void AppButton::Render() {


	auto pos = GetRenderPosition();

	pos.x = pos.x + m_Size.x / 2 - UIHelp::StrWidth(m_Text) / 2;
	pos.y = pos.y + m_Size.y / 2 - UIHelp::StrHeight(m_Text) / 2;


//	if (m_RenderBody || m_Over) {
		UIHelp::DrawOutlineRect(GetRenderPosition() + glm::vec2(-1, -1), m_Size + glm::vec2(2, 2), glm::vec4(0.5, 0.5, 0.5, 1.0));
		UIHelp::DrawImage(GetRenderPosition(), m_Size,GameUI::GetTheme()->GetButton(), m_Color);
	//}
	UIHelp::DrawText(pos+glm::vec2(15,1), m_Text, glm::vec4(1, 1, 1, 1));
	if (m_Image != nullptr) {
		pos = GetRenderPosition();
		UIHelp::DrawImage(pos + glm::vec2(4,4), glm::vec2(16, 16), m_Image, m_Color);
	}

	float ar = m_Window->GetSize().y / m_Window->GetSize().x;
	if (ar < 0.65) { ar = 0.65f; };
	ar = 1;
	float ww = m_Window->GetSize().x;
	float wh = m_Window->GetSize().y * ar;


	if (m_ShowPreview) {

		if (m_Thumbnail == nullptr)
		{


			m_Thumbnail = new RenderTarget2D(ww,wh);

		}
		else if (m_Thumbnail->GetWidth() != (int)ww || m_Thumbnail->GetHeight() !=wh)
		{

			m_Thumbnail->Free();
			m_Thumbnail = new RenderTarget2D(ww,wh);


		}


		UIHelp::RemoveScissor();
		auto rt = m_Thumbnail;
	
		rt->Bind();
		auto win_root = m_Window->GetRoot();
		auto win_pos = m_Window->GetPosition();
		auto win_size = m_Window->GetSize();
		m_Window->SetRoot(nullptr);
		m_Window->Set(glm::vec2(0, 0),glm::vec2(ww,wh));
		
		
		m_Window->Render();

		m_Window->SetRoot(win_root);
		m_Window->Set(win_pos,win_size);

		rt->Unbind();

		if (ar > 1) {
			ar = 1;
		}


		float dy = -128;
		float dh = 80 * ar;
		dy = dy + (128 - dh) / 2;
		UIHelp::RemoveScissor();
		UIHelp::DrawRect(GetRenderPosition() + glm::vec2(-8, -120), glm::vec2(144, 120), glm::vec4(0.2, 0.2, 0.2, 0.75));
		UIHelp::DrawImage(GetRenderPosition() + glm::vec2(0,dy+dh), glm::vec2(128,-dh), rt->GetTexture(), glm::vec4(1, 1, 1, 1));




	}


}

void AppButton::OnMouseEnter() {

	m_ShowPreview = true;

}

void AppButton::OnMouseLeave() {

	m_ShowPreview = false;

}