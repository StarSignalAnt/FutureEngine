#include "GameMap.h"
#include "GameTile.h"
#include "GameCam.h"
#include "GameLight.h"
#include "SmartDraw.h"
#include "FutureApp.h"
#include "MathsOps.h"
#include "ShaderModule.h"
#include "DrawInfo.h"
#include "RenderTarget2D.h"
#include "Texture2D.h"

void GameMap::InitMap() {

	m_ShadowRenderer = new SmartDraw;
	m_DrawLit = new ShaderModule("engine/shader/drawLitVS.glsl", "engine/shader/drawLitFS.glsl");
	m_ShadowWrite = new ShaderModule("engine/shader/drawvs.glsl", "engine/shader/shadowwriterfs.glsl");
	
	m_TileRenderer->SetShaderModule(m_DrawLit);
	m_ShadowRenderer->SetShaderModule(m_ShadowWrite);
	m_ShadowRT = new RenderTarget2D(m_ShadowMapSize, m_ShadowMapSize);

}

void GameMap::RenderShadowMap() {

	m_ShadowRT->Bind();
	m_ShadowRT->Clear(glm::vec3(1, 1, 1));

	float totalWidth = m_TileWidth * m_Width;
	float totalHeight = m_TileHeight * m_Height;

	float xScale = m_ShadowMapSize / totalWidth;
	float yScale = m_ShadowMapSize / totalHeight;


	m_ShadowRenderer->Begin();

	for (int z = 0; z < m_Depth; z++) {
		for (int y = 0; y < m_Height; y++) {
			for (int x = 0; x < m_Width; x++) {

				float drawX = (x * m_TileWidth) * xScale;
				float drawY = (y * m_TileHeight) * yScale;

				auto tile = GetTile(x, y, z);

				if (tile != nullptr) {

					if (tile->GetCastShadows()) {

						m_ShadowRenderer->DrawDirect(glm::vec2(drawX, drawY), glm::vec2(m_TileWidth * xScale, m_TileHeight * yScale), glm::vec4(1, 1, 1, 1), tile->GetFrame(0)[0]);

					}

				}


			}
		}
	}

	m_ShadowRenderer->End();

	m_ShadowRT->Unbind();
	glClearColor(0, 0, 0, 1);

//	m_TestRender->Begin();
//	m_TestRender->DrawDirect(glm::vec2(0, FutureApp::m_Inst->GetHeight()), glm::vec2(FutureApp::m_Inst->GetWidth(),-FutureApp::m_Inst->GetHeight()), glm::vec4(1, 1, 1, 1), m_ShadowRT->GetTexture());
//	m_TestRender->End();


}

void GameMap::RenderMap(GameCam* camera)
{

	RenderShadowMap();




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
				
				auto renderPos = MathsOps::TransformCoord(glm::vec2(pX, pY),rot, camera->GetPosition().z);

				renderPos = glm::vec2(midX, midY) + 
					renderPos;	


				auto tile = GetTile(x, y, z);

				if (tile != nullptr) {
					auto info = m_TileRenderer->Draw(renderPos, glm::vec2(m_TileWidth, m_TileHeight), glm::vec4(1, 1, 1, 1), tile->GetFrame(0)[0],rot,camera->GetPosition().z);
					//RenderTile(drawX, drawY, tile);

					int sX = x * m_TileWidth;
					int sY = y * m_TileHeight;

					info->SetNormalTexture(tile->GetFrame(0)[1]);
					info->SetRealCoord(0, sX,sY);
					info->SetRealCoord(1, sX + m_TileWidth,sY);
					info->SetRealCoord(2, sX+ m_TileWidth, sY + m_TileHeight);
					info->SetRealCoord(3, sX, sY + m_TileHeight);


				}

			}

		}
	}

	for (auto light : m_Lights) {

		m_DrawLit->Bind();

		glm::vec3 lightPos = light->GetPosition();

		lightPos -= glm::vec3(camera->GetPosition().x, camera->GetPosition().y, 0);

		//

		float pX = lightPos.x - midX;
		float pY = lightPos.y - midY;

		float rot = camera->GetRotation().y;

		auto renderPos = MathsOps::TransformCoord(glm::vec2(pX, pY), rot, camera->GetPosition().z);

		lightPos = glm::vec3(midX, midY, lightPos.z) +
			glm::vec3(renderPos.x,renderPos.y,0);




		//

		m_DrawLit->SetInt("feShadowMap", 2);
		m_DrawLit->SetInt("feNormalMap", 1);
		m_DrawLit->SetVec2("feScreenSize", glm::vec2(FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight()));
		m_DrawLit->SetVec3("feLightPos", lightPos);
		m_DrawLit->SetFloat("feLightRange", light->GetRange()*camera->GetPosition().z);
		m_DrawLit->SetFloat("feCamRot", camera->GetRotation().y);
		m_DrawLit->SetFloat("feCamZoom", camera->GetPosition().z);
		m_DrawLit->SetVec2("feLightActual", glm::vec2(light->GetPosition().x, light->GetPosition().y));
		m_DrawLit->SetVec2("feMapSize", glm::vec2(m_Width * m_TileWidth, m_Height * m_TileHeight));
		m_ShadowRT->GetTexture()->Bind(2);
		m_TileRenderer->End();
		m_ShadowRT->GetTexture()->Unbind(2);


	}



}

void GameMap::AddLight(GameLight* light) {

	m_Lights.push_back(light);

}

void GameMap::FIllBlock(GameTile* tile, int x, int y, int w, int h, int z)
{
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			SetTile(i, j, z, tile);
		}
	}
}