#include "ImageStatus.h"
using namespace std;

ImageStatus::ImageStatus()
{
	setColor(COLORFUL);
	setMediaPlayer(SIMPLE_PLAYER);
	imageName = "mypicture.jpg";
}
ImageStatus::ImageStatus(const string& textContent_ , const string& imageName) :Status(textContent_) ,imageName(imageName)
{
	setColor(COLORFUL);
	setMediaPlayer(SIMPLE_PLAYER);
}
ImageStatus::ImageStatus(ifstream& inFile) : Status(inFile)
{
	int imageNameLen;
	inFile >> imageNameLen;
	char* temp = new char[imageNameLen+1];
	inFile.read(temp, imageNameLen);
	temp[imageNameLen] = '\0';
	imageName = temp;
	delete[] temp;
}

void ImageStatus::showContent() const
{
	Status::showContent();
	string str = "start " + imageName;
	system(str.c_str());
}

void ImageStatus::save(ofstream& outFile) const
{
	Status::save(outFile);
	int imageNameLen = imageName.size();
	outFile << imageNameLen;
	outFile.write((const char*)imageName.c_str(), imageNameLen);
}
