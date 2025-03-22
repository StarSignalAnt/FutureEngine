#pragma once
#include <vector>
#include <string>
#include "BinaryFile.h"

class Texture2D;

class FUserProfile
{
public:

	FUserProfile();
	void LoadUser(std::string path);
	void SaveUser();
	void CreateUser();
	void SetFullName(std::string name);
	void SetID(std::string);
	std::string GetID();
	void SetAvatar(std::string file);
	void SetPassword(std::string password);
	std::string GetFullName();
	std::string GetPassword();
	std::string GetAvatar();
	std::string GetPath();
	Texture2D* GetAvatarImage() {
		return m_AvatarImage;
	}
private:

	std::string m_ID;
	std::string m_Path;
	std::string m_FullName;
	std::string m_AvatarID;
	std::string m_Password;
	Texture2D* m_AvatarImage;

};

