#pragma once
#include <IControl.h>

class IWindow;
class RenderTarget2D;
class FPApp;

class AppButton :

    public IControl
{
public:

    AppButton() {
        SetIgnoreScissor(true);
    }
    void Update(float delta) override;
    void Render() override;
    void SetWindow(IWindow* window) {
        m_Window = window;
    }
    IWindow* GetWindow() {
        return m_Window;
    }
    void OnMouseEnter() override;
    void OnMouseLeave() override;
    void SetApp(FPApp* app) {
        m_App = app;
    }

private:

    IWindow* m_Window;
    bool m_ShowPreview = false;
    RenderTarget2D* m_Thumbnail;
    FPApp* m_App;

};

