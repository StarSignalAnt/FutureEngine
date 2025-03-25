#pragma once
#include <vector>
#include "SmartDraw.h"

class GameTile;
class GameCam;
class GameLight;
class GameSprite;
class ShaderModule;
class RenderTarget2D;
class Texture2D;

class GameMap
{
public:

	GameMap(int width,int height,int depth,int tileWidth,int tileHeight) : m_Width(width), m_Height(height), m_Depth(depth), m_TileWidth(tileWidth), m_TileHeight(tileHeight), m_Tiles(width*height*depth),m_Highlights(width*height) {
	 
		m_TileRenderer = new SmartDraw;
		m_TestRender = new SmartDraw;
		InitMap();

    }

	void InitMap();

	int Index(int x, int y, int z) const {
		return x + m_Width * (y + m_Height * z);
	}
    void SetTile(int x, int y, int z, GameTile* tile) {
        if (x >= 0 && x < m_Width && y >= 0 && y < m_Height && z >= 0 && z < m_Depth) {
            m_Tiles[Index(x, y, z)] = tile;
        }
    }

	void SetHighlight(int x, int y, bool hl)
	{
		m_Highlights[y * m_Width + x] = hl;

	}

	bool GetHighlight(int x, int y) {

		return m_Highlights[y * m_Width + x];

	}


    // Get a tile at (x, y, z)
    GameTile* GetTile(int x, int y, int z) const {
        if (x >= 0 && x < m_Width && y >= 0 && y < m_Height && z >= 0 && z < m_Depth) {
            return m_Tiles[Index(x, y, z)];
        }
        return nullptr; // Return default tile if out of bounds
    }

	void Fill(GameTile* tile,int z) {
		
			for (int y = 0; y < m_Height; y++) {
				for (int x = 0; x < m_Width; x++) {
					SetTile(x, y, z, tile);
				}
			}
		
	}

	void FIllBlock(GameTile* tile, int x, int y, int w, int h, int z);

	void AddLight(GameLight* light);

	void RenderMap(GameCam* camera);
	void RenderGrid(GameCam* camera);
	void RenderShadowMap();

	void AddSprite(GameSprite* sprite) {
		m_Sprites.push_back(sprite);
	}



private:

	int m_Width, m_Height, m_Depth;
	int m_TileWidth, m_TileHeight;
	std::vector<GameTile*> m_Tiles;
	std::vector < bool > m_Highlights;
	SmartDraw* m_TileRenderer;
	SmartDraw* m_TestRender;
	SmartDraw* m_ShadowRenderer;
	ShaderModule* m_DrawLit;
	ShaderModule* m_ShadowWrite;
	std::vector<GameLight*> m_Lights;
	RenderTarget2D* m_ShadowRT;
	int m_ShadowMapSize = 1024;
	std::vector<GameSprite*> m_Sprites;
	Texture2D* m_GridTex;

};

