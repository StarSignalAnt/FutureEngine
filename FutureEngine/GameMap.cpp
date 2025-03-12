#include "GameMap.h"
#include "GameTile.h"
#include "GameCam.h"
#include "SmartDraw.h"
#include "FutureApp.h"
#include "MathsOps.h"

void GameMap::RenderMap(GameCam* camera)
{

	float midX = FutureApp::m_Inst->GetWidth() / 2.0f;
	float midY = FutureApp::m_Inst->GetHeight() / 2.0f;

	m_TileRenderer->Begin();
	for (int z = 0; z < m_Depth; z++) {
		for (int y = 0; y < m_Height; y++) {

			for (int x = 0; x < m_Width; x++)
			{

				float drawX = x * m_TileWidth + m_TileWidth / 2;
				float drawY = y * m_TileHeight + m_TileHeight / 2;

				drawX -= camera->GetPosition().x;

				drawY -= camera->GetPosition().y;


				float pX = drawX - midX;
				float pY = drawY - midY;

				float rot = camera->GetRotation().y;
				
				auto renderPos = MathsOps::TransformCoord(glm::vec2(pX, pY),rot, 1.0f);

				renderPos = glm::vec2(midX, midY) + 
					renderPos;	


				auto tile = GetTile(x, y, z);

				if (tile != nullptr) {
					m_TileRenderer->Draw(renderPos, glm::vec2(m_TileWidth, m_TileHeight), glm::vec4(1, 1, 1, 1), tile->GetFrame(0)[0],rot);
					//RenderTile(drawX, drawY, tile);
				}

			}

		}
	}
	m_TileRenderer->End();



}

void GameMap::FIllBlock(GameTile* tile, int x, int y, int w, int h, int z)
{
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			SetTile(i, j, z, tile);
		}
	}
}