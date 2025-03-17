#pragma once
#include <glm/glm.hpp>
class IControl;
class IWindow;
class IDocker;

class GameUI
{
public:

	GameUI();
	void SetRoot(IControl* control) { m_RootControl = control; }
	IControl* GetRoot() { return m_RootControl; };
	void UpdateUI(float delta);
	void RenderUI();
	IWindow* GetDraggingWindow() { return m_DraggingWindow; }
	IControl* GetBeneathWindow();
private:
	bool m_WindowDockingEnabled = true;
	glm::vec2 m_LastWindowPosition;
	IWindow* m_DraggingWindow = nullptr;
	IControl* m_FirstClick = nullptr;
	IControl* m_RootControl;
	IControl* m_ControlOver = nullptr;
	IControl* m_ControlPressed = nullptr;
	IControl* m_ControlActive = nullptr;
	int prev_Click = 0;
	IDocker* m_DraggingDock = nullptr;
//	IWindow* m_DraggingWindow = nullptr;
	IWindow* m_DockingWindow = nullptr;
};

