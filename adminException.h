#define _CRT_SECURE_NO_WARNINGS
#ifndef __ADMINEXCEPTIONS_H
#define __ADMINEXCEPTIONS_H
#include <iostream>
#include <string>

class adminException :public std::exception
{
public:
    const char* what() const { return "Admin Error!\n"; }
};
class nameDuplication :public adminException
{
public:
    const char* what() const { return "Error: this user name is already Exists!\n"; }
};
class invalidInput :public adminException
{
public:
    const char* what() const { return "Error: invalid choice!\n"; }
};
class selfFriendship :public adminException
{
public:
    const char* what() const { return "Error: you can't create friendship with yourself!\n"; }
};
class friendshipExists :public adminException
{
public:
    const char* what() const { return "Error: these users are already friends!\n"; }
};
class selfCancelFriendship :public adminException
{
public:
    const char* what() const { return "Error: you can't cancel friendship with yourself!\n"; }
};
class cancelFriendshipExcep :public adminException
{
public:
    const char* what() const { return "Error: these users are not friends alredy!\n"; }
};
class fanPageExist :public adminException
{
public:
    const char* what() const { return "Error: this user is already a fan of this page!\n"; }
};
class fanPageNotExist :public adminException
{
public:
    const char* what() const { return "Error: this user is not a fan of this page!\n"; }
};

class wrongMediaName :public adminException
{
public:
    const char* what() const { return "Error: this file name is not in the correct pattern!\n"; }
};




#endif //__ADMINEXCEPTIONS_H