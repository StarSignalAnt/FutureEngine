#include "IVideoPlayer.h"
#include "GameVideo.h"
#include "UIHelp.h"

IVideoPlayer::IVideoPlayer(std::string path, glm::vec2 position, glm::vec2 size) {

	m_Text = path;
	m_Position = position;
	m_Size = size;

}

IVideoPlayer::IVideoPlayer(glm::vec2 position, glm::vec2 size) {

	m_Position = position;
	m_Size = size;

}

void IVideoPlayer::Play() {

	m_Video = new GameVideo(m_Text);
	m_Video->Play();

}

void IVideoPlayer::Update(float delta) {

	m_Video->Update();

}

void IVideoPlayer::Render() {

	auto frame = m_Video->GetFrame();

	if (frame != nullptr) {
		UIHelp::DrawImage(GetRenderPosition(), m_Size, frame, m_Color);
	}

}