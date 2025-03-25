#include "FSLogin.h"
#include "Texture2D.h"
#include "SmartDraw.h"
#include "FutureApp.h"
#include "UIHelp.h"
#include "IWindow.h"
#include "IButton.h"
#include "IDateSelector.h"
#include "ITimeSelector.h"
#include "GameUI.h"
#include "ITextEdit.h"
#include "ILabel.h"
#include "IImage.h"
#include "FileRequester.h"
#include "FUsers.h"
#include "FUserProfile.h"
#include "ISizeBox.h"
#include "FSDesktop.h"
#include "SoundLib.h"
#include "GameVideo.h"
#include "MessageBox.h"

void FSLogin::InitState() {

	if (FFile::fileExists("platform/autologin.data"))
	{

		FFile* ff = new FFile("platform/autologin.data",true);

		auto user = ff->readString();

		ff->close();

		


		m_Users = new FUsers;
		m_Users->LoadUsers();
		m_Users->SaveUsers();

		auto users = m_Users->GetUsers();
		FUserProfile* ulog = nullptr;

		for (auto u : users) {
			if (u->GetFullName() == user)
			{
				ulog = u;
				break;
			}

		}

		if (ulog == nullptr) {

		}
		auto desktop = new FSDesktop;
		desktop->SetUser((FUserProfile*)ulog);

		FutureApp::m_Inst->PushState(desktop);
		return;
	}

	m_Draw = new SmartDraw;
	m_Background = new Texture2D("platform/wallpapers/platform_defaultwp.jpg");
	auto boot = FutureApp::m_Inst->SLib->loadSound("platform/audio/boot/bootsound.wav");
	FutureApp::m_Inst->SLib->playSound(boot);
	m_BGVideo = new GameVideo("platform/video/loginBG.mp4");
	m_BGVideo->Play();
}

void FSLogin::UpdateState(float delta) {

	m_BGVideo->Update();
	m_BGAlpha += 0.45f * delta;
	if (m_BGAlpha > 1) {
		m_BGAlpha = 1.0;
		if (!m_CreatedUI) {

			m_Time = new ITimeSelector(glm::vec2(FutureApp::m_Inst->GetWidth() - 256, 16), glm::vec2(220, 30));
			m_Date = new IDateSelector(glm::vec2(FutureApp::m_Inst->GetWidth() - 386, 58), glm::vec2(350, 30));
			
			auto date = m_Date->GetDate();
//			date.
			date.day = 25;

			m_Date->SetDate(date);

			Texture2D* calendarIcon = new Texture2D("engine/ui/calendar.png");

			m_Date->SetCalendarIcon(calendarIcon);

			m_UI = new GameUI;

			m_UI->GetRoot()->AddChild(m_Time);
			m_UI->GetRoot()->AddChild(m_Date);
			
			m_NewUser = new IButton("New User", glm::vec2(32, FutureApp::m_Inst->GetHeight() - 72), glm::vec2(130, 30));

			m_NewUser->SetOnClick([&](void * data) {

				CreateNewUser();

				});

			m_UI->GetRoot()->AddChild(m_NewUser);
			
			m_CreatedUI = true;

			m_Users = new FUsers;
			m_Users->LoadUsers();
			m_Users->SaveUsers();


			auto login_lab = new ILabel("Future-Platform Login", glm::vec2(FutureApp::m_Inst->GetWidth() / 2 - UIHelp::StrWidth("Future-Platform Login") / 2, FutureApp::m_Inst->GetHeight() / 2 - 180));
			m_UsersBox = new ISizeBox(glm::vec2(FutureApp::m_Inst->GetWidth() / 2 - 200, FutureApp::m_Inst->GetHeight() / 2 - 140), glm::vec2(400, 280));

			m_UI->GetRoot()->AddChild(m_UsersBox);
			m_UI->GetRoot()->AddChild(login_lab);

			auto users = m_Users->GetUsers();

			int y = 20;

			for (auto user : users) {

				auto img = new IImage(glm::vec2(10, y), glm::vec2(96, 96));
				img->SetImage(user->GetAvatarImage());
				auto lab = new ILabel(user->GetFullName(), glm::vec2(120, y + 40));
				
				auto login = new IButton("Login", glm::vec2(255, y + 58), glm::vec2(135, 30));
				
				m_UsersBox->AddChild(img);
				m_UsersBox->AddChild(lab);
				m_UsersBox->AddChild(login);

				login->SetData(user);

				login->SetOnClick([&](void* data) {

					auto profile = (FUserProfile*)data;

					m_Login = new IWindow("Login", glm::vec2(FutureApp::m_Inst->GetWidth()/2-200,FutureApp::m_Inst->GetHeight()/2-80), glm::vec2(400,160));
					m_UI->GetRoot()->AddChild(m_Login);

					auto pass_lab = new ILabel("Password", glm::vec2(20, 60));
					auto name_lab = new ILabel("Account:"+profile->GetFullName(), glm::vec2(10, 15));
					auto pass_edit = new ITextEdit(glm::vec2(100, 50), glm::vec2(220, 30));
					auto login = new IButton("Login", glm::vec2(5, 100), glm::vec2(80, 30));

					pass_edit->SetIsPassword(true);

					pass_edit->SetOnEdit([&](std::string pass) {

						m_UserPassword = pass;

						});

					pass_edit->SetData(profile);

					pass_edit->SetOnEnter([&](void* data) {

						auto profile = (FUserProfile*)data;

						if (profile->GetPassword() != m_UserPassword)
						{
							std::cout << "Incorrect password" << std::endl;
							new MessageBox("You have entered an incorrect password. Please try-again","Login");
						}
						else {

							auto desktop = new FSDesktop;
							desktop->SetUser((FUserProfile*)data);

							FFile* lf = new FFile("platform/autologin.data");
							lf->writeString(profile->GetFullName());
							lf->close();

							FutureApp::m_Inst->PushState(desktop);

						}

						});

					m_Login->AddClientControl(name_lab);
					m_Login->AddClientControl(pass_lab);
					m_Login->AddClientControl(pass_edit);
					m_Login->AddClientControl(login);

					login->SetData(profile);



					login->SetOnClick([&](void* data) {

						auto profile = (FUserProfile*)data;

						if (profile->GetPassword() != m_UserPassword)
						{
							std::cout << "Incorrect password" << std::endl;
							new MessageBox("You have entered an incorrect password. Please try-again","Login");
						}
						else {

							FFile* lf = new FFile("platform/autologin.data");
							lf->writeString(profile->GetFullName());
							lf->close();


							auto desktop = new FSDesktop;
							desktop->SetUser((FUserProfile*)data);

							FutureApp::m_Inst->PushState(desktop);

						}

						});

					/*
				
					*/

					});

				y = y + 110;

			}

		}
	}

	if(m_UI){
		m_UI->UpdateUI(delta);
	}

}

