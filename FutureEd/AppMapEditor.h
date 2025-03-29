#pragma once
#include <FPApp.h>

class GameMap;
class IDocker;
class IFrameBuffer;
class MapViewFB;
class GameCam;
class ContentBrowser;

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

    ContentBrowser* m_ContentBrowser = nullptr;

    MapViewFB* m_MapViewFB;
    GameMap* m_EditMap;
    GameCam* m_EditCam;

    bool m_DragCam = false;

};

