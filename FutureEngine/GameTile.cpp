#include "GameTile.h"
#include "Texture2D.h"

Texture2D* GameTile::m_BlankNormal = nullptr;

GameTile::GameTile() {

	if (m_BlankNormal == nullptr) {
		
		m_BlankNormal = new Texture2D("engine/maps/blanknormal.png");
	}

}

void GameTile::AddFrame(Texture2D* colorFrame, Texture2D* normalFrame)
{
	if (normalFrame == nullptr) {
		normalFrame = m_BlankNormal;
	}
	m_ColorFrames.push_back(colorFrame);
	m_NormalFrames.push_back(normalFrame);
}

std::vector<Texture2D*> GameTile::GetFrame(int index)
{
	std::vector<Texture2D*> frames;
	frames.push_back(m_ColorFrames[index]);
	frames.push_back(m_NormalFrames[index]);
	return frames;
}


