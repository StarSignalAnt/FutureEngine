#include "StateGameIntro.h"
#include <glm/glm.hpp>
#include "GameVideo.h"
#include "UIHelp.h"
#include "FutureApp.h"

void StateGameIntro::InitState() {

	m_IntroVideo = new GameVideo("content/video/intro/futureCalling.mp4");
	m_IntroVideo->Play();

}

void StateGameIntro::UpdateState(float delta) {

	m_IntroVideo->Update();
	if (m_IntroVideo->IsFinished()) {

	}
}

void StateGameIntro::RenderState() {

	auto frame = m_IntroVideo->GetFrame();

	if (frame.Image != nullptr) {
		UIHelp::DrawImage(glm::vec2(0, 0), glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()), m_IntroVideo->GetFrame().Image, glm::vec4(1, 1, 1, 1));
	}
}

void StateGameIntro::EndState() {


}