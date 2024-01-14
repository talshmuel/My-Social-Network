#define _CRT_SECURE_NO_WARNINGS
#ifndef __STATUS_H
#define __STATUS_H
#include<string>
#include <iostream>
#include <ctime>
#include <fstream>
#include "statusExeption.h"


class Status
{
public:
	enum eColor { BLACK_WHITE, COLORFUL };
	enum ePlayer { SIMPLE_PLAYER, VIDEO_PLAYER };

private:
	std::string textContent;
	std::string statTm;
	eColor color;
	ePlayer mediaPlayer;

public:
	Status();
	Status(const std::string& textContent_)  noexcept(false);
	Status(std::ifstream& inFile);
	virtual ~Status() = default;

	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;

	virtual void showContent() const;
	int getColor();
	int getMediaPlayer();
	void setColor(const eColor color);
	void setMediaPlayer(const ePlayer mediaPlayer);
	virtual void save(std::ofstream& outFile) const;


};



#endif // __STATUS_H