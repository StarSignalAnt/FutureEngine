#pragma once
#include <vector>
#include <string>

class GameTile;

class TileGroup
{
public:

	void SetName(std::string name) {
		m_Name = name;
	}

	std::string GetName() {
		return m_Name;
	}
	void AddTile(GameTile* tile) {
		m_Tiles.push_back(tile);
	}
	std::vector<GameTile*> GetTiles() {
		return m_Tiles;
	}

private:

	std::string m_Name;
	std::vector<GameTile*> m_Tiles;

};


