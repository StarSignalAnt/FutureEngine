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

void FSLogin::InitState() {

	m_Draw = new SmartDraw;
	m_Background = new Texture2D("platform/wallpapers/platform_defaultwp.jpg");

}

void FSLogin::UpdateState(float delta) {

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

			m_NewUser->SetOnClick([&]() {

				CreateNewUser();

				});

			m_UI->GetRoot()->AddChild(m_NewUser);
			
			m_CreatedUI = true;


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

	m_SelectAvatar->SetOnClick([&]() {

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

	create->SetOnClick([&]() {

		FUserProfile* profile = new FUserProfile;
		profile->SetID(m_Name->GetText());
		profile->CreateUser();
		profile->SetAvatar(m_AvatarPath);
	

		m_CreateUser->Close();

		});

	
	m_UI->GetRoot()->AddChild(m_CreateUser);


}