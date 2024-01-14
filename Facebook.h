#define _CRT_SECURE_NO_WARNINGS
#ifndef __FACEBOOK_H
#define __FACEBOOK_H

#include "Admin.h"
#include <list>
#include <iostream>
#include <string>
#include "userExceptions.h"
#include "adminException.h"
#include"fanPageExceptions.h"
#include"statusExeption.h"

static int MAX_NAME_LEN = 30;
static int BDAY_LEN = 11;
static int MAX_STATUS_LEN = 256;

class Admin;

class Facebook
{
	Admin a;

public:

	Facebook() {}
	Facebook(const Facebook& other) = delete;
	~Facebook() {}

	enum eChoice { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN };

	int showMenuAndGetChoice()const;
	void makeAction(int i);//gets the users choice from the menu and call the relevant function
	void readUser(); // get from the user details of new user on facebook.
	void readFanPage(); // get from the user details of new page on facebook.
	void showAllStatusOfUser() const;
	void showAllStatusOfPage() const;
	int getUserIndexForActions() const;//מבקשת מהמשתמש שם של יוזר
	int getPageIndexForActions() const;//מבקשת מהמשתמש שם של דף
	void readStatusToUser();//מבקשת מהמשתמש שם משתמש וסטטוס להוספה
	void readStatusToPage();//מבקשת מהמשתמש שם דף וסטטוס להוספה
	void show10RecentStatusOfAllUserFriends() ;
	void createFriendShip();
	void cancelFriendship();
	void addFanToPage();
	void removeFanFromPage();
	void showAllObjectsInFacebook() const; //print all users and fan pages
	void ShowAllFriendsOfUser() const;
	void ShowAllFansOfPage() const;
	int statusTypeChoice(std::string& mediaFileName)noexcept(false);
	void restoration(std::ifstream& inFile) { a.restorationData(inFile); }
	bool isFileEmpty(std::ifstream& inFile)const;
	void createBuiltInObjects();
	void save(std::ofstream& outFile)const;
	bool checkImageName(const std::string& name) const;
	bool checkVideoName(const std::string& name) const;


};

#endif // __FACEBOOK_H

