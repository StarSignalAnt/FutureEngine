#include "TestApp1.h"
#include <glm/glm.hpp>
#include "IWindow.h"
#include "IMainMenu.h"
#include "IImage.h"
#include "Texture2D.h"
#include "IVideoPlayer.h"
#include "FPApps.h"

TestApp1::TestApp1() {

	SetName("Test App");

}

void TestApp1::InitApp() {

	int b = 5;
	IWindow* win = new IWindow("Test App",glm::vec2(200, 200), glm::vec2(400, 300));
	
	IImage* img = new IImage(glm::vec2(40, 40), glm::vec2(400, 400));

	//win->AddClientControl(img);
	IVideoPlayer* pl = new IVideoPlayer("test/fcintro.mp4",glm::vec2(0, 0), glm::vec2(505, 505));
	//pl->SetDockType(DockType::m_Fill);
	pl->Set(glm::vec2(0, 0), glm::vec2(512, 512));

	//pl->SetVideo("test/fcintro.mp4");

	pl->Play();

	win->AddClientControl(pl);

	img->SetImage(new Texture2D("test/test1.png"));

	auto menu = new IMainMenu;
	win->SetAppTitle("Future Editor");
	win->SetMenu(menu);


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

	SetIcon(new Texture2D("apps/testapp/icon.png"));


	m_StartWindow = win;


}