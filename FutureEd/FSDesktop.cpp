#include "FSDesktop.h"
#include "FutureApp.h"
#include "SoundLib.h"

void FSDesktop::InitState() {

	auto boot = FutureApp::m_Inst->SLib->loadSound("platform/audio/boot/bootsound.wav");
	FutureApp::m_Inst->SLib->playSound(boot);

}

void FSDesktop::UpdateState(float delta) {

}

void FSDesktop::RenderState() {

}

void FSDesktop::EndState() {

}