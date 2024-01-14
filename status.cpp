#include"status.h"
using namespace std;

Status::Status()
{
	color =BLACK_WHITE;
	mediaPlayer = SIMPLE_PLAYER;
}

Status:: Status(const string& textContent_)  noexcept(false) : textContent(textContent_)
{
	if (textContent_ == "")
		throw emptyStatus();
	time_t currTime = time(NULL);
	statTm =ctime(&currTime);

	color = BLACK_WHITE;
	mediaPlayer =SIMPLE_PLAYER;
}

Status::Status(ifstream& inFile)
{
	int textLen, timeLen, temp_;

	inFile >> textLen;
	char* temp = new char[textLen+1];
	inFile.read(temp, textLen);
	temp[textLen] = '\0';
	textContent = temp;

	inFile >> timeLen;
	temp = new char[timeLen + 1];
	inFile.read(temp, timeLen);
	temp[timeLen] = '\0';
	statTm = temp;
	
	inFile >> temp_;
	color = (eColor)temp_;
	
	inFile >> temp_;
	mediaPlayer = (ePlayer)temp_;

	delete[]temp;
}

bool Status:: operator==(const Status& other)const
{
	if (textContent == other.textContent)
		return true;
	return false;	
	
}

bool Status:: operator!=(const Status& other)const
{
	if (*this == other)
		return false;
	return true;
}

void Status::showContent() const
{
	cout << textContent << "\ndate: "<<statTm;
	cout <<"Status's color: " << (color == BLACK_WHITE ? "black and white" : "colorful")<< "\n";
	cout << "Status's media player: " << (mediaPlayer == SIMPLE_PLAYER ? "simple player" : "video player") << "\n";

}

int Status::getColor()
{
	return color;
}

int Status::getMediaPlayer()
{
	return mediaPlayer;
}

void Status::setColor(const eColor color)
{
	this->color = color;
}

void Status::setMediaPlayer(const ePlayer mediaPlayer)
{
	this->mediaPlayer = mediaPlayer;
}

void Status::save(ofstream& outFile) const
{
	int textLen, timeLen, type;
	textLen = textContent.length();
	timeLen = statTm.length();
	
	if (color == BLACK_WHITE)
		type = 0;
	else if (color == COLORFUL && mediaPlayer == SIMPLE_PLAYER)
		type = 1;
	else
		type = 2;

	outFile << type << " ";

	outFile << textLen;
	outFile.write((const char*)textContent.c_str(), textLen);
	outFile << timeLen;
	outFile.write((const char*)statTm.c_str(), timeLen);
	outFile << color<< " ";

	outFile<<mediaPlayer<<" ";


}



