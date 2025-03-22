#include "FUsers.h"
#include "BinaryFile.h"
#include "FUserProfile.h"

FUsers::FUsers() {



}

void FUsers::LoadUsers() {

	if (FFile::fileExists("platform/users.platform")) {

		FFile* f = new FFile("platform/users.platform", true);

		short count = f->readShort();

		for (int i = 0; i < (int)count; i++) {

			auto path = f->readString();
			//path = path + "/user.dat";
			FUserProfile* profile = new FUserProfile;
			profile->LoadUser(path);
			

			m_Users.push_back(profile);



		}

		f->close();

	}

}

void FUsers::SaveUsers() {

	FFile* f = new FFile("platform/users.platform");
	f->writeShort(m_Users.size());
	for (auto user : m_Users) {

		f->writeString(user->GetPath());

	}
	f->close();


}

void FUsers::AddUser(FUserProfile* profile) {

	m_Users.push_back(profile);

}