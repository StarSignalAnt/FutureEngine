#pragma once
#include <IControl.h>

class TileGroup;
class GameTile;

class GroupView :
    public IControl
{
public:

    GroupView() : IControl(glm::vec2(0, 0), glm::vec2(0, 0)) { SetIgnoreScissor(true); };
    void Update(float delta) override;
    void Render() override;
    void SetGroup(TileGroup* group) {
        m_Group = group;
    }
    void OnMouseMove(glm::vec2 position, glm::vec2 delta) override;
    void OnMouseDown(int button) override;
    void OnMouseDoubleClick() override;


private:

    TileGroup* m_Group;
    GameTile* m_SelectedTile = nullptr;
    GameTile* m_OverTile = nullptr;

};

