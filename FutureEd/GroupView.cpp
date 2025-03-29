#include "GroupView.h"
#include "TileGroup.h"
#include "UIHelp.h"
#include "GameTile.h"

void GroupView::Update(float delta) {

}

void GroupView::Render() {


	int dx = 10;
	int dy = 10;

	for (auto tile : m_Group->GetTiles())
	{

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