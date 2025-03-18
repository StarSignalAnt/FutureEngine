#pragma once
#include <string>
#include <vector>
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
	std::string GetPath() {
		return m_Path;
	}
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

	static std::vector<Texture2D*> m_Cache;

private:

	int m_Handle;
	int m_Width, m_Height, m_Channels;
	std::string m_Path;

};

