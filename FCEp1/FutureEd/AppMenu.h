#pragma once
#include <IControl.h>
#include <string>
#include <vector>

class IVerticalMenu;

struct MenuItem;



class AppMenu :
    public IControl
{
public:

    AppMenu(glm::vec2 position, glm::vec2 size);
    void Update(float delta) override;
    void Render() override;
    void AddItem(MenuItem* item);
    void OnMouseMove(glm::vec2 position, glm::vec2 delta);
    void OnMouseDown(int button) override;

private:

    std::vector<MenuItem*> m_Items;
    MenuItem* m_OverItem = nullptr;
    IVerticalMenu* m_ActiveMenu;

};

