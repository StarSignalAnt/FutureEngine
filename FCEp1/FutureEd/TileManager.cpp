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
#include "BinaryFile.h"
#include "IWindow.h"
#include "IImage.h"
#include "ILabel.h"
#include "IPropertyEditor.h"

GameTile* TileManager::m_SelectedTile = nullptr;
TileManager* TileManager::m_Inst = nullptr;

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
	m_Inst = this;
	m_Dock = new IDocker(glm::vec2(0, 0), glm::vec2(200, 200));
	m_Dock->SetDockType(DockType::m_Fill);

	AddClientControl(m_Dock);

	m_TileTree = new IWindow("Tiles", glm::vec2(20, 20), glm::vec2(220, 202),false);

	m_Dock->DockWindow(m_TileTree, DockArea::DOCK_LEFT);

	m_TileView = new IWindow("Tile View", glm::vec2(20, 20), glm::vec2(220, 220),false);

	m_Dock->DockWindow(m_TileView, DockArea::DOCK_CENTER);

	m_TileProps = new IWindow("Tile Properties", glm::vec2(20, 20), glm::vec2(300, 300), false);
	m_Dock->DockWindow(m_TileProps, DockArea::DOCK_RIGHT);


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

			Save();
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
				Save();
				RebuildTree();



			}
		}
		};

	Load();
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
				m_View = view;
				m_CGroup = (TileGroup*)node->GetUserData();


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

void TileManager::Save() {

	FFile* f = new FFile("apps/mapeditor/tiles.dat",false);

	f->writeInt(m_Groups.size());

	for (auto g : m_Groups) {

		f->writeString(g->GetName());
		f->writeInt(g->GetTiles().size());

		for (auto t : g->GetTiles()) {


			f->writeBool(t->GetCastShadows());
			f->writeBool(t->GetReceivesShadows());
			f->writeBool(t->GetReceivesLight());
			f->writeString(t->GetName());

			f->writeInt(t->GetFrameCount());

			for (int tf = 0; tf < t->GetFrameCount(); tf++) {

				auto frame = t->GetFrame(tf);

				f->writeString(frame[0]->GetPath());
				f->writeString(frame[1]->GetPath());

			}

		}

	}

	f->close();

}

void TileManager::Load() {


	m_Groups.clear();

	if (FFile::fileExists("apps/mapeditor/tiles.dat")) {

		FFile* f = new FFile("apps/mapeditor/tiles.dat", true);

	
		int gc = f->readInt();

		for (int g = 0; g < gc; g++) {

			TileGroup* group = new TileGroup;
			m_Groups.push_back(group);
			auto name = f->readString();
			group->SetName(name);
			int tc = f->readInt();

			for (int t = 0; t < tc; t++) {

				GameTile* tile = new GameTile;

				bool castShadows = f->readBool();
				bool recvShadows = f->readBool();
				bool recvLight = f->readBool();

				auto name = f->readString();

				int fc = f->readInt();

				tile->Set(castShadows, recvShadows, recvLight);
				tile->SetName(name);


				for (int tf = 0; tf < fc; tf++) {

					auto dif = f->readString();
					auto norm = f->readString();

					if (norm == "") {
						tile->AddFrame(new Texture2D(dif), nullptr);
					}
					else {
						tile->AddFrame(new Texture2D(dif), new Texture2D(norm));
					}
					

				}

				group->AddTile(tile);

			}

		}

		f->close();

	}
	RebuildTree();
}

GameTile* TileManager::FindTile(std::string name) {

	for (auto g : m_Groups) {

		for (auto t : g->GetTiles()) {

			if (t->GetName() == name) {
				return t;
			}

		}

	}

}

