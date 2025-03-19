#pragma once
#include "IControl.h"
#include "IButton.h"

class IControlGroup;
class IHorizontalScroller;
class IVerticalScroller;
class IDocker;

enum WindowArea {
    AREA_TITLE, AREA_LEFT, AREA_RIGHT, AREA_BOTTOM, AREA_RESIZER, AREA_CLIENT, AREA_NONE
};

class IWindow :
    public IControl
{
public:
    IWindow(std::string title, glm::vec2 position, glm::vec2 size) : IControl(position, size) { m_Text = title; InitWindow(); }

    // Get the current active area (needed for undocking detection)
    WindowArea GetCurrentArea() const { return m_CurrentArea; }
    void InitWindow();
    void Update(float delta) override;
    void Render() override;
    void OnMouseDown(int button) override;
    void OnMouseUp(int button) override;
    void OnMouseMove(glm::vec2 position, glm::vec2 delta) override;
    void OnMouseDoubleClick() override;

    bool InBounds(glm::vec2 position) override;
    void AlignWindow();
    void AddClientControl(IControl* control);
    IControlGroup* GetClientArea() {
        return m_ClientArea;
    }

    void AfterSet() override;

    // Make dragging state accessible to friends
    friend class DockPanel;
    friend class IWindowDock;
    friend class IWindowDockHandler;
    bool m_Dragging = false;
    void SetDocked(bool dock) {
        m_Docked = dock;
    }
    void SetDock(IDocker* dock) {
        m_Dock = dock;
    }
    void DockWindow(IWindow* window);
    void SetMenu(IMainMenu* menu) { m_ActiveMenu = menu; }
    IMainMenu* GetMenu() { return m_ActiveMenu; }
    void SetAppTitle(std::string title) { m_AppTitle = title; }
    std::string GetAppTitle() {
        return m_AppTitle;
    }
private:


    IDocker* m_Dock = nullptr;
    bool m_Docked = false;
    WindowArea m_CurrentArea = AREA_NONE;
    IButton* m_CloseButton = nullptr;
    IButton* m_MaximizeButton = nullptr;
    IButton* m_Resizer = nullptr;
    IButton* m_MinimizeButton = nullptr;
    IControlGroup* m_ClientArea = nullptr;
    IVerticalScroller* m_YScroller = nullptr;
    IHorizontalScroller* m_XScroller = nullptr;
    Texture2D* m_TitleBarImage;
    //IButton* m_Resizer;
    Texture2D* m_TitleBG;
    Texture2D* m_ClientBG;
    std::vector<IWindow*> m_DockedWindows;
    glm::vec2 m_OriginalSize;
    glm::vec2 m_OriginalPosition;
    int m_CurrentTab = 0;
    glm::vec2 m_MousePos;
    IControlGroup* m_BaseArea = nullptr;
    IMainMenu* m_ActiveMenu = nullptr;
    std::string m_AppTitle = "";
};
