#pragma once
#include "IWindow.h"
#include "ILabel.h"
#include "ITextEdit.h"
#include "IButton.h"
#include "GameMap.h"

class CreateMapWindow : public IWindow {
public:
    CreateMapWindow();
    void Setup() override;

    std::function<void(GameMap*)> OnMapCreated;

private:
    ILabel* m_WidthLabel;
    ITextEdit* m_WidthEdit;

    ILabel* m_HeightLabel;
    ITextEdit* m_HeightEdit;

    ILabel* m_DepthLabel;
    ITextEdit* m_DepthEdit;

    ILabel* m_TileWidthLabel;
    ITextEdit* m_TileWidthEdit;

    ILabel* m_TileHeightLabel;
    ITextEdit* m_TileHeightEdit;

    IButton* m_CreateButton;
    IButton* m_CancelButton;
};