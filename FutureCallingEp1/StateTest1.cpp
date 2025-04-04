#include "StateTest1.h"
#include "MathsOps.h"
#include "GameCam.h"
#include "GameMap.h"
#include "GameTile.h"
#include "GameLight.h"
#include "GameInput.h"
#include "FutureApp.h"
#include "GameSprite.h"
#include "GameUI.h"
#include "GameAnimation.h"
#include "RenderTarget2D.h"
#include "IImage.h"
#include "IButton.h"
#include "GameVideo.h"
#include <iostream>
#include "IWindow.h"
#include "IControlGroup.h"
#include "IVideoPlayer.h"
#include "IFrameBuffer.h"
#include "UIHelp.h"
#include "IDocker.h"
#include "IMainMenu.h"
#include "FileRequester.h";
#include "ITextEdit.h"
#include "IComboBox.h"
#include "ITreeNode.h"
#include "ITreeView.h"
#include "IDateSelector.h"
#include "ITimeSelector.h"
#include "ISizebox.h"

// Adding a 
// context menu option to undock windows:

void StateTest1::InitState()
{
	m_Tex1 = new Texture2D("test/test2.png");
	m_Tex2 = new Texture2D("test/test2.png");
	m_UI = new GameUI;
	
	/*
	IWindowDockHandler::GetInstance()->Initialize(m_UI->GetRoot());

	auto gameUI = m_UI;

	// Create the window dock (normally you would size this to fill most of your application area)
	IWindowDock* mainDock = new IWindowDock(
		glm::vec2(0, 0),  // Position
		glm::vec2(FutureApp::m_Inst->GetWidth(),FutureApp::m_Inst->GetHeight())  // Size
	);

	// Add the dock to your UI
	gameUI->GetRoot()->AddChild(mainDock);

	// Register the dock with the handler
	IWindowDockHandler::GetInstance()->RegisterDock(mainDock);

	// Create some example windows
	IWindow* window1 = new IWindow("Window 1", glm::vec2(100, 100), glm::vec2(400, 300));
	IWindow* window2 = new IWindow("Window 2", glm::vec2(200, 150), glm::vec2(400, 300));
	IWindow* window3 = new IWindow("Window 3", glm::vec2(300, 200), glm::vec2(400, 300));

	// Add windows to your UI
	gameUI->GetRoot()->AddChild(window1);
	gameUI->GetRoot()->AddChild(window2);
	gameUI->GetRoot()->AddChild(window3);

	// Optionally, pre-dock some windows
	mainDock->DockWindow(window1, DOCK_LEFT);

	//mainDock->DockWindow(window2, DOCK_LEFT);  // This will create a tab with window1
	mainDock->DockWindow(window3, DOCK_CENTER);




	return;
	*/

	auto norm1 = new Texture2D("test/norm4.png");
	auto norm2 = new Texture2D("test/norm3.png");
	m_Draw = new SmartDraw;

	m_Map1 = new GameMap(16, 16, 3, 128, 128);

	m_Tile1 = new GameTile;
	m_Tile1->AddFrame(m_Tex1,nullptr);

	m_Tile2 = new GameTile;
	m_Tile2->AddFrame(m_Tex2,nullptr);
	m_Tile2->Set(true, false, true);

	m_Tile1->Set(false, true, true);


	m_Map1->Fill(m_Tile1, 0);


	m_Map1->FIllBlock(m_Tile2, 2, 2, 4, 1, 0);
	m_Map1->FIllBlock(m_Tile2, 2, 5, 4, 1, 0);

	m_Cam1 = new GameCam;

	m_Light1 = new GameLight;

	m_Light1->SetPosition(glm::vec3(400, 450, 356.0f));

	m_Map1->AddLight(m_Light1);

	m_RT1 = new RenderTarget2D(1024, 768);

	int a = 5;
	//m_Cam1->SetPosition(glm::vec3(300,300, 0));

	m_Spr1 = new GameSprite;

	auto spr1 = new Texture2D("test/spr1.png");

	auto anim1 = new GameAnimation("Idle");
	anim1->AddFrame(spr1, nullptr);

	m_Spr1->AddAnimation(anim1);
	m_Spr1->PlayAnimation("Idle");

	m_Map1->AddSprite(m_Spr1);

	m_Spr1->SetPosition(glm::vec3(200, 350, 1));

	

	IImage* img1 = new IImage(glm::vec2(0,0), glm::vec2(FutureApp::m_Inst->GetWidth(),FutureApp::m_Inst->GetHeight()));
	img1->SetImage(m_Tex1);
	m_UI->GetRoot()->AddChild(img1);
	img1->SetDockType(DockType::m_Fill);


	auto dock = new IDocker(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()));
	m_UI->GetRoot()->AddChild(dock);


	IButton* but1 = new IButton("Testing",glm::vec2(450, 200), glm::vec2(168, 80));
	//m_UI->GetRoot()->AddChild(but1);

	but1->SetOnClick([](void * data) {
		//std::cout << "Button clicked! (Lambda function)" << std::endl;
		});
	but1->SetOnDoubleClick([]() {
		std::cout << "Double Click!" << std::endl;
		});

	auto win1 = new IWindow("Test Window", glm::vec2(400, 100), glm::vec2(300, 300));
	auto win2 = new IWindow("Other Window", glm::vec2(550, 100), glm::vec2(300, 300));
	m_UI->GetRoot()->AddChild(win1);
	m_UI->GetRoot()->AddChild(win2);
	auto wb1 = new IButton("Load Game", glm::vec2(20, 60), glm::vec2(130, 30));
	auto wb2 = new IButton("Save Game", glm::vec2(600, 600), glm::vec2(130, 30));


	wb1->SetOnClick([&](void * data) {

		std::vector<FileRequester::FileFilter> videoFilters = {
	 {"Video Files", "*.mp4;*.avi;*.mkv"},
	 {"MP4 Files", "*.mp4"},
	 {"AVI Files", "*.avi"}
		};

		// Open file dialog with filters
		std::string filePath = FileRequester::OpenFile("Open Video", videoFilters);

		if (!filePath.empty()) {
			std::cout << "Selected file: " << filePath << std::endl;
			// Open the file...
		}

		});
	win1->AddClientControl(wb1);
	win1->AddClientControl(wb2);

	auto menu = new IMainMenu;
	win1->SetAppTitle("Future Editor");
	win1->SetMenu(menu);


	MenuItem* file = new MenuItem("File");
	MenuItem* edit = new MenuItem("Edit");
	MenuItem* options = new MenuItem("Options");

	menu->AddItem(file);
	menu->AddItem(edit);
	menu->AddItem(options);

	MenuItem* new_project = new MenuItem("New File");
	MenuItem* save_project = new MenuItem("Save File");
	MenuItem* load_project = new MenuItem("Load Project");

	MenuItem* edit_cut = new MenuItem("Cut");
	MenuItem* edit_paste = new MenuItem("Paste");
	MenuItem* edit_copy = new MenuItem("Copy");

	MenuItem* cut_Test = new MenuItem("Test 1");
	MenuItem* cut_test2 = new MenuItem("This is another test");
	MenuItem* cut_test3 = new MenuItem("And so is this");

	edit_cut->AddItem(cut_Test);
	edit_cut->AddItem(cut_test2);
	edit_cut->AddItem(cut_test3);

	cut_test2->AddItem(new MenuItem("Other one"));
	cut_test2->AddItem(new MenuItem("Another test"));

	file->AddItem(new_project);
	file->AddItem(save_project);
	file->AddItem(load_project);

	edit->AddItem(edit_cut);
	edit->AddItem(edit_paste);
	edit->AddItem(edit_copy);



	cut_Test->OnClick = [&]() {

		exit(5);

		};


	auto vid = new IVideoPlayer("test/testVideo2.mp4", glm::vec2(20, 20), glm::vec2(512, 512));
	vid->SetDockType(DockType::m_Fill);
	//win1->GetClientArea()->SetCullChildren(false);

	auto fb = new IFrameBuffer(glm::vec2(20, 20), glm::vec2(512, 512));

	fb->SetOnPreRender([&]() {

		m_Draw->Begin();
		m_Draw->Draw(glm::vec2(256, 256), glm::vec2(512,512), glm::vec4(1, 1, 1, 1), m_Tex1, 0, 1.0f);
		m_Draw->End();

		});

	//win1->GetRoot()->AddChild(vid);
	//win2->AddClientControl(dock);
	ITextEdit* m_NameInput;

	m_NameInput = new ITextEdit();
	m_NameInput->Set(glm::vec2(20, 40), glm::vec2(360, 30));
	m_NameInput->SetText("John Doe");
	//panel->AddChild(m_NameInput);

	//m_UI->GetRoot()->AddChild(m_NameInput);

	IComboBox* comboBox = new IComboBox(glm::vec2(100, 100), glm::vec2(200, 30));

	// Add items
	comboBox->AddItem("Option 1");
	comboBox->AddItem("Option 2");
	comboBox->AddItem("Option 3");

	// Set a callback for selection changes
	comboBox->SetOnSelectionChanged([](int index, std::string item) {
		std::cout << "Selected: " << item << " (index: " << index << ")" << std::endl;
		});

	// Add to your UI
	//GameUI::m_Inst->GetRoot()->AddChild(comboBox);


	vp = vid;
