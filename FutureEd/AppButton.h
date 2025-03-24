#pragma once
#include <IControl.h>

class IWindow;
class RenderTarget2D;

class AppButton :

    public IControl
{
public:

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

private:

    IWindow* m_Window;
    bool m_ShowPreview = false;
    RenderTarget2D* m_Thumbnail;

};

