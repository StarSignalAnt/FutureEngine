#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

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
	}
	void SetRoot(IControl* root) { m_RootControl = root; }
	IControl* GetRoot() { return m_RootControl; }
	void AddChild(IControl* child) { m_Children.push_back(child); child->SetRoot(this); }
	void SetImage(Texture2D* image) { m_Image = image; }
	Texture2D* GetImage() { return m_Image; }
	void SetText(std::string text) { m_Text = text; }
	std::string GetText() { return m_Text; }
	glm::vec2 GetRenderPosition();
	std::vector<IControl*> GetChildren() { return m_Children; }


	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	void UpdateChildren(float delta);
	void RenderChildren();
	virtual void OnMouseEnter() {};
	virtual void OnMouseLeave() {};
	virtual void OnMouseDown(int button) {};
	virtual void OnMouseUp(int button) {};
	virtual void OnMouseMove(glm::vec2 position) {};
	virtual void OnMouseWheel(float delta) {};
	virtual void OnKeyDown(int key) {};
	virtual void OnKeyUp(int key) {};
	bool InBounds(glm::vec2 position)
	{
		glm::vec2 root = GetRenderPosition();
		if (position.x > root.x && position.x < root.x + m_Size.x &&
			position.y > root.y && position.y < root.y + m_Size.y)
		{
			return true;
		}
		return false;
	}

protected:

	glm::vec2 m_Position;
	glm::vec2 m_Size;
	std::vector<IControl*> m_Children;
	IControl* m_RootControl = nullptr;
	Texture2D* m_Image = nullptr;
	std::string m_Text;
	glm::vec4 m_Color;
	

};

