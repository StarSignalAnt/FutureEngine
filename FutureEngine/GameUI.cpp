#include "GameUI.h"
#include "IControl.h"
#include "IControlGroup.h"
#include "GameInput.h"
#include "FutureApp.h"

std::vector<IControl*> AddControls(std::vector<IControl*> list, IControl* control) {

	list.push_back(control);
	for (auto sub_control : control->GetChildren())
	{
		list = AddControls(list, sub_control);
	}

	return list;
}

GameUI::GameUI()
{
	m_RootControl = new IControlGroup;
	m_RootControl->Set(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(),FutureApp::m_Inst->GetHeight()));
	

}

void GameUI::UpdateUI(float delta)
{

	std::vector<IControl*> list;

	list = AddControls(list, m_RootControl);

	std::reverse(list.begin(), list.end()); // Reverse the vector in-place

	auto mouse_pos = GameInput::MousePosition;


	if (m_ControlPressed == nullptr) {
		for (auto control : list) {

			if (control->InBounds(mouse_pos))
			{
				if (m_ControlOver) {
					if (m_ControlOver == control) {

					}
					else {
						m_ControlOver->OnMouseLeave();
						m_ControlOver = control;
						control->OnMouseEnter();
					}
				}
				else {
					m_ControlOver = control;
					control->OnMouseEnter();
				}
				break;
			}
		}

	}
	if (GameInput::Buttons[MOUSE_BUTTON_LEFT])
	{

		if (m_ControlOver != nullptr) {
			if (m_ControlPressed == nullptr) {
				m_ControlPressed = m_ControlOver;
				m_ControlPressed->OnMouseDown(0);
			}
			else {

			}

		}
	}
	else {
		if (m_ControlPressed != nullptr) {
			m_ControlPressed->OnMouseUp(0);
			m_ControlPressed = nullptr;
		}
	}

	m_RootControl->Update(delta);

}

void GameUI::RenderUI()
{
	m_RootControl->Render();
}
