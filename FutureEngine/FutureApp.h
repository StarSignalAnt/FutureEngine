#pragma once
#include "FutureState.h"
#include <string>
#include <vector>
#include <stack>

class GLFWwindow;
class RenderTarget2D;
class SoundLIB;

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
	int GetWidth();
	int GetHeight();
	void SetBind(RenderTarget2D* rt);
	RenderTarget2D* GetBind() { return m_BoundRT; };
	static FutureApp* m_Inst;
	SoundLIB* SLib;
private:

	int m_Width;
	int m_Height;
	std::string m_App;
	std::stack<FutureState*> m_States;
	GLFWwindow* window;
	int UpdateInerval;
	//fps
	int frames = 0;
	int fps = 0;
	RenderTarget2D* m_BoundRT;

};

