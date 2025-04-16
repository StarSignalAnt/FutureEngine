#pragma once
#include <FPApp.h>

class GameMap;
class IDocker;
class IFrameBuffer;
class MapViewFB;
class GameCam;
class ContentBrowser;
class GameObj;
class PropertyItem;

class AppMapEditor :
    public FPApp
{
public:

    AppMapEditor();

    void InitApp() override;
    void SetObject(GameObj* obj);
    void UpdateObj();

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
    GameObj* m_SelectedObj = nullptr;

    bool m_DragCam = false;

    static void Select(GameObj* obj);
    static AppMapEditor* m_Inst;
    PropertyItem* m_Pos;
    PropertyItem* m_Diff;
    PropertyItem* m_Range;

};

