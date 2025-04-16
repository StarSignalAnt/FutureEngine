#pragma once
#include <IControl.h>
#include <glm/glm.hpp>

class Texture2D;
class AppMenu;

class AppStart :
    public IControl
{
public:

    AppStart(glm::vec2 position, glm::vec2 size);
    void Update(float delta) override;
    void Render() override;
    void OnMouseEnter() override;
    void OnMouseLeave() override;
    void OnMouseDown(int button) override;

private:

    Texture2D* m_AppStartImage;
    AppMenu* m_Menu = nullptr;

};

