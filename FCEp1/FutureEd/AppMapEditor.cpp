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
#include "GameLight.h"
#include "GameObj.h"
#include "IControlGroup.h"
#include "IPropertyEditor.h"
#include "CreateMapWindow.h"
#include "FileRequester.h"

AppMapEditor* AppMapEditor::m_Inst = nullptr;


AppMapEditor::AppMapEditor() {

	SetName("Map Editor");
	m_AppType = AppType::ATYPE_Development;
	m_Inst = this;
}

void AppMapEditor::Select(GameObj* obj) {

	m_Inst->SetObject(obj);

}

void AppMapEditor::InitApp() {

	IWindow* win = new IWindow("Map Editor", glm::vec2(100, 100), glm::vec2(700, 600),false,true);

	auto toolbar = win->GetToolBar();

	toolbar->AddButton(new Texture2D("apps/mapeditor/translate.png"));
	toolbar->AddButton(new Texture2D("apps/mapeditor/rotate.png"));
	toolbar->AddButton(new Texture2D("apps/mapeditor/scale.png"));
	toolbar->Seperator(30);
	auto b_paste = toolbar->AddButton(new Texture2D("apps/mapeditor/b_paste.png"));
	auto b_line = toolbar->AddButton(new Texture2D("apps/mapeditor/b_line.png"));
	auto b_rect = toolbar->AddButton(new Texture2D("apps/mapeditor/b_rect.png"));
	auto b_rectfill = toolbar->AddButton(new Texture2D("apps/mapeditor/b_rectfill.png"));
	auto b_erase = toolbar->AddButton(new Texture2D("apps/mapeditor/b_erase.png"));
	auto b_fill = toolbar->AddButton(new Texture2D("apps/mapeditor/b_fill.png"));

	b_paste->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_Paste;
		});

	b_line->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_Line;
		});

	b_rect->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_Rect;
		});
	b_rectfill->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_RectFill;
		});

	b_erase->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_Erase;
		});

	b_fill->SetOnClick([&](void* data) {

		MapViewFB::m_EditMode = EM_Fill;

		});






	//auto b1 = toolbar->AddButton("Rect");
	//auto b2 = toolbar->AddButton("Fill");


	/*
	b1->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_RectFill;
		});
	b2->SetOnClick([&](void* data) {
		MapViewFB::m_EditMode = EM_Fill;
		});
		*/


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
	auto m_Add = new MenuItem("Add");
	auto m_tools = new MenuItem("Tools");

	auto tile_manager = new MenuItem("Tile Manager");
	m_tools->AddItem(tile_manager);
	edit_menu->AddItem(m_File);
	edit_menu->AddItem(m_Add);
	edit_menu->AddItem(m_tools);


	auto new_map = new MenuItem("New Map");
	auto open_map = new MenuItem("Open Map");
	auto save_map = new MenuItem("Save Map");
	auto save_as_map = new MenuItem("Save As Map");

	m_File->AddItem(new_map);
	m_File->AddItem(open_map);
	m_File->AddItem(save_map);
	m_File->AddItem(save_as_map);
	auto exit = new MenuItem("Exit");
	m_File->AddItem(exit);

	new_map->OnClick = [&]() {

		CreateMapWindow* mapWindow = new CreateMapWindow();

		// Set up callback for when map is created
		mapWindow->OnMapCreated = [&](GameMap* newMap) {
			// Do something with the new map
			// For example:
			// m_CurrentMap = newMap;
			// InitializeMap(newMap);
			m_EditMap = newMap;
			m_MapViewFB->SetMap(m_EditMap);
			};

		// Add window to UI
		GameUI::m_Inst->GetWindowSurface()->AddChild(mapWindow);

		};
	
	save_map->OnClick = [&]() {
		std::vector<FileRequester::FileFilter> filters;
		filters.push_back({ "Map Files", "*.map" });

		// Get save location from user
		std::string mapFilePath = FileRequester::SaveFile(
			"Save Map File",  // Dialog title
			filters,          // Only allow .map files
			"new_map.map",    // Default filename
			""                // No specific initial directory
		);

		m_EditMap->SaveMap(mapFilePath);

		};

	open_map->OnClick = [&]() {
		std::vector<FileRequester::FileFilter> filters;
		filters.push_back({ "Map Files", "*.map" });
		// Get file location from user
		std::string mapFilePath = FileRequester::OpenFile(
			"Open Map File",  // Dialog title
			filters,          // Only allow .map files
			""                // No specific initial directory
		);
		m_EditMap->OpenMap(mapFilePath);
		m_MapViewFB->SetMap(m_EditMap);
		};

	auto a_light = new MenuItem("Light");

	m_Add->AddItem(a_light);
	
	auto l_point = new MenuItem("Point Light");
	auto l_spot = new MenuItem("Spot Light");
	
	a_light->AddItem(l_point);
	a_light->AddItem(l_spot);





	win->SetMenu(edit_menu);


	tile_manager->OnClick = [&]() {

		auto tm = new TileManager;
		GameUI::m_Inst->GetWindowSurface()->AddChild(tm);

		};


	l_point->OnClick = [&]() {

		auto new_Light = new GameLight;
		new_Light->SetRange(1024);
		new_Light->SetPosition(glm::vec3(512, 512,350));
		m_EditMap->AddLight(new_Light);


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

void AppMapEditor::SetObject(GameObj* obj) {


		if (obj == nullptr) {
			m_Properties->GetClientArea()->ClearChildren();
			return;
		}
		m_SelectedObj = obj;
		
		m_Properties->GetClientArea()->ClearChildren();

		IPropertyEditor* m_Edit = new IPropertyEditor;

		auto g_obj = new PropertyGroup("Object");


		//auto info = new PropertyGroup("Info");
		//auto images = new PropertyGroup("Images");
		//auto rendering = new PropertyGroup("Rendering");




		m_Properties->GetClientArea()->AddChild(m_Edit);
		m_Properties->ApplyDockChildren();
		m_Edit->AddGroup(g_obj);
		//m_Edit->AddGroup(images);
		//m_Edit->AddGroup(rendering);


		auto name = g_obj->AddItem(new PropertyItem("Name", PT_Text));
		auto pos = g_obj->AddItem(new PropertyItem("Position", PT_Vec3));
	
		pos->m_VX->SetNumber(obj->GetPosition().x);
		pos->m_VY->SetNumber(obj->GetPosition().y);
		pos->m_VZ->SetNumber(obj->GetPosition().z);

		if (dynamic_cast<GameLight*>(obj)) {

			auto light = (GameLight*)obj;

			auto g_light = new PropertyGroup("Light");
			m_Edit->AddGroup(g_light);
			auto diff = g_light->AddItem(new PropertyItem("Color", PT_Vec3));
			auto range = g_light->AddItem(new PropertyItem("Range", PT_Float));
			diff->m_VX->SetNumber(light->GetDiffuse().x);
			diff->m_VY->SetNumber(light->GetDiffuse().y);
			diff->m_VZ->SetNumber(light->GetDiffuse().z);
			range->m_Float->SetNumber(light->GetRange());
			m_Diff = diff;
			m_Range = range;
		
			diff->m_VX->SetOnEnter([&](void* data)
				{
					auto light = (GameLight*)m_SelectedObj;
					light->SetDiffuse(glm::vec3(m_Diff->m_VX->GetNumber(), m_Diff->m_VY->GetNumber(), m_Diff->m_VZ->GetNumber()));
				});
			diff->m_VY->SetOnEnter([&](void* data)
				{
					auto light = (GameLight*)m_SelectedObj;
					light->SetDiffuse(glm::vec3(m_Diff->m_VX->GetNumber(), m_Diff->m_VY->GetNumber(), m_Diff->m_VZ->GetNumber()));
				});
			diff->m_VZ->SetOnEnter([&](void* data)
				{
					auto light = (GameLight*)m_SelectedObj;
					light->SetDiffuse(glm::vec3(m_Diff->m_VX->GetNumber(), m_Diff->m_VY->GetNumber(), m_Diff->m_VZ->GetNumber()));
				});

			range->m_Float->SetOnEnter([&](void* data)
				{
					auto light = (GameLight*)m_SelectedObj;
					light->SetRange(m_Range->m_Float->GetNumber());
				});

		}

		m_Pos = pos;

		pos->m_VX->SetOnEnter([&](void* data)
			{
				m_SelectedObj->SetPosition(glm::vec3(m_Pos->m_VX->GetNumber(),m_Pos->m_VY->GetNumber(), m_Pos->m_VZ->GetNumber()));
			});
		
		pos->m_VY->SetOnEnter([&](void* data)
			{
				m_SelectedObj->SetPosition(glm::vec3(m_Pos->m_VX->GetNumber(), m_Pos->m_VY->GetNumber(), m_Pos->m_VZ->GetNumber()));
			});
		pos->m_VZ->SetOnEnter([&](void* data)
			{
				m_SelectedObj->SetPosition(glm::vec3(m_Pos->m_VX->GetNumber(), m_Pos->m_VY->GetNumber(), m_Pos->m_VZ->GetNumber()));
			});




		return;

	

}

void AppMapEditor::UpdateObj() {


	m_Pos->m_VX->SetNumber(m_SelectedObj->GetPosition().x);
	m_Pos->m_VY->SetNumber(m_SelectedObj->GetPosition().y);
	m_Pos->m_VZ->SetNumber(m_SelectedObj->GetPosition().z);



}