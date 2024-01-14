#include "VideoStatus.h"
using namespace std;

VideoStatus::VideoStatus()
{
	setColor(COLORFUL);
	setMediaPlayer(VIDEO_PLAYER);
	videoName = "myvideo.mp4";
}
VideoStatus::VideoStatus(const std::string& textContent_, const string& videoName):Status(textContent_), videoName(videoName)
{
	setColor(COLORFUL);
	setMediaPlayer(VIDEO_PLAYER);
}
VideoStatus::VideoStatus(std::ifstream& inFile):Status(inFile)
{
	int videoNameLen;
	inFile >> videoNameLen;
	char* temp = new char[videoNameLen + 1];
	inFile.read(temp, videoNameLen);
	temp[videoNameLen] = '\0';
	videoName = temp;
	delete[] temp;
}

void VideoStatus::showContent() const
{
	Status::showContent();
	string str = "start " + videoName;
	system(str.c_str());
}

void VideoStatus::save(std::ofstream& outFile) const
{
	Status::save(outFile);
	int videoNameLen = videoName.size();
	outFile<< videoNameLen;
	outFile.write((const char*)videoName.c_str(), videoNameLen);
}

