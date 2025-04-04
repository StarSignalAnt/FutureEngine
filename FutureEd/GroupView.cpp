#include "GroupView.h"
#include "TileGroup.h"
#include "UIHelp.h"
#include "GameTile.h"
#include "TileManager.h"

void GroupView::Update(float delta) {

}

void GroupView::Render() {


	int dx = 10;
	int dy = 10;

	for (auto tile : m_Group->GetTiles())
	{


		if (tile == m_SelectedTile) {
			UIHelp::DrawRect(GetRenderPosition() + glm::vec2(dx - 2, dy - 2), glm::vec2(96, 96), glm::vec4(0, 1, 0, 1));
		}
		if (tile == m_OverTile) {
			UIHelp::DrawRect(GetRenderPosition() + glm::vec2(dx - 2, dy - 2), glm::vec2(96, 96), glm::vec4(0, 1, 1, 1));
		}
		UIHelp::DrawImage(GetRenderPosition()+glm::vec2(dx, dy), glm::vec2(92, 92), tile->GetFrame(0)[0], glm::vec4(1, 1, 1, 1));
		dx = dx + 98;
		if (dx >= (m_Size.x - 92))
		{
			dx = 10;
			dy = dy + 98;
		}


	}

	RenderChildren();

}

void GroupView::OnMouseMove(glm::vec2 position, glm::vec2 size) {

	int dx = 10;
	int dy = 10;
	m_OverTile = nullptr;

	for (auto tile : m_Group->GetTiles())
	{

		//UIHelp::DrawImage(GetRenderPosition() + glm::vec2(dx, dy), glm::vec2(92, 92), tile->GetFrame(0)[0], glm::vec4(1, 1, 1, 1));
		
		if (position.x >= dx && position.x<dx + 92 && position.y>dy && position.y < dy + 92)
		{
			m_OverTile = tile;
		}

		dx = dx + 98;

		if (dx >= (m_Size.x - 92))
		{
			dx = 10;
			dy = dy + 98;
		}


	}


}

void GroupView::OnMouseDown(int button) {

	m_SelectedTile = m_OverTile;
	TileManager::m_SelectedTile = m_OverTile;
	TileManager::m_Inst->Save();
	TileManager::m_Inst->SetPropTile(m_OverTile);

}

void GroupView::OnMouseDoubleClick() {



}