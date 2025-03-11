#pragma once
#include "FutureState.h"
#include <string>
#include <vector>
#include <stack>

class GLFWwindow;

class FutureApp
{
public:

	FutureApp();
	void SetApp(int width, int height, std::string app);
	int Run();
	void InitGL();
	void PushState(FutureState* state);
	void PopState();
	void SetSize(int width, int height);
	int GetWidth() { return m_Width; };
	int GetHeight() { return m_Height; };

	static FutureApp* m_Inst;

private:

	int m_Width;
	int m_Height;
	std::string m_App;
	std::stack<FutureState*> m_States;
	GLFWwindow* window;

	//fps
	int frames = 0;
	int fps = 0;

};

