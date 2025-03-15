#pragma once
#include <string>
class Texture2D
{
public:

	Texture2D(std::string path);
	Texture2D(int width, int height, unsigned char* data, int channels);
	Texture2D(int handle, int w, int h)
	{
		m_Handle = handle;
		m_Width = w;
		m_Height = h;
	}
	Texture2D(int w, int h);
	void Grab(int x, int y);

	void Bind(int unit);
	void Unbind(int unit);
	int GetID() {
		return m_Handle;
	}
	void Free();
private:

	int m_Handle;
	int m_Width, m_Height, m_Channels;

};

