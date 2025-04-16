#pragma once
#include <vector>
#include <string>

class FUserProfile;

class FUsers
{
public:

	FUsers();
	void SaveUsers();
	void LoadUsers();
	void AddUser(FUserProfile* profile);
	std::vector<FUserProfile*> GetUsers() { return m_Users; }

private:

	std::vector<FUserProfile*> m_Users;

};

