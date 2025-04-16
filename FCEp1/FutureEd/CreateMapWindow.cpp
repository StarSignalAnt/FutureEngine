#include "CreateMapWindow.h"
#include "FutureApp.h"
#include "GameUI.h"

CreateMapWindow::CreateMapWindow() : IWindow("Create Map", glm::vec2(0, 0), glm::vec2(300, 250), true, false) {
    // Center the window on screen
    int screenWidth = FutureApp::m_Inst->GetWidth();
    int screenHeight = FutureApp::m_Inst->GetHeight();
    int x = (screenWidth - 300) / 2;
    int y = (screenHeight - 250) / 2;

    Set(glm::vec2(x, y), glm::vec2(320, 270));
    Setup();
}

void CreateMapWindow::Setup() {
    // Create labels and inputs
    m_WidthLabel = new ILabel("Width:", glm::vec2(20, 40));
    m_WidthEdit = new ITextEdit(glm::vec2(120, 40), glm::vec2(150, 25));
    m_WidthEdit->SetIsNumeric(true);
    m_WidthEdit->SetNumber(32); // Default value

    m_HeightLabel = new ILabel("Height:", glm::vec2(20, 70));
    m_HeightEdit = new ITextEdit(glm::vec2(120, 70), glm::vec2(150, 25));
    m_HeightEdit->SetIsNumeric(true);
    m_HeightEdit->SetNumber(32); // Default value

    m_DepthLabel = new ILabel("Depth:", glm::vec2(20, 100));
    m_DepthEdit = new ITextEdit(glm::vec2(120, 100), glm::vec2(150, 25));
    m_DepthEdit->SetIsNumeric(true);
    m_DepthEdit->SetNumber(1); // Default value

    m_TileWidthLabel = new ILabel("Tile Width:", glm::vec2(20, 130));
    m_TileWidthEdit = new ITextEdit(glm::vec2(120, 130), glm::vec2(150, 25));
    m_TileWidthEdit->SetIsNumeric(true);
    m_TileWidthEdit->SetNumber(32); // Default value

    m_TileHeightLabel = new ILabel("Tile Height:", glm::vec2(20, 160));
    m_TileHeightEdit = new ITextEdit(glm::vec2(120, 160), glm::vec2(150, 25));
    m_TileHeightEdit->SetIsNumeric(true);
    m_TileHeightEdit->SetNumber(32); // Default value

    // Create buttons
    m_CreateButton = new IButton("Create", glm::vec2(70, 200), glm::vec2(80, 30));
    m_CancelButton = new IButton("Cancel", glm::vec2(160, 200), glm::vec2(80, 30));

    // Add create button click handler
    m_CreateButton->SetOnClick([this](void* data) {
        int width = static_cast<int>(m_WidthEdit->GetNumber());
        int height = static_cast<int>(m_HeightEdit->GetNumber());
        int depth = static_cast<int>(m_DepthEdit->GetNumber());
        int tileWidth = static_cast<int>(m_TileWidthEdit->GetNumber());
        int tileHeight = static_cast<int>(m_TileHeightEdit->GetNumber());

        // Validate inputs
        if (width <= 0 || height <= 0 || depth <= 0 || tileWidth <= 0 || tileHeight <= 0) {
            return; // Invalid inputs
        }

        // Create the map
        GameMap* newMap = new GameMap(width, height, depth, tileWidth, tileHeight);

        // Call the callback if assigned
        if (OnMapCreated) {
            OnMapCreated(newMap);
        }

        // Close the window
        Close();
        });

    // Add cancel button click handler
    m_CancelButton->SetOnClick([this](void* data) {
        Close();
        });

    // Add controls to the client area
    AddClientControl(m_WidthLabel);
    AddClientControl(m_WidthEdit);

    AddClientControl(m_HeightLabel);
    AddClientControl(m_HeightEdit);

    AddClientControl(m_DepthLabel);
    AddClientControl(m_DepthEdit);

    AddClientControl(m_TileWidthLabel);
    AddClientControl(m_TileWidthEdit);

    AddClientControl(m_TileHeightLabel);
    AddClientControl(m_TileHeightEdit);

    AddClientControl(m_CreateButton);
    AddClientControl(m_CancelButton);
}