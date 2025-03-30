#pragma once
#include <IWindow.h>

class IDock;
class ITreeView;
class TileGroup;
class GameTile;

class TileManager :
    public IWindow
{
public:

    TileManager() : IWindow("Tile Manager", glm::vec2(30, 60), glm::vec2(750, 500))
    {

        Setup();
    }

    void Setup() override;

    void RebuildTree();
    void Save();
    void Load();
    GameTile* FindTile(std::string name);

    static std::vector<TileGroup*> m_Groups;

    static GameTile* m_SelectedTile;
    static TileManager* m_Inst;
private:
    IDocker* m_Dock;
    IWindow* m_TileTree;
    IWindow* m_TileView;
    ITreeView* m_Tree;
    

};

