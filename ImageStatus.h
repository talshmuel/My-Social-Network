#define _CRT_SECURE_NO_WARNINGS
#ifndef __IMAGESTATUS_H
#define __IMAGESTATUS_H
#include<string>
#include <iostream>
#include"status.h"

class ImageStatus :public Status
{
	std::string imageName;
public:

	ImageStatus();
	ImageStatus(const std::string& textContent_ ,const std::string& imageName);
	ImageStatus(std::ifstream& inFile);
	~ImageStatus()override = default;
	virtual void showContent() const;
	virtual void save(std::ofstream& outFile) const override;

};
#endif // __IMAGESTATUS_H