//	win1->AddClientControl(fb);

	vid->Play();

	ITreeView* treeView = new ITreeView(glm::vec2(50, 50), glm::vec2(300, 400));

	// Load icons
	Texture2D* folderIcon = new Texture2D("engine/ui/folder.png");
	Texture2D* fileIcon = new Texture2D("engine/ui/file.png");
	Texture2D* expandedIcon = new Texture2D("engine/ui/expanded.png");
	Texture2D* collapsedIcon = new Texture2D("engine/ui/collapsed.png");

	// Set custom expand/collapse icons
	treeView->SetExpandedIcon(expandedIcon);
	treeView->SetCollapsedIcon(collapsedIcon);

	// Create a root node
	ITreeNode* projectNode = new ITreeNode("My Project", folderIcon);

	// Add source folder
	ITreeNode* sourceNode = new ITreeNode("Source", folderIcon);
	projectNode->AddChild(sourceNode);
	for (int i = 0; i < 50; i++) {
		ITreeNode* nn = new ITreeNode("Test!!!", fileIcon);
		projectNode->AddChild(nn);
	}

	// Add source files
	sourceNode->AddChild(new ITreeNode("Main.cpp", fileIcon));
	sourceNode->AddChild(new ITreeNode("GameState.cpp", fileIcon));
	sourceNode->AddChild(new ITreeNode("Player.cpp", fileIcon));

	// Add assets folder
	ITreeNode* assetsNode = new ITreeNode("Assets", folderIcon);
	projectNode->AddChild(assetsNode);

	// Add asset subfolders and files
	ITreeNode* texturesNode = new ITreeNode("Textures", folderIcon);
	assetsNode->AddChild(texturesNode);
	texturesNode->AddChild(new ITreeNode("grass.png", fileIcon));
	texturesNode->AddChild(new ITreeNode("sky.png", fileIcon));

	ITreeNode* modelsNode = new ITreeNode("Models", folderIcon);
	assetsNode->AddChild(modelsNode);
	modelsNode->AddChild(new ITreeNode("character.fbx", fileIcon));
	modelsNode->AddChild(new ITreeNode("weapon.fbx", fileIcon));

	ITreeNode* audioNode = new ITreeNode("Audio", folderIcon);
	assetsNode->AddChild(audioNode);
	audioNode->AddChild(new ITreeNode("music.mp3", fileIcon));
	audioNode->AddChild(new ITreeNode("effect.wav", fileIcon));

	// Add resources folder
	ITreeNode* resourcesNode = new ITreeNode("Resources", folderIcon);
	projectNode->AddChild(resourcesNode);
	resourcesNode->AddChild(new ITreeNode("config.json", fileIcon));
	resourcesNode->AddChild(new ITreeNode("settings.ini", fileIcon));

	// Add build folder
	ITreeNode* buildNode = new ITreeNode("Build", folderIcon);
	projectNode->AddChild(buildNode);
	buildNode->AddChild(new ITreeNode("bin", folderIcon));
	buildNode->AddChild(new ITreeNode("lib", folderIcon));

	// Add root node to tree view
	treeView->AddRootNode(projectNode);

	// Set callback for node selection
	treeView->SetOnNodeSelected([](ITreeNode* node) {
		std::cout << "Selected: " << node->GetText() << std::endl;
		});

	// Set callback for node expansion
	treeView->SetOnNodeExpanded([](ITreeNode* node) {
		std::cout << "Expanded: " << node->GetText() << std::endl;
		});

	// Set callback for node collapse
	treeView->SetOnNodeCollapsed([](ITreeNode* node) {
		std::cout << "Collapsed: " << node->GetText() << std::endl;
		});

	// Set individual node click callback
	sourceNode->SetOnClick([](ITreeNode* node) {
		std::cout << "Source folder clicked!" << std::endl;
		});

	// Expand some nodes by default
	treeView->ExpandNode(projectNode);
	treeView->ExpandNode(sourceNode);
	treeView->ExpandNode(assetsNode);

	// Add tree view to the UI
	//GameUI::m_Inst->GetRoot()->AddChild(treeView);
	//return;
	IDateSelector* dateSelector = new IDateSelector(glm::vec2(50, 50), glm::vec2(350, 40));

	// Load a calendar icon (optional)
	Texture2D* calendarIcon = new Texture2D("engine/ui/calendar.png");
	dateSelector->SetCalendarIcon(calendarIcon);

	// Set custom colors (optional)
	dateSelector->SetBackgroundColor(glm::vec4(0.15f, 0.15f, 0.2f, 0.9f));
	dateSelector->SetLabelColor(glm::vec4(0.8f, 0.9f, 1.0f, 1.0f));

	// Set callback for date changes
	dateSelector->SetOnDateChanged([](const Date& date) {
		std::cout << "Date changed: " << date.ToString() << std::endl;

		// Example of checking specific dates
		if (date.month == 12 && date.day == 25) {
			std::cout << "It's Christmas!" << std::endl;
		}
		else if (date.month == 1 && date.day == 1) {
			std::cout << "Happy New Year!" << std::endl;
		}
		});

	// Set a specific date (e.g., January 15, 2023)
	dateSelector->SetDate(15, 1, 2023);

	// Add to UI
	//GameUI::m_Inst->GetRoot()->AddChild(dateSelector);

	// Create a second date selector for a date range example
	IDateSelector* endDateSelector = new IDateSelector(glm::vec2(50, 100), glm::vec2(350, 40));
	endDateSelector->SetCalendarIcon(calendarIcon);

	// Set to current date + 7 days (for a simple date range)
	Date endDate;
	endDate.day += 7;
	if (endDate.day > endDate.GetDaysInMonth()) {
		endDate.day -= endDate.GetDaysInMonth();
		endDate.month++;
		if (endDate.month > 12) {
			endDate.month = 1;
			endDate.year++;
		}
	}
	endDateSelector->SetDate(endDate);

	// Add label for end date
	endDateSelector->SetOnDateChanged([dateSelector](const Date& endDate) {
		Date startDate = dateSelector->GetDate();

		// Calculate rough difference (not accounting for all edge cases)
		int startDays = startDate.day + startDate.month * 30 + startDate.year * 365;
		int endDays = endDate.day + endDate.month * 30 + endDate.year * 365;

		if (endDays < startDays) {
			std::cout << "End date cannot be before start date!" << std::endl;
		}
		else {
			std::cout << "Date range: approximately " << (endDays - startDays) << " days" << std::endl;
		}
		});

	//GameUI::m_Inst->GetRoot()->AddChild(endDateSelector);


	std::cout << "Date selectors created. Current date: " << Date().ToString() << std::endl;

