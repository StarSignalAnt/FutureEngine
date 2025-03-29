#include "TileManager.h"
#include "IDocker.h"
#include "ITreeView.h"
#include "IMainMenu.h"
#include <iostream>
#include "IGetName.h"
#include "FileRequester.h"
#include "TileGroup.h"
#include "GameTile.h"
#include "IControlGroup.h"
#include "GroupView.h"
std::vector<std::string> LoadMultipleImageFiles(const std::string& initialDir = "") {
	// Define common image file filters
	std::vector<FileRequester::FileFilter> imageFilters = {
		FileRequester::FileFilter("PNG Files", "*.png"),
		FileRequester::FileFilter("JPEG Files", "*.jpg;*.jpeg"),
		FileRequester::FileFilter("BMP Files", "*.bmp"),
		FileRequester::FileFilter("TGA Files", "*.tga"),
		FileRequester::FileFilter("GIF Files", "*.gif"),
		FileRequester::FileFilter("All Image Files", "*.png;*.jpg;*.jpeg;*.bmp;*.tga;*.gif")
	};

	// Use the multi-file selection function
	return FileRequester::OpenMultipleFiles("Load Tile Images", imageFilters, initialDir);
}
std::vector<TileGroup*> TileManager::m_Groups;

void TileManager::Setup() {

	m_Dock = new IDocker(glm::vec2(0, 0), glm::vec2(200, 200));
	m_Dock->SetDockType(DockType::m_Fill);

	AddClientControl(m_Dock);

	m_TileTree = new IWindow("Tiles", glm::vec2(20, 20), glm::vec2(220, 202));

	m_Dock->DockWindow(m_TileTree, DockArea::DOCK_LEFT);

	m_TileView = new IWindow("Tile View", glm::vec2(20, 20), glm::vec2(220, 220));

	m_Dock->DockWindow(m_TileView, DockArea::DOCK_CENTER);



	m_Tree = new ITreeView(glm::vec2(5, 5), glm::vec2(10, 10));

	m_Tree->SetDockType(DockType::m_Fill);

	m_TileTree->AddClientControl(m_Tree);

	IMainMenu* edit_menu = new IMainMenu;
	edit_menu->SetAppTitle("Tile Manager");
	auto m_File = new MenuItem("Tiles");
	//auto m_tools = new MenuItem("Tools");

	auto new_g = new MenuItem("New Group");
	auto add_tile = new MenuItem("Add Tile/s");

	//	auto tile_manager = new MenuItem("Tile Manager");
	//	m_tools->AddItem(tile_manager);/
	//	edit_menu->AddItem(m_File);
	//	edit_menu->AddItem(m_tools);

	m_File->AddItem(new_g);
	m_File->AddItem(add_tile);

	edit_menu->AddItem(m_File);

	//edit_menu->AddItem(add_tile);

	this->SetMenu(edit_menu);

	new_g->OnClick = [&]() {

		new IGetName("Tile Group Name", "Create Group", [&](std::string name) {
			// This function will be called when the user clicks OK or presses Enter
			// Handle the entered name here
			//std::cout << "User entered: " << name << std::endl;

			TileGroup* group = new TileGroup;
			group->SetName(name);
			m_Groups.push_back(group);

			RebuildTree();

			// Save the file or perform other actions with the name
			});

		};

	add_tile->OnClick = [&]() {


		auto g = m_Tree->GetSelectedNode();
		if (g == nullptr) return;
		if (g->GetType() == "TileGroup") {
			auto files = LoadMultipleImageFiles("");

			for (auto file : files) {

				GameTile* tile = new GameTile;
				tile->AddFrame(new Texture2D(file), nullptr);
				tile->SetName(file);
				auto g = m_Tree->GetSelectedNode();
				if (g->GetType() == "TileGroup") {
					TileGroup* gp = (TileGroup*)g->GetUserData();

					if (gp != nullptr) {
						gp->AddTile(tile);
					}

				}

				RebuildTree();



			}
		}
		};

}

void TileManager::RebuildTree() {


	Texture2D* folderIcon = new Texture2D("engine/ui/folder.png");
	Texture2D* fileIcon = new Texture2D("engine/ui/file.png");
	Texture2D* expandedIcon = new Texture2D("engine/ui/expanded.png");
	Texture2D* collapsedIcon = new Texture2D("engine/ui/collapsed.png");

	// Set custom expand/collapse icons
	m_Tree->SetExpandedIcon(expandedIcon);
	m_Tree->SetCollapsedIcon(collapsedIcon);
	m_Tree->ClearNodes();

	ITreeNode* projectNode = new ITreeNode("Tiles", folderIcon);
   
	m_Tree->AddRootNode(projectNode);

	for (auto group : m_Groups) {

		ITreeNode* group_node = new ITreeNode(group->GetName(), fileIcon);
		projectNode->AddChild(group_node);
		group_node->SetUserData(group);
		group_node->SetType("TileGroup");


		for (auto tile : group->GetTiles()) {

			ITreeNode* m_Tile = new ITreeNode(tile->GetName());
			m_Tile->SetUserData(tile);
			group_node->AddChild(m_Tile);
			m_Tile->SetType("GameTile");

		}

	}


	m_Tree->ExpandAll();

	// Set up the node selection callback
	m_Tree->SetOnNodeSelected([&](ITreeNode* node) {
		// This function will be called whenever a node is selected
		if (node) {
			std::cout << "Node selected: " << node->GetText() << std::endl;

			if (node->GetType() == "TileGroup")
			{

				m_TileView->GetClientArea()->ClearChildren();
				auto view = new GroupView;
				view->SetDockType(DockType::m_Fill);
				m_TileView->GetClientArea()->AddChild(view);
				view->SetGroup((TileGroup*)node->GetUserData());


			}
			if (node->GetType() == "GameTile") {
				// You can access the node's user data if it was set
				void* userData = node->GetUserData();

				if (static_cast<GameTile*>(userData)) {

					auto gt = (GameTile*)userData;
					int b = 5;

					// Cast to appropriate type and use the data
					// MyDataType* data = static_cast<MyDataType*>(userData);
					// Process the data...
				}

				// Perform actions based on the selected node
				// For example, update UI elements, load content, etc.
			}
			else {
				std::cout << "No node selected" << std::endl;
			}
		}});

		
}
