#include "MapViewFB.h"
#include "GameMap.h"
#include "GameCam.h"

MapViewFB::MapViewFB() : IFrameBuffer(glm::vec2(20, 20), glm::vec2(40, 40)) {

	SetOnPreRender([&]() {

		m_Map->RenderGrid(m_Cam);


		});

}

void MapViewFB::OnMouseDown(int button) {

	if (button == 1) m_DragCam = true;

}

void MapViewFB::OnMouseUp(int button) {

	if (button == 1) m_DragCam = false;

}


void MapViewFB::OnMouseMove(glm::vec2 position, glm::vec2 delta) {

	if (m_DragCam) {
		m_Cam->MoveLocal(-delta);
	}
}


void MapViewFB::OnMouseWheel(float z) {

	m_Cam->Zoom(z * 0.1);

}