#pragma once
#include <FutureState.h>

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

class StateGameIntro :
    public FutureState
{
public:

	void InitState() override;
	void UpdateState(float delta) override;
	void RenderState() override;
	void EndState() override;

private:

	GameVideo* m_IntroVideo;
};

