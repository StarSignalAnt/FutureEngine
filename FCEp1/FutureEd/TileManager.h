#pragma once
#include <IWindow.h>

class IDock;
class ITreeView;
class TileGroup;
class GameTile;
class GroupView;
class PropertyItem;

class TileManager :
    public IWindow
{
public:

    TileManager() : IWindow("Tile Manager", glm::vec2(30, 60), glm::vec2(750, 500),false)
    {


        Setup();
    }

    void Setup() override;

    void RebuildTree();
    void Save();
    void Load();
    GameTile* FindTile(std::string name);
    void SetPropTile(GameTile* tile);
    static std::vector<TileGroup*> m_Groups;

    static GameTile* m_SelectedTile;
    static TileManager* m_Inst;
private:
    IDocker* m_Dock;
    IWindow* m_TileTree;
    IWindow* m_TileView;
    IWindow* m_TileProps;
    ITreeView* m_Tree;
    GroupView* m_View;
    TileGroup* m_CGroup;
    PropertyItem* m_ColProp, * m_NormProp;
    

};

