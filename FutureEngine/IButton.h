#pragma once
#include "IControl.h"
class IButton :
    public IControl
{
public:

	IButton() : IControl() { LoadResources(); }
	IButton(std::string text, glm::vec2 position, glm::vec2 size) : IControl(position, size) { m_Text = text; LoadResources(); }
	void Update(float delta) override;
	void Render() override;
	void OnMouseEnter() override;
	void OnMouseLeave() override;
	void OnMouseDown(int button) override;
	void OnMouseUp(int button) override;
	void LoadResources();
//	void SetImage(Texture2D* image) { m_Image = image; }
//	Texture2D* GetImage() { return m_Image; }
//	void SetText(std::string text) { Text = text; }
	//std::string GetText() { return Text; }
	//void SetClickFunction(std::function<void()> func) { m_ClickFunction = func; }



private:
};

