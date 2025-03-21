#pragma once
#include <vector>
#include <string>
#include "BinaryFile.h"

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

private:

	std::string m_ID;
	std::string m_Path;
	std::string m_FullName;
	std::string m_AvatarID;

};

