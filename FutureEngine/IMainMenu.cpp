#include "IMainMenu.h"
#include "FutureApp.h"
#include "UIHelp.h"
#include "IVerticalMenu.h"

IMainMenu::IMainMenu() {

	m_Size = glm::vec2(FutureApp::m_Inst->GetWidth(), 25);

}

void IMainMenu::Update(float delta) {

}

void IMainMenu::OnMouseMove(glm::vec2 position, glm::vec2 delta) {

	int dx = 15;

	m_OverItem = nullptr;
	for (auto item : m_Items) {

		if (position.x >= dx-15 && position.x <= dx-15 + UIHelp::StrWidth(item->m_Name) + 35)
		{
			m_OverItem = item;
		}

		dx = dx + UIHelp::StrWidth(item->m_Name) + 35;

	}

}

void IMainMenu::OnMouseDown(int button) {

	if (m_OverItem) {

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



			new_menu->Set(glm::vec2(m_OverItem->m_DrawX+5, 30), glm::vec2(big_width + 60, height + 5));

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

void IMainMenu::Render() {

	UIHelp::DrawRect(m_Position, m_Size, glm::vec4(0.15, 0.15, 0.15, 0.85f));

	int dx = 15;
	glm::vec2 pos = GetRenderPosition();

	for (auto item : m_Items) {

		if (item == m_OverItem) {

			UIHelp::DrawRect(pos + glm::vec2(dx-15, 2), glm::vec2(UIHelp::StrWidth(item->m_Name) + 35, 20), glm::vec4(0.4f, 0.4f, 0.4f, 0.8f));

		}

		item->m_DrawX = dx - 15;
	

		UIHelp::DrawText(pos + glm::vec2(dx, 13 - UIHelp::StrHeight(item->m_Name)/2), item->m_Name, glm::vec4(1, 1, 1, 1));
		dx = dx + UIHelp::StrWidth(item->m_Name) + 35;

	}

	RenderChildren();

}