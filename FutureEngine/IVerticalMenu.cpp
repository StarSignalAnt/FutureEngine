#include "IVerticalMenu.h"
#include "UIHelp.h"
#include "IMainMenu.h"

void IVerticalMenu::OnMouseMove(glm::vec2 position, glm::vec2 delta) {

	int dy = 10;
	int dx = 25;
	m_OverItem = nullptr;
	for (auto item : m_Items) {

//		UIHelp::DrawText(GetRenderPosition() + glm::vec2(dx, dy), item->m_Name, glm::vec4(1, 1, 1, 1));

		if (position.y >= dy-5 && position.y <= dy-10 + 25)
		{
			m_OverItem = item;
		}

		dy = dy + 25;

	}

}


void IVerticalMenu::OnMouseDown(int button) {

	if (m_OverItem) {

		if (m_OverItem->m_Items.size() == 0) {
			if (m_OverItem->OnClick)
			{
				m_OverItem->OnClick();
			}
		}
		else {

			if (m_OverItem->m_Open == false)
			{

				if (m_OpenItem != nullptr) {

					RemoveChild(m_OpenItem->m_ActiveControl);
					delete m_OpenItem->m_ActiveControl;
					m_OpenItem->m_Open = false;

				}

				IVerticalMenu* new_menu = new IVerticalMenu;

				int height = m_OverItem->m_Items.size() * 25;

				int big_width = 0;

				for (auto item : m_OverItem->m_Items)
				{

					int string_w = UIHelp::StrWidth(item->m_Name);
					if (string_w > big_width) big_width = string_w;
					new_menu->AddItem(item);

				}



				new_menu->Set(glm::vec2(m_Size.x + 5, m_OverItem->m_DrawY), glm::vec2(big_width + 60, height + 5));

				AddChild(new_menu);

				m_OverItem->m_ActiveControl = new_menu;

				m_OverItem->m_Open = true;

				m_OpenItem = m_OverItem;
			}
			else {

				RemoveChild(m_OverItem->m_ActiveControl);
				delete m_OverItem->m_ActiveControl;
				m_OverItem->m_Open = false;
				if (m_OpenItem == m_OverItem) {
					m_OpenItem = nullptr;
				}


			}


		}

	}
}

void IVerticalMenu::Update(float delta) {


}

void IVerticalMenu::Render() {

	UIHelp::DrawRect(GetRenderPosition(), GetSize(), glm::vec4(0.15, 0.15, 0.15, 0.75));

	int dy = 10;
	int dx = 25;
	for (auto item : m_Items) {


		if (item == m_OverItem) {
			UIHelp::DrawRect(GetRenderPosition() + glm::vec2(0, dy-5), glm::vec2(GetSize().x, 20), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		}

		UIHelp::DrawText(GetRenderPosition()+glm::vec2(dx, dy), item->m_Name, glm::vec4(1, 1, 1, 1));

		item->m_DrawY = dy;
		dy = dy + 25;

	}

	RenderChildren();

}