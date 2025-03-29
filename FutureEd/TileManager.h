#pragma once
#include <IWindow.h>

class IDock;
class ITreeView;
class TileGroup;


class TileManager :
    public IWindow
{
public:

    TileManager() : IWindow("Tile Manager", glm::vec2(30, 60), glm::vec2(400, 400))
    {

        Setup();
    }

    void Setup() override;

    void RebuildTree();

    static std::vector<TileGroup*> m_Groups;

private:
    IDocker* m_Dock;
    IWindow* m_TileTree;
    IWindow* m_TileView;
    ITreeView* m_Tree;
    

};

