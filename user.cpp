#include"user.h"
using namespace std;


User::User(const string& name_, const Date& birthday, int index)noexcept(false) : name(name_), birthday(birthday), uIndex(index)
{
	if (name_ == "")
		throw emptyUserName();
	if(!isValidBDay())
		throw invalidBirthday();
}

User::User(ifstream& inFile)
{
	int len, i, textLen, statusType;
	inFile >> len;
	char* temp = new char[len + 1];
	inFile.read(temp, len);
	temp[len] = '\0';
	name = temp;

	inFile >> i;
	birthday.setDay(i);

	inFile >> i;
	birthday.setMonth(i);

	inFile >> i;
	birthday.setYear(i);

	inFile >> uIndex;

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

void User:: operator+=(User& other)
{
	friends.push_back(&other);
	other.friends.push_back(this);
}

void User:: operator+=(FanPage& page)
{
	pages.push_back(&page);
}

bool User:: operator>(User* other)
{
	if (friends.size() > other->friends.size())
		return true;
	return false;
}

bool User:: operator>(FanPage* page)
{
	if (friends.size() > page->numOfFans())
		return true;
	return false;
}

string User::getBDay()const
{
	string BDay;
	BDay = to_string(birthday.getDay());
	BDay += "/" ;
	BDay += to_string(birthday.getMonth());
	BDay += "/";
	BDay += to_string(birthday.getYear());

	return BDay;
}

void User::addStatus(Status* s)
{
	board.push_back(s);
}

void User::showPages() const
{
	vector<FanPage*>::const_iterator  itr;
	if (pages.size() == 0)
		cout << "There are no fan pages for this user.\n" << endl;
	else {
		cout << name << "is a fan of the next pages:\n";

		for (itr = pages.begin(); itr != pages.end(); ++itr)
			cout << (*itr)->getName() << "\n";
		cout << endl;
	}
}

void User::showAllStatuses() const
{
	vector<Status*>::const_iterator  itr;
	if (board.size() == 0)
		cout << "There are no fan statuses for this user.\n" << endl;
	else {
		cout << "\n" << name << "'s statuses: \n";
		for (itr = board.begin(); itr != board.end(); ++itr)
			(*itr)->showContent();
		cout << endl;
	}
}

void User::showFriends() const
{
	vector<User*>::const_iterator  itr;
	if (friends.size() == 0)
		cout << "There are no friends to this user.\n" << endl;
	for (itr = friends.begin(); itr != friends.end(); ++itr) 
		cout << (*itr)->name << ", birthday: " << (*itr)->getBDay() <<"\n";
	cout << endl;
}

void User::show10RecentStatus() const
{
	int i=0;

	vector<Status*>::const_iterator  itr;
	cout << "\n" << name << "'s statuses: \n";
	for (itr = board.begin(); itr != board.end() && i<10; ++itr, i++)
		(*itr)->showContent();
	cout << endl;

}

void User::show10RecentStatusOfAllFriends() const 
{
	int i = 0;
	vector<User*> ::const_iterator itr;

	for (itr = friends.begin(); itr != friends.end() && i < TEN; ++itr, i++)
		(*itr)->show10RecentStatus();
}

void User:: removeFriend(User* fToRemove)
{
	vector<User*> ::iterator itr = friends.begin();

	while (itr!= friends.end())
	{
		if (*itr == fToRemove)
		{
			friends.erase(itr);
			itr = friends.end();
		}
		else
			++itr;
	}

}

void User:: removePage(FanPage& pToRemove)
{

	vector<FanPage*> ::iterator itr = pages.begin();

	while (itr != pages.end())
	{
		if (*itr == &pToRemove)
		{
			pages.erase(itr);
			itr = pages.end();
		}
		else
			++itr;
	}


}

bool User:: isValidBDay()const
{
	if (birthday.getDay() < ONE || birthday.getDay() > DAY_IN_MONTH)
		return false;
	if (birthday.getMonth() < ONE || birthday.getMonth() > MONTH_NUM)
		return false;
	if (birthday.getYear() < MIN_YEAR || birthday.getYear() > MAX_YEAR)
		return false;
	return true;
}

bool User::userIsFriend(const User& u) const
{
	vector<User*>::const_iterator  itr;

	for (itr = friends.begin(); itr != friends.end(); ++itr)
		if ((*itr)->getName() == u.getName())
			return true;
	return false;
}

void User::save(ofstream& outFile) const
{
	int i, len;
	len = name.length();
	outFile << len;
	outFile.write((const char*)name.c_str(), len);

	outFile << birthday.getDay() <<" "<< birthday.getMonth()<<" "<< birthday.getYear()<<" ";
	
	outFile << uIndex<<" ";

	len = board.size();
	outFile << len << " ";
	for (i = 0; i < len; i++)
		board[i]->save(outFile);

}

int User::getPageIndex(int arrIndx) const
{ 
	return pages[arrIndx]->getIndex(); 
}









