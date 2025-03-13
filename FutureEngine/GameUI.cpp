#include "GameUI.h"
#include "IControl.h"
#include "IControlGroup.h"


GameUI::GameUI()
{
	m_RootControl = new IControlGroup;
}

void GameUI::UpdateUI(float delta)
{
	m_RootControl->Update(delta);
}

void GameUI::RenderUI()
{
	m_RootControl->Render();
}
