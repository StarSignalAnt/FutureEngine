#pragma once
#include <vector>
#include <string>
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
	void SetName(std::string name) {
		m_Name = name;
	}
	std::string GetName()
	{
		return m_Name;
	}

private:

	std::vector<Texture2D*> m_ColorFrames;
	std::vector<Texture2D*> m_NormalFrames;
	
	bool m_CastShadow = false;
	bool m_ReceivesShadow = false;
	bool m_ReceivesLight = true;
	static Texture2D* m_BlankNormal; // = nullptr;
	std::string m_Name = "";
};

