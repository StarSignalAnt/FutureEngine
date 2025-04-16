#include "FUserProfile.h"
#include "BinaryFile.h"
#include "Texture2D.h"

FUserProfile::FUserProfile()
{

}

void FUserProfile::LoadUser(std::string path)
{

	m_Path = path;
	FFile* f = new FFile(m_Path + "user.data",true);

	m_ID = f->readString();
	m_FullName = f->readString();
	m_Password = f->readString();
	m_AvatarID = f->readString();
	m_AvatarImage = new Texture2D(m_AvatarID);

	f->close();


}

void FUserProfile::CreateUser() {

	std::string fullPath = "platform/users/" + m_ID;
	FFile::createDirectory(fullPath);
	m_Path = fullPath + "/";
	SaveUser();


}

void FUserProfile::SaveUser() {

	FFile* f = new FFile(m_Path + "user.data");

	f->writeString(m_ID);
	f->writeString(m_FullName);
	f->writeString(m_Password);
	f->writeString(m_AvatarID);
	f->close();

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

void FUserProfile::SetPassword(std::string password) {


	m_Password = password;

}

std::string FUserProfile::GetFullName()
{
	return m_FullName;
}

std::string FUserProfile::GetPassword() {
	return m_Password;
}

std::string FUserProfile::GetAvatar() {

	return m_AvatarID;

}


std::string FUserProfile::GetPath() {

	return m_Path;

}