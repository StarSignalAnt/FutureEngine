#include "MapViewFB.h"
#include "GameMap.h"
#include "GameLight.h"
#include "GameCam.h"
#include <iostream>
#include "TileManager.h"
#include "Texture2D.h"
#include "UIHelp.h"
#include "AppMapEditor.h"
EditMode MapViewFB::m_EditMode = EditMode::EM_Rect;

MapViewFB::MapViewFB() : IFrameBuffer(glm::vec2(20, 20), glm::vec2(40, 40)) {

	m_LightIcon = new Texture2D("apps/mapeditor/light.png");
	m_LeftRight = new Texture2D("apps/mapeditor/right.png");
	m_UpDown = new Texture2D("apps/mapeditor/down.png");

	SetOnPreRender([&]() {

		m_Map->RenderShadowMap();
		Bind();
		m_Map->RenderMap(m_Cam);
	//	UIHelp::ClearZ();

		m_Map->RenderGizmos(m_Cam);

		if (m_Selected) {

			glm::vec2 pos = m_Map->MapPosition(m_Cam,glm::vec2(m_Selected->GetPosition().x, m_Selected->GetPosition().y));
			UIHelp::Begin();
			UIHelp::DrawImage(pos+glm::vec2(-32,-64-32), glm::vec2(64, 64), m_UpDown, glm::vec4(1, 1, 1, 1));
			UIHelp::DrawImage(pos + glm::vec2(32,-32), glm::vec2(64, 64), m_LeftRight, glm::vec4(1, 1, 1, 1));
			UIHelp::End();

			//m_Map->RenderAligned(m_Cam, m_LeftRight, glm::vec2(m_Selected->GetPosition().x+64, m_Selected->GetPosition().y), glm::vec2(64, 64),true);
			//_Map->RenderAligned(m_Cam, m_UpDown, glm::vec2(m_Selected->GetPosition().x, m_Selected->GetPosition().y-64), glm::vec2(64, 64),true);

		}

		auto lights = m_Map->GetLights();
		//for (auto l : lights) {


			//m_Map->RenderGizmos(m_Cam, m_LightIcon, glm::vec2(l->GetPosition().x, l->GetPosition().y), glm::vec2(64, 64));

		//}

		Unbind();



		});

	

}

void MapViewFB::OnMouseDown(int button) {

	if (button == 2)
	{
		m_RotCam = true;
		return;
	}
	if (button == 1) m_DragCam = true;
	if (button == 0) {

		

		if (m_Selected != nullptr) {
			Bind();
			glm::vec2 pos = m_Map->MapPosition(m_Cam, glm::vec2(m_Selected->GetPosition().x, m_Selected->GetPosition().y));
			Unbind();

			if (IsWithin(pos + glm::vec2(-32, -64 - 32), glm::vec2(64, 64), m_MousePos)) {
			//	exit(1);
				m_MoveUp = true;
				return;

			}
			if (IsWithin(pos + glm::vec2(32, -32), glm::vec2(64, 64), m_MousePos)) {
			//	exit(1)
				m_MoveRight = true;
				return;
			}
			if (IsWithin(pos + glm::vec2(-32, -32), glm::vec2(64, 64), m_MousePos))
			{
				m_MoveBoth = true;
				return;
			}

		}

		m_Selected = nullptr;


		auto over = m_Map->MouseOver(m_Cam, glm::vec2(m_MousePos.x, m_MousePos.y));

		if (over != nullptr) {
			//exit(0);
			m_Selected = over;
			AppMapEditor::Select(over);
			return;

		}

		auto lights = m_Map->GetLights();
		for (auto l : lights) {

			

		}

		m_Select = true;
		m_StartX = m_MousePos.x;
		m_StartY = m_MousePos.y;
		if (m_EditMode == EM_Erase) {
			auto l = m_Map->SelectPoint(m_Cam, m_StartX, m_StartY);
			if (l.m_List.size() > 0) {

				m_Map->SetTile(l.m_List[0].m_X, l.m_List[0].m_Y, 0, nullptr);

			}
		}
		if (m_EditMode == EM_Paste)
		{

			auto l = m_Map->SelectPoint(m_Cam, m_StartX, m_StartY);
			if (l.m_List.size() > 0) {

				m_Map->SetTile(l.m_List[0].m_X, l.m_List[0].m_Y, 0, TileManager::m_SelectedTile);

			}

		}
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
		m_MoveRight = false;
		m_MoveUp = false;
		m_MoveBoth = false;
		switch (m_EditMode) {
		case EM_Paste:
		{

		
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
	//m_Map->RenderShadowMap();
	m_MousePos = position;
	if (m_Selected) {

		if (m_MoveRight && delta.x!=0) {
			delta.y = 0;
			m_Selected->Move(m_Cam->Transform(delta));
			AppMapEditor::m_Inst->UpdateObj();
			return;
		}
		if (m_MoveUp) {
			delta.x = 0;
			m_Selected->Move(m_Cam->Transform(delta));
			AppMapEditor::m_Inst->UpdateObj();
			return;
		}
		if (m_MoveBoth) {

			m_Selected->Move(m_Cam->Transform(delta));
			AppMapEditor::m_Inst->UpdateObj();
			return;
		}

	}


	if (m_Select) {

		switch (m_EditMode) {
		case EM_Paste:
		{

			if (m_EditMode == EM_Paste)
			{

				auto l = m_Map->SelectPoint(m_Cam, m_MousePos.x, m_MousePos.y);
				if (l.m_List.size() > 0) {

					m_Map->SetTile(l.m_List[0].m_X, l.m_List[0].m_Y, 0, TileManager::m_SelectedTile);

				}

			}

		}
		break;
		case EM_Erase:
		{
			auto l = m_Map->SelectPoint(m_Cam, m_MousePos.x, m_MousePos.y);
			if (l.m_List.size() > 0) {

				m_Map->SetTile(l.m_List[0].m_X, l.m_List[0].m_Y, 0, nullptr);

			}

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