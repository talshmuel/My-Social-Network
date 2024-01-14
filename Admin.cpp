#include "Admin.h"
using namespace std;


//private functions:

void Admin::createBuiltInObjects()
{

	User *Ilan, *Oded, *Kobi;
	FanPage* a, * b, * c;
	string s = "", imgstring= "mypicture.jpg";


	Ilan = createUser("Ilan Rozenfeld", Date(1,1,1985));
	Oded = createUser("Oded Paz", Date(30, 9, 1986));
	Kobi = createUser("Kobi Farag", Date(5, 11, 1987));

	
	a = createFanPage("The Pajamas");
	b = createFanPage("Gerry's hamburger");
	c = createFanPage("We miss Alona Tal");

	createFriendship(*Ilan, *Oded);
	createFriendship(*Ilan, *Kobi);
	createFriendship(*Oded, *Kobi);
	
	addFanToPage(*Ilan, *a);
	addFanToPage(*Oded, *b);
	addFanToPage(*Kobi, *c);
	
	addStatusToUser("Well, what do I need it for?", *Ilan, 1, s);
	addStatusToUser("I'm all in this house", *Ilan, 1, s);

	addStatusToUser("Gotta go, gotta go!", *Oded, 1, s);
	addStatusToUser("Zazzi Bazzazi", *Oded, 1, s);

	addStatusToUser("What a spirit, madness!", *Kobi, 1, s);
	addStatusToUser("This is Neji from the Housing Culture Association", *Kobi, 1, s);

	addStatusToPage("We are on TV!", *a, 1, s);
	addStatusToPage("The Pajamas are back!", *a, 1, s);

	addStatusToPage("Gerry's hamburger is the best hamburger in the world", *b, 1, s);
	addStatusToPage("Mitunaf!", *b, 1, s);

	addStatusToPage("Don't Alona me!", *c, 1, s);
	addStatusToPage("I have a dejavoo", *c, 2, imgstring);
	
}

bool Admin::isUserNameExist(const std::string& name)const
{
	bool found = false;
	list<User>::const_iterator  itr=users.begin();

	while (itr!= users.end() && found ==false)
	{
		if ((*itr).getName() == name)
			found = true;
		++itr;
	}
	return found;
}

bool Admin:: isPageNameExist(const std::string& name)const
{
	bool found = false;
	list<FanPage>::const_iterator  itr = pages.begin();

	while (itr != pages.end() && found == false)
	{
		if ((*itr).getName() == name)
			found = true;
		++itr;
	}
	return found;
}

void Admin::isFriendshipValid(const User& u1, const User& u2) const noexcept(false)
{
	if (u1.getName()== u2.getName())
		throw selfFriendship();

	if (u1.userIsFriend(u2))
		throw friendshipExists();

}

void Admin::isCancelFriendshipValid(const User& u1, const User& u2) const noexcept(false)
{
	if (u1.getName() == u2.getName())
		throw selfCancelFriendship();

	if (!u1.userIsFriend(u2))
		throw cancelFriendshipExcep();
}



//public functions:
void Admin::restorationData(ifstream& inFile)
{

	int size, i,j, numOfFriends, friendIndx, numOfPages, pageIndx;
	list<User>::iterator  u1Itr;
	list<User>::iterator  u2Itr;
	list<FanPage>::iterator  fpItr;

	inFile >> size;
	for ( i = 0; i < size; i++)
	{
		FanPage f(inFile);
		pages.push_back(f);
	}

	inFile >> size;
	for (i = 0; i < size; i++)
	{
		User u(inFile);
		users.push_back(u);
	}
	
	
	for (i = 0, u1Itr = users.begin(); i < size; i++,++u1Itr)
	{
		inFile >> numOfFriends;
		for (j = 0; j < numOfFriends; j++)
		{
			inFile >> friendIndx;
			u2Itr = users.begin();
			advance(u2Itr, friendIndx);
			if (!(*u1Itr).userIsFriend((*u2Itr)))
				createFriendship((*u1Itr), (*u2Itr));
		}

		inFile >> numOfPages;
		for (j = 0; j < numOfPages; j++)
		{
			fpItr = pages.begin();
			inFile >> pageIndx;
			advance(fpItr, pageIndx);
			if (!(*fpItr).IsFan(*u1Itr))
				addFanToPage((*u1Itr), (*fpItr));
		}
	}
}

User* Admin::createUser(const string& name, const Date& bday)  noexcept(false)
{
	if (isUserNameExist(name))
		throw nameDuplication();
	User newU(name, bday,users.size());
	users.push_back(newU);
	return &users.back();

}

FanPage* Admin::createFanPage(const string& name) noexcept(false)
{
	if (isPageNameExist(name))
		throw pageNameDuplication();
	FanPage newP(name, pages.size());
	pages.push_back(newP);
	return &pages.back();
}

