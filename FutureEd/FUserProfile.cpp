#include "FUserProfile.h"
#include "BinaryFile.h"

FUserProfile::FUserProfile()
{

}

void FUserProfile::LoadUser(std::string path)
{

	m_Path = path;

}

void FUserProfile::CreateUser() {

	std::string fullPath = "platform/users/" + m_ID;
	FFile::createDirectory(fullPath);
	m_Path = fullPath + "/";


}

void FUserProfile::SaveUser() {



}

void FUserProfile::SetID(std::string id) {

	m_ID = id;

}

std::string FUserProfile::GetID() {

	return m_ID;

}

void FUserProfile::SetFullName(std::string name) {

	m_FullName = name;

}

void FUserProfile::SetAvatar(std::string id) {

	m_AvatarID = id;
	FFile::copyFile(id, m_Path + "avatar" + FFile::getFileExtension(id));

}