//	m_Vid1 = new GameVideo("test/fcintro.mp4");
//	m_Vid1->Play();
	 // Create time selector with appropriate size
	ITimeSelector* timeSelector = new ITimeSelector(glm::vec2(50, 50), glm::vec2(300, 40));

	// Load a clock icon (optional)
	Texture2D* clockIcon = new Texture2D("engine/ui/clock.png");
	timeSelector->SetClockIcon(clockIcon);

	// Set custom colors (optional)
	timeSelector->SetBackgroundColor(glm::vec4(0.15f, 0.15f, 0.2f, 0.9f));
	timeSelector->SetLabelColor(glm::vec4(0.8f, 0.9f, 1.0f, 1.0f));
	timeSelector->SetTimeColor(glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));

	// Configure time display options
	timeSelector->SetShowSeconds(true);         // Show seconds in display
	timeSelector->SetAutoUpdateSeconds(true);   // Auto-update seconds

	// Set callback for time changes
	timeSelector->SetOnTimeChanged([](const Time& time) {
		// Print time in format: HH:MM:SS
		std::cout << "Time changed: " << time.ToString() << std::endl;

		// Example of checking specific times
		if (time.hours == 12 && time.minutes == 0 && time.seconds == 0) {
			std::cout << "It's noon!" << std::endl;
		}
		else if (time.hours == 0 && time.minutes == 0 && time.seconds == 0) {
			std::cout << "It's midnight!" << std::endl;
		}
		});

	// Set a specific time (e.g., 15:35:22)