void TileManager::SetPropTile(GameTile* tile) {


	if (tile == nullptr) {
		m_TileProps->GetClientArea()->ClearChildren();
		return;
	}
	m_SelectedTile = tile;
	m_TileProps->GetClientArea()->ClearChildren();

	IPropertyEditor* m_Edit = new IPropertyEditor;

	auto info = new PropertyGroup("Info");
	auto images = new PropertyGroup("Images");
	auto rendering = new PropertyGroup("Rendering");



	m_TileProps->GetClientArea()->AddChild(m_Edit);
	m_TileProps->ApplyDockChildren();
	m_Edit->AddGroup(info);
	m_Edit->AddGroup(images);
	m_Edit->AddGroup(rendering);

	auto name = info->AddItem(new PropertyItem("Name", PT_Text));
	auto col = images->AddItem(new PropertyItem("Color Map", PT_Image));
	auto norm = images->AddItem(new PropertyItem("Normal Map", PT_Image));
	auto castShadows = rendering->AddItem(new PropertyItem("Cast Shadows", PT_Check));
	auto recvShadows = rendering->AddItem(new PropertyItem("Receive Shadows", PT_Check));
	auto recvLight = rendering->AddItem(new PropertyItem("Receive Light", PT_Check));
	//auto v1 = rendering->AddItem(new PropertyItem("Position", PT_Vec3));
	castShadows->m_PropCheck->SetChecked(m_SelectedTile->GetCastShadows());
	recvShadows->m_PropCheck->SetChecked(m_SelectedTile->GetReceivesShadows());
	recvLight->m_PropCheck->SetChecked(m_SelectedTile->GetReceivesLight());
	m_ColProp = col;
	m_NormProp = norm;

	col->m_ImgDot->SetOnClick([&](void* data) {
		std::vector<FileRequester::FileFilter> imageFilters = {
FileRequester::FileFilter("PNG Files", "*.png"),
FileRequester::FileFilter("JPEG Files", "*.jpg;*.jpeg"),
FileRequester::FileFilter("BMP Files", "*.bmp"),
FileRequester::FileFilter("TGA Files", "*.tga"),
FileRequester::FileFilter("GIF Files", "*.gif"),
FileRequester::FileFilter("All Image Files", "*.png;*.jpg;*.jpeg;*.bmp;*.tga;*.gif")
		};
		auto img = FileRequester::OpenFile("Select Color Image", imageFilters);
		m_SelectedTile->SetColorFrame(new Texture2D(img), 0);
		Save();
		m_View->SetGroup(m_CGroup);
		m_ColProp->m_PropImage->SetImage(m_SelectedTile->GetFrame(0)[0]);
	});

		norm->m_ImgDot->SetOnClick([&](void* data) {
			std::vector<FileRequester::FileFilter> imageFilters = {
	FileRequester::FileFilter("PNG Files", "*.png"),
	FileRequester::FileFilter("JPEG Files", "*.jpg;*.jpeg"),
	FileRequester::FileFilter("BMP Files", "*.bmp"),
	FileRequester::FileFilter("TGA Files", "*.tga"),
	FileRequester::FileFilter("GIF Files", "*.gif"),
	FileRequester::FileFilter("All Image Files", "*.png;*.jpg;*.jpeg;*.bmp;*.tga;*.gif")
			};
			auto img = FileRequester::OpenFile("Select Color Image", imageFilters);

			m_SelectedTile->SetNormalFrame(new Texture2D(img), 0);
			Save();
			m_View->SetGroup(m_CGroup);
			m_NormProp->m_PropImage->SetImage(m_SelectedTile->GetFrame(0)[1]);


			});


	castShadows->m_PropCheck->SetOnCheck([&](bool ch) {
		m_SelectedTile->SetCastShadows(ch);
		Save();
		});
	recvShadows->m_PropCheck->SetOnCheck([&](bool ch) {
		m_SelectedTile->SetRecvShadows(ch);
		Save();
		});
	recvLight->m_PropCheck->SetOnCheck([&](bool ch) {

		m_SelectedTile->SetRecvLight(ch);
		Save();
		});



	col->SetImage(tile->GetFrame(0)[0]);
	norm->SetImage(tile->GetFrame(0)[1]);






	return;

	auto dif_img = new IImage(glm::vec2(75, 20), glm::vec2(96, 96));
	dif_img->SetImage(tile->GetFrame(0)[0]);

	m_TileProps->GetClientArea()->AddChild(dif_img);

	auto norm_img = new IImage(glm::vec2(75, 124),glm::vec2(96, 96));
	norm_img->SetImage(tile->GetFrame(0)[1]);

	auto dif_lab = new ILabel("Color", glm::vec2(5, 80));
	auto norm_lab = new ILabel("Normal", glm::vec2(5, 174));

	m_TileProps->GetClientArea()->AddChild(norm_img);
	m_TileProps->GetClientArea()->AddChild(dif_lab);
	m_TileProps->GetClientArea()->AddChild(norm_lab);

	auto dif_browse = new IButton("Browse", glm::vec2(185, 87),glm::vec2(80,30));
	auto norm_browse = new IButton("Browse", glm::vec2(185, 189),glm::vec2(80,30));

	m_TileProps->GetClientArea()->AddChild(dif_browse);
	m_TileProps->GetClientArea()->AddChild(norm_browse);

	dif_browse->SetOnClick([&](void* data) {
		std::vector<FileRequester::FileFilter> imageFilters = {
	FileRequester::FileFilter("PNG Files", "*.png"),
	FileRequester::FileFilter("JPEG Files", "*.jpg;*.jpeg"),
	FileRequester::FileFilter("BMP Files", "*.bmp"),
	FileRequester::FileFilter("TGA Files", "*.tga"),
	FileRequester::FileFilter("GIF Files", "*.gif"),
	FileRequester::FileFilter("All Image Files", "*.png;*.jpg;*.jpeg;*.bmp;*.tga;*.gif")
		};
		
			auto file = FileRequester::OpenFile("Open Color Image", imageFilters);
			m_SelectedTile->SetColorFrame(new Texture2D(file), 0);
			SetPropTile(m_SelectedTile);

		});

	norm_browse->SetOnClick([&](void* data) {
		std::vector<FileRequester::FileFilter> imageFilters = {
	FileRequester::FileFilter("PNG Files", "*.png"),
	FileRequester::FileFilter("JPEG Files", "*.jpg;*.jpeg"),
	FileRequester::FileFilter("BMP Files", "*.bmp"),
	FileRequester::FileFilter("TGA Files", "*.tga"),
	FileRequester::FileFilter("GIF Files", "*.gif"),
	FileRequester::FileFilter("All Image Files", "*.png;*.jpg;*.jpeg;*.bmp;*.tga;*.gif")
		};

		auto file = FileRequester::OpenFile("Open Color Image", imageFilters);
		m_SelectedTile->SetNormalFrame(new Texture2D(file), 0);
		SetPropTile(m_SelectedTile);

		});

	


}