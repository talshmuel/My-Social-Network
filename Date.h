#define _CRT_SECURE_NO_WARNINGS

#ifndef __DATE_H
#define __DATE_H
#include <iostream>
class Date
{
	int day, month, year;

public:
	Date() = default;
	Date(int day, int month, int year) :day(day), month(month), year(year) {}

	int getDay()const { return day; }
	int getMonth()const { return month; }
	int getYear()const { return year; }

	void setDay(int d) { day = d; }
	void setMonth(int m) { month = m; }
	void setYear(int y) { year = y; }


};

#endif // __DATE_H

