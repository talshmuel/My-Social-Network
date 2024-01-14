#define _CRT_SECURE_NO_WARNINGS
#ifndef __FANPAGEEXCEPTIONS_H
#define __FANPAGEEXCEPTIONS_H
#include <iostream>
#include <string>


class fanPageExceptions :public std::exception
{
public:
    const char* what() const { return "FanPage Error!\n"; }
};

class emptyPageName :public fanPageExceptions
{
public:
    const char* what() const { return "Error: you have to write a page name!\n"; }
};

class pageNameDuplication :public fanPageExceptions
{
public:
    const char* what() const { return "Error: this page name is already Exists!\n"; }
};


#endif //__FANPAGEEXCEPTIONS_H