void Admin::addStatusToUser(const string& textContent, User& addTo, int statusType, const string& mediaName) noexcept(false)
{
	Status* newStatus=nullptr;
	
	switch (statusType)
	{
	case 1:
		newStatus = new Status(textContent);
		break;
	case 2:
		newStatus = new ImageStatus(textContent, mediaName);
		break;
	case 3:
		newStatus = new VideoStatus(textContent, mediaName);
		break;
	}
	
	addTo.addStatus(newStatus);
	
}

void Admin:: addStatusToPage(const string textContent, FanPage& addTo, int statusType, const string& mediaName) noexcept(false)
{
	Status* newStatus = nullptr;

	switch (statusType)
	{
	case 1:
		newStatus = new Status(textContent);
		break;
	case 2:
		newStatus = new ImageStatus(textContent, mediaName);
		break;
	case 3:
		newStatus = new VideoStatus(textContent, mediaName);
		break;
	}
	addTo.addStatus(newStatus);
}

void Admin::showUserStatus(const User& u) const
{
	u.showAllStatuses();
}

void Admin::showPageStatus(const FanPage& p) const
{
	p.showAllStatuses();
}

void Admin::show10RecentStatusOfAllUserFriends(const User& u)const 
{
	u.show10RecentStatusOfAllFriends();
}

void Admin::createFriendship(User& u1, User& u2)
{
	isFriendshipValid(u1, u2);
	u1 += u2;
}

void Admin:: cancelFriendship(User& u1, User& u2)
{
	isCancelFriendshipValid(u1, u2);
	u1.removeFriend(&u2);
	u2.removeFriend(&u1);	
}

void Admin::addFanToPage(User& u, FanPage& fp) noexcept(false)
{
	if (fp.IsFan(u))
		throw fanPageExist();
	fp+=u;
	u += fp;
}

void Admin:: deleteFanFromPage(User& u, FanPage& p)
{
	if (!p.IsFan(u))
		throw fanPageNotExist();
	p.removeFan(u);
	u.removePage(p);
}

void Admin::showAllUsers() const
{
	int i = 1;
	cout << "Facebook users:\n";
	list<User>::const_iterator  itr;

	for (itr = users.begin(), i=1; itr != users.end(); ++itr,i++)
		cout <<i<<"- "<<(*itr).getName() << " birthday: " << (*itr).getBDay() << "\n";
	cout << endl;

}

void Admin::showAllPages() const
{
	int i = 1;
	cout << "Facebook fan pages:\n";
	list<FanPage>::const_iterator  itr;

	for (itr = pages.begin(); itr != pages.end(); ++itr,i++)
		cout<<i<<"- " << (*itr).getName() << "\n";
	cout << endl;

}

void Admin::showUserFriends(const User& u) const 
{
	cout <<"\n" << u.getName() << "'s friends in Facebook:\n";
	u.showFriends();
	cout << "\n";
}

void Admin::showPageFans(const FanPage& fp)  const
{
	cout << fp.getName() << "'s fans:\n";
	fp.showAllFans();
	cout << "\n";
}

const User& Admin::getUserInIndex(int index)const
{
	int i = 0;
	list<User>::const_iterator itr;

	for (itr = users.begin(); itr != users.end() && i < index; ++itr, ++i) {}
   
	return (*itr);
}

 User& Admin::getUserInIndex(int index)
{
	int i = 0;
	list<User>::iterator itr;

	for (itr = users.begin(); itr != users.end() && i < index; ++itr, ++i) {}

	return (*itr);
}

const FanPage& Admin::getPageInIndex(int index) const
{
	int i = 0;
	list<FanPage>::const_iterator itr;

	for (itr = pages.begin(); itr != pages.end() && i < index; ++itr, ++i) {}

	return (*itr);
	
}

FanPage& Admin::getPageInIndex(int index)
{
	int i = 0;
	list<FanPage>::iterator itr;

	for (itr = pages.begin(); itr != pages.end() && i < index; ++itr, ++i) {}

	return (*itr);

}

void Admin::validUserChoice(int index) const noexcept(false)
{
	if (index > users.size() || index < 1)
		throw invalidInput();
}

void  Admin::validPageChoice(int index) const noexcept(false)
{
	if (index > pages.size() || index < 1)
		throw invalidInput();
}

void Admin::save(ofstream& outFile) const
{
	list<FanPage>::const_iterator fpItr;
	list<User>::const_iterator uItr;
	int size, friendsNum,pagesNum, i;

	size = pages.size();
	outFile << size<<" ";
	for (fpItr = pages.begin(); fpItr != pages.end(); ++fpItr)
		(*fpItr).save(outFile);
	

	size = users.size();
	outFile << size << " ";
	for (uItr = users.begin(); uItr != users.end(); ++uItr)
		(*uItr).save(outFile);
	

	for (uItr = users.begin(); uItr != users.end(); ++uItr)
	{
	    friendsNum =(*uItr).numOfFriends();
		outFile << friendsNum << " ";
		for ( i = 0; i <friendsNum ; i++)
			outFile << (*uItr).getFriendIndex(i)<< " ";

		pagesNum = (*uItr).numOfPages();
		outFile << pagesNum << " ";
		for (i = 0; i < pagesNum; i++)
			outFile << (*uItr).getPageIndex(i) << " ";
	}
}
