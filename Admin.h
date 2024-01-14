#define _CRT_SECURE_NO_WARNINGS
#ifndef __ADMIN_H
#define __ADMIN_H
#include "User.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include"status.h"
#include"fanPage.h"
#include"user.h"
#include"adminException.h"
#include"fanPageExceptions.h"
#include"ImageStatus.h"
#include"VideoStatus.h"
class User;
class FanPage;

//Admin gets the information of all objects on facebook and implement the relevant actions.

class Admin
{
	
	std::list <FanPage> pages;
	std::list <User> users;

	
	bool isUserNameExist(const std::string& name)const;
	bool isPageNameExist(const std::string& name)const;
	void isFriendshipValid(const User& u1, const User& u2) const noexcept(false);
	void isCancelFriendshipValid(const User& u1, const User& u2) const noexcept(false);


	
public:
	Admin() {}
	Admin(const Admin& other) = delete;
	
	void restorationData(std::ifstream& inFile);
    User* createUser(const std::string& name, const Date& bday)  noexcept(false);
	FanPage* createFanPage(const std::string& name) noexcept(false);
	void addStatusToUser(const std::string& textContent, User& addTo , int statusType, const std::string& mediaName) noexcept(false);
	void addStatusToPage(const std::string textContent, FanPage& addTo, int statusType, const std::string& mediaName) noexcept(false);
	void showUserStatus(const User& u) const;
	void showPageStatus(const FanPage& p) const;
	void show10RecentStatusOfAllUserFriends(const User& u)const;
	void createFriendship(User& u1, User& u2);
	void cancelFriendship(User& u1, User& u2);
	void addFanToPage(User& u, FanPage& fp) noexcept(false);
	void deleteFanFromPage(User& u, FanPage& p);
	void showAllUsers() const;
	void showAllPages() const;
	void showUserFriends(const User& u)const;
	void showPageFans(const FanPage& fp) const;
	const User& getUserInIndex(int index)const;
	User& getUserInIndex(int index);
	const FanPage& getPageInIndex(int index) const;
	FanPage& getPageInIndex(int index);
	void validUserChoice(int index) const noexcept(false);
	void validPageChoice(int index) const noexcept(false);
	void save(std::ofstream& outFile)const;
	void createBuiltInObjects();
};



#endif // __ADMIN_H



