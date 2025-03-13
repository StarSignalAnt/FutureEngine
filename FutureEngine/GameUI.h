#pragma once

class IControl;

class GameUI
{
public:

	GameUI();
	void SetRoot(IControl* control) { m_RootControl = control; }
	IControl* GetRoot() { return m_RootControl; };
	void UpdateUI(float delta);
	void RenderUI();


private:

	IControl* m_RootControl;

};

