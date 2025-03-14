#pragma once
#include "IControl.h"
#include "IButton.h"

enum WindowArea {

	AREA_TITLE,AREA_LEFT,AREA_RIGHT,AREA_BOTTOM,AREA_RESIZER,AREA_CLIENT,AREA_NONE

};

class IWindow :
    public IControl
{
public:

	IWindow(std::string title, glm::vec2 position, glm::vec2 size) : IControl(position, size) { m_Text = title; InitWindow(); }

	void InitWindow();
	void Update(float delta) override;
	void Render() override;
	void OnMouseDown(int button) override;
	void OnMouseUp(int button) override;
	void OnMouseMove(glm::vec2 position, glm::vec2 delta) override;
	void OnMouseDoubleClick() override;

	bool InBounds(glm::vec2 position) override;
	void AlignWindow();
private:


	bool m_Dragging = false;
	WindowArea m_CurrentArea = AREA_NONE;
	IButton* m_CloseButton;
	IButton* m_MaximizeButton;
	IButton* m_MinimizeButton;
	//IButton* m_Resizer;
	glm::vec2 m_OriginalSize;
	glm::vec2 m_OriginalPosition;

};

