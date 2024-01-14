#include "FanPage.h"
using namespace std;


FanPage::FanPage(const string& name, int index)noexcept(false) : name(name), fpIndex(index)
{
	if (name == "")
		throw emptyPageName();
}

FanPage::FanPage(ifstream& inFile)
{
	int len, i, textLen, statusType;
	
	inFile >> len;
	char* temp = new char[len + 1];
	inFile.read(temp, len);
	temp[len] = '\0';
	name = temp;

	inFile >> fpIndex;

	inFile >> len;
	for (i = 0; i < len; i++)
	{
		Status* s;
		inFile >> statusType;
		switch (statusType)
		{
		case 0:
			s = new Status(inFile);
			break;
		case 1:
			s = new ImageStatus(inFile);
			break;
		case 2:
			s = new VideoStatus(inFile);
			break;	
		}
		
		board.push_back(s);
	}

}

void FanPage:: operator+=(User& fan)
{
	fans.push_back(&fan);
}

bool FanPage:: operator>(const FanPage* other)
{
	if (fans.size() > other->fans.size())
		return true;
	return false;
}

bool FanPage:: operator>(const User* user)
{
	if (fans.size() > user->numOfFriends())
		return true;
	return false;
}

void FanPage::addStatus(Status* s)
{
	board.push_back(s);
}

void FanPage::showAllStatuses() const
{
	vector<Status*>::const_iterator itr;
	if (board.size() == 0)
		cout << "There are no statuses for this page.\n" << endl;
	else
	{
		cout << "\n" << name << "'s statuses: \n";
		for (itr = board.begin(); itr != board.end(); ++itr)
			(*itr)->showContent();
		cout << endl;
	}
}

void FanPage::showAllFans() const
{
	vector<User*>::const_iterator  itr;
	if (fans.size() == 0)
		cout << "There are no fans for this page.\n" << endl;
	else
	{
		for (itr = fans.begin(); itr != fans.end(); ++itr)
			cout << (*itr)->getName() << ", birthday: " << (*itr)->getBDay() << "\n";
		cout << endl;
	}
}

void FanPage:: removeFan(User& fToRemove)
{
	vector<User*> ::iterator itr = fans.begin();

	while (itr != fans.end())
	{
		if (*itr == &fToRemove)
		{
			fans.erase(itr);
			itr = fans.end();
		}
		else
			++itr;
	}

}

bool FanPage::IsFan(const User& u) const
{
	vector<User*> ::const_iterator itr = fans.begin();
	for (itr = fans.begin(); itr != fans.end(); ++itr)
	{
		if ((*itr) == &u)
			return true;
	}
	return false;
}

void FanPage::save(ofstream& outFile) const
{
	int i,len,textLen;
	
	len = name.length();
	outFile << len;
	outFile.write((const char*)name.c_str(), len);

	outFile << fpIndex << " ";

	len = board.size();
	outFile << len << " ";
	for (i = 0; i < len; i++)
	{
		board[i]->save(outFile);
	}
}
