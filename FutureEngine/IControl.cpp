#include "IControl.h"
#include <glad/glad.h>
#include "FutureApp.h"
#include "IWindow.h"
#include "GameUI.h"
#include "UIHelp.h"

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

void IControl::PreRenderChildren() {

	for (auto child : m_Children) {

		child->PreRender();

	}

}

void IControl::RenderChildren() {
	auto gsize = GetSize();

	auto os = GetOffset();

	auto rpos = GetRenderPosition();

	float sh = FutureApp::m_Inst->GetHeight();

	//glViewport(rpos.x, rpos.y, gsize.x, gsize.y);
	//glScissor(rpos.x, sh-rpos.y, gsize.x, -gsize.y);



	for (auto child : m_Children) {
		
		auto pos = child->GetPosition() + os;
		auto size = child->GetSize();
		
	//	if (m_CullChildren) {
			if (pos.x >= 0 && pos.y >= 0 && pos.x + size.x <= gsize.x+2  && pos.y + size.y < gsize.y + 2) {
			//	child->Render();

			}
	//	}
	//	else {
			if (m_CullChildren) {
				setScissor(rpos.x, rpos.y, gsize.x, gsize.y, sh);
				glEnable(GL_SCISSOR_TEST);
			}
			if (child == GameUI::m_Inst->GetActiveControl())
			{
				UIHelp::DrawOutlineRect(child->GetRenderPosition() + glm::vec2(-1, -1), child->GetSize() + glm::vec2(2, 2), glm::vec4(1, 1, 1, 1));
			}
			child->Render();
	//	}
			glDisable(GL_SCISSOR_TEST);


	}
	

	//glViewport(0, 0, FutureApp::m_Inst->GetWidth(), FutureApp::m_Inst->GetHeight());

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

void IControl::setScissor(int x, int y, int width, int height, int windowHeight) {
	// Convert from left-top (0,0) to OpenGL's left-bottom (0,0)
	// by flipping the Y coordinate
	int openglY = windowHeight - (y + height);

	// Set the scissor test
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, openglY, width, height);
}

bool IControl::IsWindow() {

	auto current = this;

	while (current != nullptr) {

		auto window = dynamic_cast<IWindow*>(current);
		if (window != nullptr) return true;

		current = current->GetRoot();

	}

	return false;

}

IWindow* IControl::GetWindow() {

	auto current = this;

	while (current != nullptr) {

		auto window = dynamic_cast<IWindow*>(current);
		if (window != nullptr) return window;

		current = current->GetRoot();

	}

	return nullptr;

}