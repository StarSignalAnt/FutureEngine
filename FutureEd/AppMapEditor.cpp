#include "AppMapEditor.h"
#include <glm/glm.hpp>
#include "IWindow.h"
#include "IMainMenu.h"
#include "IImage.h"
#include "Texture2D.h"
#include "IVideoPlayer.h"
#include "IDocker.h"
#include "IControl.h"
#include "IFrameBuffer.h"
#include "GameMap.h"
#include "GameCam.h"

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

	m_SceneGraph = new IWindow("Scene", glm::vec2(20, 20), glm::vec2(200, 200), false);
	m_Content = new IWindow("Content", glm::vec2(20, 20), glm::vec2(200, 200), false);
	m_Properties = new IWindow("Properties", glm::vec2(20, 20), glm::vec2(200, 200), false);
	m_MapView = new IWindow("Map", glm::vec2(20, 20), glm::vec2(200, 200), false);

	m_Dock->DockWindow(m_Content, DockArea::DOCK_BOTTOM);
	m_Dock->DockWindow(m_SceneGraph, DockArea::DOCK_LEFT);
	m_Dock->DockWindow(m_Properties, DockArea::DOCK_RIGHT);
	m_Dock->DockWindow(m_MapView, DockArea::DOCK_CENTER);


	SetIcon(new Texture2D("apps/mapeditor/icon.png"));

	m_StartWindow = win;

	m_MapViewFB = new IFrameBuffer(glm::vec2(0, 0), glm::vec2(20, 20));

	m_MapViewFB->SetDockType(DockType::m_Fill);

	m_MapView->AddClientControl(m_MapViewFB);

	m_EditMap = new GameMap(16, 16, 2, 128, 128);

	m_EditCam = new GameCam;

	m_MapViewFB->SetOnPreRender([&]() {

		m_EditMap->RenderGrid(m_EditCam);

		});

	m_MapViewFB->SetOnMoved([&](glm::vec2 delta) {

		if (m_DragCam) {
			m_EditCam->MoveLocal(-delta);
		}
		});

	m_MapViewFB->SetOnMousePress([&](int button) {

		if (button == 1) {
			m_DragCam = true;
		}
		});

	m_MapViewFB->SetOnMouseUnPress([&](int button) {

		if (button == 1) {
			m_DragCam = false;
		}
		});

	for (int i = 0; i < 6; i++) {
		m_EditMap->SetHighlight(i, 0, true);
	}

	m_MapViewFB->SetOnMouseWheel([&](float v) {

		m_EditCam->Zoom(v * 0.1f);

		});
}