#include "IControl.h"


glm::vec2 IControl::GetRenderPosition() {

	glm::vec2 root = glm::vec2(0, 0);

	if (m_RootControl != nullptr) {
		root = m_RootControl->GetRenderPosition();
	}

	return root + m_Position;

}

void IControl::UpdateChildren(float delta) {
	for (auto child : m_Children) {
		child->Update(delta);
	}
}

void IControl::RenderChildren() {
	for (auto child : m_Children) {
		child->Render();
	}
}	