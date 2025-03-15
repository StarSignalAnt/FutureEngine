#include "GameUI.h"
#include "IControl.h"
#include "IControlGroup.h"
#include "GameInput.h"
#include "FutureApp.h"
#include "window-dock-handler.h"
#include "IWindow.h"

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
				
				int ctime = clock();
				//prev_Click = clock();
				if (ctime < (prev_Click + 350)) {
					m_ControlPressed->OnMouseDoubleClick();
				}
				prev_Click = ctime;
				
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

	if (m_ControlPressed != nullptr) {
		m_ControlPressed->OnMouseMove(mouse_pos - m_ControlOver->GetRenderPosition(), GameInput::MouseDelta);

	}
	else if (m_ControlOver != nullptr) {

		m_ControlOver->OnMouseMove(mouse_pos - m_ControlOver->GetRenderPosition() , GameInput::MouseDelta);

	}

	m_RootControl->Update(delta);
	


	if (m_WindowDockingEnabled && m_ControlPressed != nullptr) {
		// Check if dragging a window
		IWindow* window = dynamic_cast<IWindow*>(m_ControlPressed);
		if (window) {
			// If this is a window being dragged
			if (m_DraggingWindow == nullptr) {
				m_DraggingWindow = window;
				m_LastWindowPosition = window->GetPosition();
			}

			// Handle window dragging for potential docking
			auto dockHandler = IWindowDockHandler::GetInstance();
			dockHandler->HandleWindowDrag(window, GameInput::MousePosition);
		}
	}
	else if (m_DraggingWindow != nullptr && !GameInput::Buttons[MOUSE_BUTTON_LEFT]) {
		// Mouse released after dragging a window - attempt docking
		auto dockHandler = IWindowDockHandler::GetInstance();
		dockHandler->HandleWindowDrop(m_DraggingWindow, GameInput::MousePosition);
		m_DraggingWindow = nullptr;
	}

	// Check for tab interaction in docked windows
	if (GameInput::Buttons[MOUSE_BUTTON_LEFT] && m_ControlOver != nullptr) {
		DockPanel* panel = dynamic_cast<DockPanel*>(m_ControlOver);
		if (panel) {
			int tabIndex;
			if (panel->InTabBounds(GameInput::MousePosition, tabIndex)) {
				panel->SetActiveWindow(tabIndex);
			}
		}
	}

}

void GameUI::RenderUI()
{
	m_RootControl->PreRender();

	m_RootControl->Render();
}
