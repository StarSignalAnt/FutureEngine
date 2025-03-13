#pragma once
#include "IControl.h"
class IControlGroup :
    public IControl
{
public:

	void Update(float delta) override;
	void Render() override;

};