//	timeSelector->SetTime(15, 35, 22);

	// Add to UI
	//GameUI::m_Inst->GetRoot()->AddChild(timeSelector);

	// Create a second time selector without seconds display
	ITimeSelector* timeSelector2 = new ITimeSelector(glm::vec2(50, 100), glm::vec2(300, 40));
	timeSelector2->SetClockIcon(clockIcon);
	timeSelector2->SetShowSeconds(false);       // Hide seconds in display
	timeSelector2->SetAutoUpdateSeconds(false); // Don't auto-update seconds

	// Set to same time as first selector but only showing hours:minutes
	timeSelector2->SetTime(15, 35, 22);

	// Add to UI
//	GameUI::m_Inst->GetRoot()->AddChild(timeSelector2);

	// Create a reset button (to reset both time selectors to current time)
	IButton* resetButton = new IButton("Reset",glm::vec2(50, 150), glm::vec2(120, 30));
	resetButton->SetOnClick([timeSelector, timeSelector2](void* data) {
		// Get current time and set both selectors
		Time currentTime;
		timeSelector->SetTime(currentTime);
		timeSelector2->SetTime(currentTime);
		std::cout << "Reset to current time: " << currentTime.ToString() << std::endl;
		});

	// Add to UI
	//GameUI::m_Inst->GetRoot()->AddChild(resetButton);

	ISizeBox* sizeBox = new ISizeBox(glm::vec2(100, 100), glm::vec2(300, 200));

	// Add child controls that may exceed the size box dimensions
	//IControl* childControl1 = new MyControl(glm::vec2(10, 10), glm::vec2(200, 100));
	//IControl* childControl2 = new MyControl(glm::vec2(50, 150), glm::vec2(400, 300));

	IImage* c1,* c2,* c3;
	c1 = new IImage(glm::vec2(50, 50), glm::vec2(200, 300));
	c2 = new IImage(glm::vec2(50, 360), glm::vec2(250, 450));
	c3 = new IImage(glm::vec2(100, 900), glm::vec2(400, 400));
	c1->SetImage(m_Tex1);
	c2->SetImage(m_Tex1);
	c3->SetImage(m_Tex1);


	sizeBox->AddChild(c1);
	sizeBox->AddChild(c2);
	sizeBox->AddChild(c3);

	m_UI->GetRoot()->AddChild(sizeBox);
	// Add the size box to your UI
	//rootControl->AddChild(sizeBox);


	std::cout << "Time selectors created with the following features:" << std::endl;
	std::cout << "1. Auto-updating seconds display" << std::endl;
	std::cout << "2. Edit button to open dropdown selectors" << std::endl;
	std::cout << "3. Apply/Cancel buttons when editing" << std::endl;
}


