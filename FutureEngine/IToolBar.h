#pragma once
#include "IControl.h"

class IButton;
class Texture2D;

class IToolBar :
    public IControl
{
public:

    IToolBar() {

    };
    void Update(float delta) override;
    void Render() override;
    IButton* AddButton(std::string text);
    IButton* AddButton(Texture2D* icon);
private:

    int m_NextX = 25;

};

