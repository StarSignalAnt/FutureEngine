#include "AppMapEditor.h"
#include <glm/glm.hpp>
#include "IWindow.h"
#include "IMainMenu.h"
#include "IImage.h"
#include "Texture2D.h"
#include "IVideoPlayer.h"
#include "IDocker.h"
#include "IControl.h"
AppMapEditor::AppMapEditor() {

	SetName("Map Editor");
	m_AppType = AppType::ATYPE_Development;

}

void AppMapEditor::InitApp() {

	IWindow* win = new IWindow("Map Editor", glm::vec2(100, 100), glm::vec2(700, 600));
	
	m_Window = win;
	m_Dock = new IDocker(glm::vec2(0, 0), glm::vec2(200, 200));
	m_Dock->SetDockType(DockType::m_Fill);

	win->AddClientControl(m_Dock);

	m_SceneGraph = new IWindow("Scene", glm::vec2(20, 20), glm::vec2(200, 200),false);
	m_Content = new IWindow("Content", glm::vec2(20, 20), glm::vec2(200, 200),false);
	m_Properties = new IWindow("Properties", glm::vec2(20, 20), glm::vec2(200, 200),false);
	m_MapView = new IWindow("Map", glm::vec2(20, 20), glm::vec2(200, 200),false);

	m_Dock->DockWindow(m_Content, DockArea::DOCK_BOTTOM);
	m_Dock->DockWindow(m_SceneGraph, DockArea::DOCK_LEFT);
	m_Dock->DockWindow(m_Properties, DockArea::DOCK_RIGHT);
	m_Dock->DockWindow(m_MapView, DockArea::DOCK_CENTER);




	m_StartWindow = win;

}