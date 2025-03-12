#pragma once
#include <vector>
#include "SmartDraw.h"

class GameTile;
class GameCam;
class GameLight;
class ShaderModule;
class RenderTarget2D;


class GameMap
{
public:

	GameMap(int width,int height,int depth,int tileWidth,int tileHeight) : m_Width(width), m_Height(height), m_Depth(depth), m_TileWidth(tileWidth), m_TileHeight(tileHeight), m_Tiles(width*height*depth) {
	 
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
	void RenderShadowMap();
	

private:

	int m_Width, m_Height, m_Depth;
	int m_TileWidth, m_TileHeight;
	std::vector<GameTile*> m_Tiles;
	SmartDraw* m_TileRenderer;
	SmartDraw* m_TestRender;
	SmartDraw* m_ShadowRenderer;
	ShaderModule* m_DrawLit;
	ShaderModule* m_ShadowWrite;
	std::vector<GameLight*> m_Lights;
	RenderTarget2D* m_ShadowRT;
	int m_ShadowMapSize = 1024;

};

