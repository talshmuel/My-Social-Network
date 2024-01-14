#define _CRT_SECURE_NO_WARNINGS
#ifndef __VIDEOSTATUS_H
#define __VIDEOSTATUS_H
#include<string>
#include <iostream>
#include"status.h"

class VideoStatus:public Status
{
	std::string videoName;
public:

	VideoStatus();
	VideoStatus(const std::string& textContent_,const std::string& videoName);
	VideoStatus(std::ifstream& inFile);
	~VideoStatus()override = default;

	virtual void showContent() const;
	virtual void save(std::ofstream& outFile) const override;

};

#endif // __VIDEOSTATUS_H

