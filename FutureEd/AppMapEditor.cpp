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
#include "MapViewFB.h"
#include "IToolBar.h"
#include "ContentBrowser.h"
#include "TileManager.h"
#include "GameUI.h"
#include "MapViewFB.h"

AppMapEditor::AppMapEditor() {

	SetName("Map Editor");
	m_AppType = AppType::ATYPE_Development;

}

void AppMapEditor::InitApp() {

	IWindow* win = new IWindow("Map Editor", glm::vec2(100, 100), glm::vec2(700, 600),false,true);

	auto toolbar = win->GetToolBar();

	toolbar->AddButton(new Texture2D("apps/mapeditor/translate.png"));
	toolbar->AddButton(new Texture2D("apps/mapeditor/rotate.png"));
	toolbar->AddButton(new Texture2D("apps/mapeditor/scale.png"));
	auto b1 = toolbar->AddButton("Rect");
	auto b2 = toolbar->AddButton("Fill");
	
	b1->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_RectFill;
		});
	b2->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_Fill;
		});



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


	m_ContentBrowser = new ContentBrowser;

	m_ContentBrowser->Browse("c:\\content\\");

	m_Content->AddClientControl(m_ContentBrowser);

	SetIcon(new Texture2D("apps/mapeditor/icon.png"));

	m_StartWindow = win;

	m_MapViewFB = new MapViewFB;

	m_MapViewFB->SetDockType(DockType::m_Fill);

	m_MapView->AddClientControl(m_MapViewFB);

	m_EditMap = new GameMap(16, 16, 2, 128, 128);

	m_EditCam = new GameCam;

	m_MapViewFB->SetMap(m_EditMap);
	m_MapViewFB->SetCam(m_EditCam);


	//
	IMainMenu* edit_menu = new IMainMenu;
	edit_menu->SetAppTitle("Map Editor");
	auto m_File = new MenuItem("File");
	auto m_tools = new MenuItem("Tools");

	auto tile_manager = new MenuItem("Tile Manager");
	m_tools->AddItem(tile_manager);
	edit_menu->AddItem(m_File);
	edit_menu->AddItem(m_tools);

	win->SetMenu(edit_menu);


	tile_manager->OnClick = [&]() {

		auto tm = new TileManager;
		GameUI::m_Inst->GetWindowSurface()->AddChild(tm);

		};


	/*
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
		*/
}