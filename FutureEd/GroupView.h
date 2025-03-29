#pragma once
#include <IControl.h>

class TileGroup;

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

private:

    TileGroup* m_Group;

};

