#include "IControlGroup.h"

void IControlGroup::Update(float delta)
{

	UpdateChildren(delta);

	for (auto control : m_Children)
	{
	//	control->Update(delta);
	}

}

void IControlGroup::Render()
{

	RenderChildren();
	//for (auto control : m_Children)
	//{
//		control->Render();
//	}
}
