#pragma once
#include "FutureState.h"
#include "Texture2D.h"
#include "SmartDraw.h"
//#include "GameMap.h"
//#include "GameTile.h"

class GameMap;
class GameTile;
class GameCam;
class GameLight;
class GameSprite;
class RenderTarget2D;


class StateTest1 :
    public FutureState
{
public:

	void InitState() override;
	void UpdateState(float delta) override;
	void RenderState() override;
	void EndState() override;

private:

	Texture2D* m_Tex1;
	Texture2D* m_Tex2;
	SmartDraw* m_Draw;
	float m_Ang = 0;
	GameMap* m_Map1;
	GameTile* m_Tile1, * m_Tile2;
	GameCam* m_Cam1;
	GameLight* m_Light1;
	GameLight* m_Light2;
	RenderTarget2D* m_RT1;
	GameSprite* m_Spr1;
};

