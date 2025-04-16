#include "StateLogoScreen.h"
#include <glm/glm.hpp>
#include "GameVideo.h"
#include "UIHelp.h"
#include "StateGameIntro.h"
#include "FutureApp.h"

void StateLogoScreen::InitState() {

	m_LogoVideo = new GameVideo("content/video/logo/starlogo.mp4");
	m_LogoVideo->Play();

}

void StateLogoScreen::UpdateState(float delta) {

	m_LogoVideo->Update();
	if (m_LogoVideo->IsFinished()) {
		FutureApp::m_Inst->PushState(new StateGameIntro);
	}
}

void StateLogoScreen::RenderState() {

	auto frame = m_LogoVideo->GetFrame();

	if (frame.Image != nullptr) {
		UIHelp::DrawImage(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()), frame.Image, glm::vec4(1, 1, 1, 1));
	}
}

void StateLogoScreen::EndState() {


}