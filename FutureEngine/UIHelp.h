#pragma once
#include <glm/glm.hpp>
#include <string>

class Texture2D;

class UIHelp
{
public:

	static void InitHelp();
	static void DrawImage(glm::vec2 pos, glm::vec2 size, Texture2D* image,glm::vec4 color);
	static void DrawRect(glm::vec2 pos, glm::vec2 size, glm::vec4 color);
	static void DrawCharacter(glm::vec2 pos, glm::vec2 size, Texture2D* image, glm::vec4 color);
	static void DrawText(glm::vec2 position, std::string text,glm::vec4 color);
	static float StrWidth(std::string text);
	static float StrHeight(std::string text);
};

