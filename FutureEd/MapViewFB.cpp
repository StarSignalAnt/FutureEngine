#include "MapViewFB.h"
#include "GameMap.h"
#include "GameCam.h"
#include <iostream>
#include "TileManager.h"

EditMode MapViewFB::m_EditMode = EditMode::EM_Rect;

MapViewFB::MapViewFB() : IFrameBuffer(glm::vec2(20, 20), glm::vec2(40, 40)) {

	SetOnPreRender([&]() {


		m_Map->RenderMap(m_Cam);
				m_Map->RenderGrid(m_Cam);


		});

	

}

void MapViewFB::OnMouseDown(int button) {

	if (button == 2)
	{
		m_RotCam = true;
	}
	if (button == 1) m_DragCam = true;
	if (button == 0) {

		m_Select = true;
		m_StartX = m_MousePos.x;
		m_StartY = m_MousePos.y;
		if (m_EditMode == EM_Fill) {
			auto list = m_Map->SmartFill(m_MousePos.x, m_MousePos.y, m_Cam, nullptr);
			std::cout << "LL:" << list.m_List.size() << std::endl;
			for (auto tile : list.m_List)
			{
				m_Map->SetTile(tile.m_X, tile.m_Y,0, TileManager::m_SelectedTile);
			}
		}
	}

}

void MapViewFB::OnMouseUp(int button) {

	if (button == 2) m_RotCam = false;
	if (button == 1) m_DragCam = false;
	if (button == 0) {
		m_Select = false;
		switch (m_EditMode) {
		case EM_Paste:
		{

			auto list = m_Map->SelectRect(m_StartX, m_StartY, m_MousePos.x, m_MousePos.y, 0, m_Cam);

			for (auto tile : list.m_List)
			{
				//m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
				m_Map->SetTile(tile.m_X, tile.m_Y, 0, TileManager::m_SelectedTile);

			}

		}
		break;
		case EM_Fill:

		{
			m_Map->SmartFill(m_StartX, m_StartY, m_Cam, TileManager::m_SelectedTile);
		}
			break;
		case EM_Rect:
		{
			auto list = m_Map->SelectRect(m_StartX, m_StartY, m_MousePos.x, m_MousePos.y, 0, m_Cam);

			for (auto tile : list.m_List)
			{
				//m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
				m_Map->SetTile(tile.m_X, tile.m_Y, 0, TileManager::m_SelectedTile);

			}
		}
		break;
		case EM_Line:
		{
			auto list = m_Map->SelectLine(m_StartX, m_StartY, m_MousePos.x, m_MousePos.y, 0, m_Cam);

			for (auto tile : list.m_List)
			{
				//m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
				m_Map->SetTile(tile.m_X, tile.m_Y, 0, TileManager::m_SelectedTile);

			}
		}
			break;
		case EM_RectFill:
		{
			auto list = m_Map->SelectRectFilled(m_StartX, m_StartY, m_MousePos.x, m_MousePos.y, 0, m_Cam);

			for (auto tile : list.m_List)
			{
				//m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
				m_Map->SetTile(tile.m_X, tile.m_Y, 0, TileManager::m_SelectedTile);

			}
		}
		break;
		}
	}
}


void MapViewFB::OnMouseMove(glm::vec2 position, glm::vec2 delta) {
	m_Map->ClearHighlights();
	m_MousePos = position;
	if (m_Select) {

		switch (m_EditMode) {
		case EM_Paste:
		{



		}
		break;
		case EM_Rect:
		{
			auto list = m_Map->SelectRect(m_StartX, m_StartY, position.x, position.y, 0, m_Cam);
		
			for (auto tile : list.m_List)
			{
				m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
			}
		}
			break;
		case EM_Line:
		{
			auto list = m_Map->SelectLine(m_StartX, m_StartY, position.x, position.y, 0, m_Cam);

			for (auto tile : list.m_List)
			{
				m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
			}
		}
			break;
		case EM_RectFill:
		{
			auto list = m_Map->SelectRectFilled(m_StartX, m_StartY, position.x, position.y, 0, m_Cam);

			for (auto tile : list.m_List)
			{
				m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
			}
		}
			break;
		}
	}
	else {

		if (m_EditMode == EM_Fill) {

			auto list = m_Map->SmartFill(m_MousePos.x, m_MousePos.y, m_Cam, nullptr);
			std::cout << "LL:" << list.m_List.size() << std::endl;
			for (auto tile : list.m_List)
			{
				m_Map->SetHighlight(tile.m_X, tile.m_Y, true);
			}

		}

	}

	if (m_DragCam) {
		m_Cam->MoveLocal(-delta);
	}
	if (m_RotCam) {
	
		m_Cam->Turn(glm::vec3(0, delta.x, 0));
	}
	auto sel = m_Map->SelectPoint(m_Cam, position.x, position.y);
	if (sel.m_List.size() > 0) {
		//if (sel.m_List[0]) {
			m_Map->SetHighlight(sel.m_List[0].m_X, sel.m_List[0].m_Y,true);
		//}

	}

}


void MapViewFB::OnMouseWheel(float z) {

	m_Cam->Zoom(z * 0.1);

}