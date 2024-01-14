#define _CRT_SECURE_NO_WARNINGS
#ifndef __USEREXCEPTIONS_H
#define __USEREXCEPTIONS_H
#include <iostream>
#include <string>


class userException :public std::exception
{
public:
    const char* what() const { return "User Error!\n"; }
};

class emptyUserName :public userException
{
public:
    const char* what() const { return "Error: you have to write a user name!\n"; }
};

class invalidBirthday :public userException
{
public:
    const char* what() const { return "Error: invalid date!\n"; }
};


#endif //__USEREXCEPTIONS_H