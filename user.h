#define _CRT_SECURE_NO_WARNINGS

#ifndef __USER_H
#define __USER_H
#include <iostream>
#include <vector>
#include <string>
#include"status.h"
#include"fanPage.h"
#include "userExceptions.h"
#include"Date.h"
#include "ImageStatus.h"
#include"VideoStatus.h"

class FanPage;
static int TEN = 10;
static int ONE = 1;
static int MONTH_NUM = 12;
static int DAY_IN_MONTH = 31;
static int MAX_YEAR = 2023;
static int MIN_YEAR = 1900;

class User
{
	std::string name;
	Date birthday;
	std::vector <Status*> board;
	std::vector <User*> friends;
	std::vector <FanPage*> pages;
	int uIndex;

	bool isValidBDay()const;


public:
	User() = default;
	User(const std::string& name, const Date& birthday, int index) noexcept(false);
	User(const User& other) = default;
	User(std::ifstream& inFile);

	void operator+=(User& other);
	void operator+=(FanPage& page);
	bool operator>(User* other);
	bool operator>(FanPage* other);

	
	void showPages() const;//print all fan pages of user
	void addStatus(Status* s); //add status to board of user
	void showAllStatuses() const;
	void show10RecentStatus() const;
	void show10RecentStatusOfAllFriends() const;

	std::string getName() const { return name; };
	std::string getBDay() const;
	void showFriends() const; // print names and birthdays of all friends of user.
	void removeFriend(User* fToRemove); //delete wanted user from friends array
	void removePage(FanPage& pToRemove);//delete wanted fan page from pages array
	bool userIsFriend(const User& u) const;
	void save(std::ofstream& outFile) const;
	int numOfFriends() const { return friends.size(); }
	int getFriendIndex(int arrIndx) const { return friends[arrIndx]->uIndex; }
	int numOfPages() const { return pages.size(); }
	int getPageIndex(int arrIndx) const;
};




#endif // __USER_H