bool click = false;

void StateTest1::UpdateState(float delta)
{

	/*
	if (GameInput::Buttons[MOUSE_BUTTON_LEFT] && click == false)
	{
		if (m_Playing) {
			m_Vid1->Pause();
			m_Playing = false;
		}
		else {
			m_Vid1->Resume();
			m_Playing = true;
		}
		click = true;
	}
	else if (GameInput::Buttons[MOUSE_BUTTON_LEFT] == false) {
		click = false;
	}
	*/

	m_Ang += 10.0f * delta;

	//m_Vid1->Update();

	if (GameInput::Buttons[MOUSE_BUTTON_RIGHT]) {
		m_Cam1->MoveLocal(glm::vec2(GameInput::MouseDelta.x, GameInput::MouseDelta.y));
		//m_Cam1->SetPosition(glm::vec2(GameInput::
	}
	if (GameInput::Buttons[MOUSE_BUTTON_MIDDLE])
	{
		m_Cam1->Turn(glm::vec3(0, (GameInput::MouseDelta.x), 0 ));
	}

	m_Cam1->Zoom(GameInput::MouseDelta.z * 0.05f);
	m_Spr1->Turn(glm::vec3(0, 10*delta, 0));
	//m_Cam1->Turn(glm::vec3(0, 10.0f*delta, 0));
//	m_Cam1->Move(glm::vec3(30.0f * delta,0,0));
}