void FSLogin::RenderState() {


	UIHelp::DrawImage(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()), m_Background, glm::vec4(1, 1, 1, m_BGAlpha));

	if (m_UI != nullptr) {
		m_UI->RenderUI();
	}

		return;
	m_Draw->Begin();


	//m_Draw->DrawDirect(, m_Background);

	m_Draw->End();

}

void FSLogin::EndState() {

}

void FSLogin::CreateNewUser() {

	m_CreateUser = new IWindow("Future-Platform - New User", glm::vec2(FutureApp::m_Inst->GetWidth()/2 - 350, FutureApp::m_Inst->GetHeight()/2 - 200), glm::vec2(700, 400));
	m_Name = new ITextEdit(glm::vec2(90, 190), glm::vec2(250, 30));
	m_Password = new ITextEdit(glm::vec2(90, 250), glm::vec2(250, 30));

	auto name_Lab = new ILabel("Username", glm::vec2(10, 200));
	auto pass_Lab = new ILabel("Password", glm::vec2(10, 260));

	m_Avatar = new IImage(glm::vec2(10, 30), glm::vec2(128, 128));
	m_Avatar->SetImage(new Texture2D("platform/avatar/none.png"));
	auto av_Lab = new ILabel("Avatar", glm::vec2(20, 8));

	m_SelectAvatar = new IButton("Select Avatar", glm::vec2(148, 35), glm::vec2(100, 30));

	m_SelectAvatar->SetOnClick([&](void * data) {

		auto path = FileRequester::OpenFile("Select Avatar");

		auto tex = new Texture2D(path);
		m_Avatar->SetImage(tex);
		m_AvatarPath = path;

		});

	m_CreateUser->AddClientControl(m_Name);
	m_CreateUser->AddClientControl(m_Password);
	m_CreateUser->AddClientControl(name_Lab);
	m_CreateUser->AddClientControl(pass_Lab);
	m_CreateUser->AddClientControl(av_Lab);
	m_CreateUser->AddClientControl(m_Avatar);
	m_CreateUser->AddClientControl(m_SelectAvatar);

	auto create = new IButton("Create User", glm::vec2(m_CreateUser->GetSize().x - 160, m_CreateUser->GetSize().y - 65), glm::vec2(140, 30));
	m_CreateUser->AddClientControl(create);

	create->SetOnClick([&](void* data) {

		FUserProfile* profile = new FUserProfile;
		profile->SetID(m_Name->GetText());
		profile->CreateUser();
		profile->SetFullName(m_Name->GetText());
		profile->SetAvatar(m_AvatarPath);
		profile->SetPassword(m_Password->GetText());
		profile->SaveUser();
	
		m_Users->AddUser(profile);

		m_Users->SaveUsers();

		m_CreateUser->Close();

		});

	
	m_UI->GetRoot()->AddChild(m_CreateUser);


}