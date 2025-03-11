#pragma once
#include <vector>

class Texture2D;

class GameTile
{
public:

	void AddFrame(Texture2D* colorFrame, Texture2D* normalFrame);
	std::vector<Texture2D*> GetFrame(int index);

private:

	std::vector<Texture2D*> m_ColorFrames;
	std::vector<Texture2D*> m_NormalFrames;
	
	bool m_CastShadow = false;
	bool m_ReceivesShadow = false;
	bool m_ReceivesLight = true;


};

