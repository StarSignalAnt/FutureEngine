#pragma once
#include "IWindow.h"

class TileView : public IWindow
{
public:
    TileView() : IWindow("Tile View", glm::vec2(30, 60), glm::vec2(400, 400))
    {

        Setup();
    }

    void Setup() override;

};

