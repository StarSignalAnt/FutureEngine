#pragma once
#include <string>
class Texture2D
{
public:

	Texture2D(std::string path);
	void Bind(int unit);
	void Unbind(int unit);

private:

	int m_Handle;
	int m_Width, m_Height, m_Channels;

};

