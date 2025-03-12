#pragma once
#include <vector>

class Texture2D;

class GameTile
{
public:

	GameTile();
	void AddFrame(Texture2D* colorFrame, Texture2D* normalFrame);
	std::vector<Texture2D*> GetFrame(int index);
	void Set(bool castShadows, bool recievesShadows, bool recievesLight)
	{
		m_CastShadow = castShadows;
		m_ReceivesShadow = recievesShadows;
		m_ReceivesLight = recievesLight;
	}
	bool GetCastShadows() { return m_CastShadow; }
	bool GetReceivesShadows() { return m_ReceivesShadow; }
	bool GetReceivesLight() { return m_ReceivesLight; }


private:

	std::vector<Texture2D*> m_ColorFrames;
	std::vector<Texture2D*> m_NormalFrames;
	
	bool m_CastShadow = false;
	bool m_ReceivesShadow = false;
	bool m_ReceivesLight = true;
	static Texture2D* m_BlankNormal; // = nullptr;

};

