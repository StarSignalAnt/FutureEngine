#pragma once
#include "FutureState.h"
#include "Texture2D.h"
#include "SmartDraw.h"
//#include "GameMap.h"
//#include "GameTile.h"

class GameUI;
class GameMap;
class GameTile;
class GameCam;
class GameLight;
class GameSprite;
class RenderTarget2D;
class GameVideo;
class IDocker;
class IWindow;
class IVideoPlayer;

class StateTest1 :
    public FutureState
{
public:

	void InitState() override;
	void UpdateState(float delta) override;
	void RenderState() override;
	void EndState() override;

private:
	void CreateDemoWindows();
	IVideoPlayer* vp;
	std::vector<IWindow*> m_Windows;
	Texture2D* m_Tex1;
	Texture2D* m_Tex2;
	SmartDraw* m_Draw;
	float m_Ang = 0;
	bool m_Playing = true;
	GameMap* m_Map1;
	GameTile* m_Tile1, * m_Tile2;
	GameCam* m_Cam1;
	GameLight* m_Light1;
	GameLight* m_Light2;
	RenderTarget2D* m_RT1;
	GameUI* m_UI;
	GameSprite* m_Spr1;
	GameVideo* m_Vid1;
	IDocker* m_Dock;
};

