#include "ILabel.h"
#include "UIHelp.h"

void ILabel::Update(float delta) {

}

void ILabel::Render() {

	UIHelp::DrawText(GetRenderPosition(), m_Text, glm::vec4(1, 1, 1, 1), 1.2f);

}