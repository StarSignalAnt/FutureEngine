#include "GameUI.h"
#include "IControl.h"
#include "IControlGroup.h"
#include "GameInput.h"
#include "FutureApp.h"
#include "IDocker.h"
#include "IWindow.h"



GameUI* GameUI::m_Inst = nullptr;



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
    m_Inst = this;
    m_RootControl = new IControlGroup;
	m_RootControl->Set(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(),FutureApp::m_Inst->GetHeight()));
    
}void GameUI::UpdateUI(float delta)
{
    // Process any pending undock operations first


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
                        prev_Click = 0;
                    }
                }
                else {
                    m_ControlOver = control;
                    control->OnMouseEnter();
                    prev_Click = 0;
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

                // Check if this is a window and being dragged by title area
                IWindow* window = dynamic_cast<IWindow*>(m_ControlPressed);
                if (window != nullptr && window->GetCurrentArea() == AREA_TITLE) {
                    m_DraggingWindow = window;
                }

                int ctime = clock();
                //prev_Click = clock();
                if (ctime < (prev_Click + 350) && m_FirstClick == m_ControlPressed) {
                    m_ControlPressed->OnMouseDoubleClick();
                    m_FirstClick = nullptr;
                }
                else {
                    m_FirstClick = nullptr;
                }
                prev_Click = ctime;
                m_FirstClick = m_ControlPressed;

            }
            else {

            }

        }
    }
    else {
        if (m_ControlPressed != nullptr) {
            m_ControlPressed->OnMouseUp(0);
            m_ControlPressed = nullptr;
            m_DraggingWindow = nullptr; // Clear dragging window when mouse is released
        }
    }

    if (m_ControlPressed != nullptr) {
        m_ControlPressed->OnMouseMove(mouse_pos - m_ControlOver->GetRenderPosition(), GameInput::MouseDelta);

    }
    else if (m_ControlOver != nullptr) {

        m_ControlOver->OnMouseMove(mouse_pos - m_ControlOver->GetRenderPosition(), GameInput::MouseDelta);

    }

    m_RootControl->Update(delta);

    if (GetDraggingWindow() != nullptr) {

        auto beneath = GetBeneathWindow();
        if (beneath != nullptr) {

            IDocker* dock = dynamic_cast<IDocker*>(beneath);
            if (dock != nullptr) {
                dock->WindowOver(GetDraggingWindow(), mouse_pos);
                m_DraggingDock = dock;
                m_DockingWindow = GetDraggingWindow();
                
            }
            if (beneath->IsWindow()) {
                //exit(1);
                m_TabWindow = beneath->GetWindow();
                m_TabTarget = GetDraggingWindow();
                m_DraggingDock = nullptr;
                m_DockingWindow = nullptr;
            }
            else {
                m_TabWindow = nullptr;
                m_TabTarget = nullptr;
            }
        }

    }
    else {

        if (m_TabWindow != nullptr) {
            //exit(1);
            m_TabWindow->DockWindow(m_TabTarget);
            m_TabWindow = nullptr;
        }
        if (m_DraggingDock != nullptr) {
         

            m_DraggingDock->DockWindow(m_DockingWindow, mouse_pos);
            m_DraggingDock = nullptr;
            //auto area = m_DraggingDock->GetDockAreaAtPosition(mouse_pos);

            //if (area != AREA_NONE) {
            //    m_DraggingDock->DockWindow(m_DockingWindow, area);
                //m_DraggingDock->WindowCancel();

            //}

        }

    }



}
void GameUI::RenderUI()
{
	m_RootControl->PreRender();

	m_RootControl->Render();
}


IControl* GameUI::GetBeneathWindow()
{
    // If no window is being dragged, return nullptr
    if (m_DraggingWindow == nullptr) {
        return nullptr;
    }

    // Get current mouse position
    auto mouse_pos = GameInput::MousePosition;

    // Create a list of all controls to check against
    std::vector<IControl*> list;
    list = AddControls(list, m_RootControl);

    // Reverse the list to check front-to-back (same order as in UpdateUI)
    std::reverse(list.begin(), list.end());

    // To find control beneath dragged window, we need to skip the dragged window
    // and any of its children in the hit test
    bool skipWindow = false;

    for (auto control : list) {
        // Skip the dragged window and its children
        if (control == m_DraggingWindow) {
            skipWindow = true;
            continue;
        }

        // For child controls of the dragged window, continue skipping
        if (skipWindow) {
            IControl* parent = control->GetRoot();
            bool isChild = false;

            // Check if control is a child of the dragged window
            while (parent != nullptr) {
                if (parent == m_DraggingWindow) {
                    isChild = true;
                    break;
                }
                parent = parent->GetRoot();
            }

            if (isChild) {
                continue;
            }
        }

        // Check if control is under mouse position
        if (control->InBounds(mouse_pos)) {
            return control;
        }
    }

    // No control found beneath the window
    return nullptr;
}

void GameUI::ResetMouse() {

    m_ControlOver = nullptr;
    m_ControlPressed = nullptr;
    m_TabWindow = nullptr;
    m_TabTarget = nullptr;

}