#include "IControl.h"


glm::vec2 IControl::GetRenderPosition() {

	glm::vec2 root = glm::vec2(0, 0);

	if (m_RootControl != nullptr) {
		root = m_RootControl->GetRenderPosition();
		root = root += m_RootControl->GetOffset();
	}

	return root + m_Position;

}

void IControl::UpdateChildren(float delta) {
	for (auto child : m_Children) {
		child->Update(delta);
	}
}

void IControl::RenderChildren() {
	auto gsize = GetSize();

	auto os = GetOffset();

	for (auto child : m_Children) {
		
		auto pos = child->GetPosition() + os;
		auto size = child->GetSize();
		
		if (m_CullChildren) {
			if (pos.x >= 0 && pos.y >= 0 && pos.x + size.x <= gsize.x+2  && pos.y + size.y < gsize.y + 2) {
				child->Render();

			}
		}
		else {
			child->Render();
		}



	}
}	

int IControl::GetMaxHeight() {

	int max_y = 0;

	for (auto control : m_Children) {

		auto controlY = control->GetPosition().y + control->GetSize().y;

		if (controlY > max_y) {
			max_y = controlY;
		}

	}

	return max_y;

}


int IControl::GetMaxWidth() {

	int max_x = 0;

	for (auto control : m_Children) {

		auto controlX = control->GetPosition().x + control->GetSize().x;

		if (controlX > max_x) {
			max_x = controlX;
		}

	}

	return max_x;

}