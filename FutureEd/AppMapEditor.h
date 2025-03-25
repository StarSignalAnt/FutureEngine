#pragma once
#include <FPApp.h>

class IDocker;

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

};

