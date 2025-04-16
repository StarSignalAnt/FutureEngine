#pragma once
#include "FPApp.h"
#include <vector>
#include <string>

class FPApps
{
public:

	void RegisterApp(FPApp* app) {
		m_Apps.push_back(app);
	}


private:

	std::vector<FPApp*> m_Apps;

};