int ax = 0;
int ay = 0;

void StateTest1::RenderState()
{

	//auto frame = m_Vid1->GetFrame();
//	if (frame != nullptr) {
//		m_Draw->Begin();
//		m_Draw->DrawDirect(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()), glm::vec4(1, 1, 1, 1), frame);
//		m_Draw->End();
	//}


	
	ax = ax + 1;
	if (ax > 800) {
		ax = 0;
	//	ay = ay + 1;
	}
	
	//m_RT1->Bind();
	//m_RT1->Clear();
	m_Map1->RenderShadowMap();
	m_Map1->RenderMap(m_Cam1);
	//m_RT1->Unbind();



	
	return;
	m_Draw->Begin();
	m_Draw->DrawDirect(glm::vec2(0,FutureApp::m_Inst->GetHeight()), glm::vec2(FutureApp::m_Inst->GetWidth(),-FutureApp::m_Inst->GetHeight()), glm::vec4(1, 1, 1, 1), m_RT1->GetTexture());
	m_Draw->End();



	return;
	m_Draw->Begin();
	ax = 0;
	ay = 200;

	for (int i = 0; i < 100; i++) {
	//	ax = MathsOps::RndFloat(0, 800);
	//
	// 	ay = MathsOps::RndFloat(0, 600);
		m_Draw->Draw(glm::vec2(ax, ay), glm::vec2(220, 220), glm::abs(glm::vec4(1, 1, 1, 1)), m_Tex2, m_Ang * 2);

		ax = ax + 128;
		m_Draw->Draw(glm::vec2(ax, ay), glm::vec2(220, 220), glm::abs(glm::vec4(1, 1, 1, 1)), m_Tex1, m_Ang);
		ax = ax + 128;
	

	}


	m_Draw->End();

}

void StateTest1::EndState()
{
}
