#include "GameTile.h"
#include "Texture2D.h"

void GameTile::AddFrame(Texture2D* colorFrame, Texture2D* normalFrame)
{
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


