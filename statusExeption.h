#define _CRT_SECURE_NO_WARNINGS
#ifndef __STATUSEXCEPTION_H
#define __STATUSEXCEPTION_H
#include <iostream>
#include <string>


class statusException :public std::exception
{
public:
    const char* what() const { return "Stautus Error!\n"; }
};
class emptyStatus :public statusException
{
public:
    const char* what() const { return "Error: you have to write a status!\n"; }
};





#endif//__STATUSEXCEPTION_H