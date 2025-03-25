#pragma once
#include <FPApp.h>

class GameMap;
class IDocker;
class IFrameBuffer;
class GameCam;

class AppMapEditor :
    public FPApp
{
public:

    AppMapEditor();

    void InitApp() override;

    IDocker* m_Dock;
    IWindow* m_Window;
    IWindow* m_SceneGraph;
    IWindow* m_Content;
    IWindow* m_Properties;
    IWindow* m_MapView;

    IFrameBuffer* m_MapViewFB;
    GameMap* m_EditMap;
    GameCam* m_EditCam;

    bool m_DragCam = false;

};

