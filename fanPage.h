#define _CRT_SECURE_NO_WARNINGS
#ifndef __FANPAGE_H
#define __FANPAGE_H
#include <iostream>
#include<string>
#include<vector>
#include"status.h"
#include"user.h"
#include "fanPageExceptions.h"
#include "ImageStatus.h"
#include"VideoStatus.h"

class User;


class FanPage
{
	std:: string name;
	std::vector <User*> fans;
	std::vector <Status*> board;
	int fpIndex;


public:
	FanPage() = default;
	FanPage(const std::string& name, int index)noexcept(false);
	FanPage(const FanPage& other) = default;
	FanPage(std::ifstream& inFile);
	void operator+=(User& fan);
	bool operator>(const FanPage * other);
	bool operator>(const User* other);


	std:: string getName() const { return name; }
	void addStatus(Status* s);
	void showAllStatuses() const;
	void showAllFans() const;
	void removeFan(User& fToRemove); //delete user from users array
	bool IsFan(const User& u) const;
	void save(std::ofstream& inFile) const;
	int getIndex() const { return fpIndex; }
	int numOfFans() const { return fans.size(); }
};


#endif // __FANPAGE_H
