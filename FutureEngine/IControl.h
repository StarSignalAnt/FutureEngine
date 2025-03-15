#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <functional>
class Texture2D;

class IControl
{
public:

	IControl() : m_Position(0, 0), m_Size(0, 0),m_Color(glm::vec4(1,1,1,1)) {}
	IControl(glm::vec2 position, glm::vec2 size) : m_Position(position), m_Size(size),m_Color(glm::vec4(1,1,1,1)) {}
	void Set(glm::vec2 position, glm::vec2 size = glm::vec2(-1, -1))
	{
		if (size.x < 0) {
			
		}
		else {
			m_Size = size;
		}
		m_Position = position;
		AfterSet();
	}
	void SetRoot(IControl* root) { m_RootControl = root; }
	IControl* GetRoot() { return m_RootControl; }
	void AddChild(IControl* child) { m_Children.push_back(child); child->SetRoot(this); }
	void RemoveChild(IControl* child) { m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end()); }
	void SetImage(Texture2D* image) { m_Image = image; }

	Texture2D* GetImage() { return m_Image; }
	void SetText(std::string text) { m_Text = text; }
	std::string GetText() { return m_Text; }
	glm::vec2 GetRenderPosition();
	std::vector<IControl*> GetChildren() { return m_Children; }

	void setScissor(int x, int y, int width, int height, int windowHeight);

	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	virtual void PreRender() {
		PreRenderChildren();
	}
	void UpdateChildren(float delta);
	void RenderChildren();
	void PreRenderChildren();
	virtual void OnMouseEnter() {};
	virtual void OnMouseLeave() {};
	virtual void OnMouseDown(int button) {};
	virtual void OnMouseUp(int button) {};
	virtual void OnMouseMove(glm::vec2 position,glm::vec2 delta) {};
	virtual void OnMouseWheel(float delta) {};
	virtual void OnKeyDown(int key) {};
	virtual void OnKeyUp(int key) {};
	virtual void OnMouseDoubleClick() {};
	virtual bool InBounds(glm::vec2 position)
	{
		glm::vec2 root = GetRenderPosition();
		
		if (m_RootControl != nullptr) {
			if (position.x < m_RootControl->GetRenderPosition().x || position.y < m_RootControl->GetRenderPosition().y)
			{
				return false;

			}
			if (position.x > m_RootControl->GetRenderPosition().x + m_RootControl->GetSize().x || position.y > m_RootControl->GetRenderPosition().y + m_RootControl->GetSize().y) {
				return false;
			}
		}
		
		if (position.x > root.x && position.x < root.x + m_Size.x &&
			position.y > root.y && position.y < root.y + m_Size.y)
		{
			return true;
		}
		return false;
	}
	void Click() {
		if (OnClick) {
			OnClick();  // Call the assigned function
		}
	}
	void DoubleClick() {
		if (OnDoubleClick) {
			OnDoubleClick();
		}	
	}
	void CallPreRender() {
		if (OnPreRender) {
			OnPreRender();
		}
	}

	void Move(glm::vec2 delta) {

		if (OnMove) {
			OnMove(delta);
		}
	}
	
	void SetOnClick(std::function<void()> callback) {
		OnClick = callback;
	}
	void SetOnDoubleClick(std::function<void()> callback)
	{
	
		OnDoubleClick = callback;
	}
	void SetOnPreRender(std::function<void()> callback) {

		OnPreRender = callback;

	}
	void SetOnMoved(std::function<void(glm::vec2)> move)
	{
		OnMove = move;

	}

	int GetMaxHeight();
	int GetMaxWidth();

	glm::vec2 GetPosition() { return m_Position; }
	glm::vec2 GetSize() { return m_Size; }
	glm::vec2 GetOffset() { return m_Offset; }
	void SetOffset(glm::vec2 offset) { m_Offset = offset; };
	void SetCullChildren(bool cull) { m_CullChildren = cull; }
	virtual void AfterSet() {};


protected:

	glm::vec2 m_Position;
	glm::vec2 m_Size;
	glm::vec2 m_Offset;
	std::vector<IControl*> m_Children;
	IControl* m_RootControl = nullptr;
	Texture2D* m_Image = nullptr;
	std::string m_Text;
	glm::vec4 m_Color;
	std::function<void()> OnClick = nullptr;
	std::function<void()> OnDoubleClick = nullptr;
	std::function<void()> OnPreRender = nullptr;
	std::function<void(glm::vec2 delta)> OnMove = nullptr;
	bool m_CullChildren = false;


};

