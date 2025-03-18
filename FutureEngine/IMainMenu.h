#pragma once
#include "IControl.h"

class IMainMenu : public IControl
{
public:


	void Update(float delta) override;
	void Render() override;


};

