#include "Facebook.h"
using namespace std;


int Facebook::showMenuAndGetChoice()const
{
	int choice;

	cout << "You can choose one of the following actions:\n\n"
		<< "1- Create new friend on Facebook.\n"
		<< "2- Create new fan page on Facebook.\n"
		<< "3- Add new status to user.\n"
		<< "4- Add new status to fan page.\n"
		<< "5- Show all statuses of user.\n"
		<< "6- Show all statuses of fan page.\n"
		<< "7- Show 10 recent statuses of all friends of user.\n"
		<< "8- Create new friendship.\n"
		<< "9- Cancel friendship.\n"
		<< "10- Add new fan to page.\n"
		<< "11- Remove fan from page.\n"
		<< "12- Show all users and pages.\n"
		<< "13- Show all friends of user.\n"
		<< "14- Show All fans of page.\n"
		<< "15- Exit.\n"
		<< "\nPlease enter your choice:";

	cin >> choice;
	cout << "\n";
	return choice;

}

void Facebook::makeAction(int i)
{
	switch (i)
	{
	case ONE:
		readUser();
		break;
	case TWO:
		readFanPage();
		break;
	case THREE:
		readStatusToUser();
		break;
	case FOUR:
		readStatusToPage();
		break;
	case FIVE:
		showAllStatusOfUser();
		break;
	case SIX:
		showAllStatusOfPage();
		break;
	case SEVEN:
		show10RecentStatusOfAllUserFriends();
		break;
	case EIGHT:
		createFriendShip();
		break;
	case NINE:
		cancelFriendship();
		break;
	case TEN:
		addFanToPage();
		break;
	case ELEVEN:
		removeFanFromPage();
		break;
	case TWELVE:
		showAllObjectsInFacebook();
		break;
	case THIRTEEN:
		ShowAllFriendsOfUser();
		break;
	case FOURTEEN:
		ShowAllFansOfPage();
		break;
	case FIFTEEN:
		cout << "Thank you and bye bye!";
	}
}

void Facebook::readUser()
{
	bool isValidData = false;
	string name;
	
	int day, month, year;

	while (isValidData == false)
	{
		isValidData = true;
		
		cout << "\nPlease enter user name:";
		getchar();
		getline(cin, name);

	
		cout << "\nPlease enter user birthday:\n";
		cout << "\nDay: ";
		cin >> day;
		cout << "\nMonth: ";
		cin >> month;
		cout << "\nYear: ";
		cin >> year;

		Date bDay(day, month, year);
		cout << "\n";
		try
		{
			a.createUser(name, bDay);
		}
		catch (std::exception& e)
		{
			cout << e.what()<<endl;
			isValidData = false;
		}
		
	}
}

void Facebook::readFanPage() 
{
	string name;
	bool isValidData = false;
	while (isValidData == false)
	{
		isValidData = true;
		cout << "Please enter fan page name:";
		getchar();
		getline(cin, name);
		cout << "\n";
		try
		{
			a.createFanPage(name);
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
			isValidData = false;
		}
	}
	
}

void Facebook::readStatusToUser() 
{
	string content , mediaFileName;
	int uIndex, statusType;
	bool isValidData = false;
	uIndex = getUserIndexForActions();

	while (isValidData == false)
	{
		isValidData = true;
		try
		{
			statusType = statusTypeChoice(mediaFileName);
			cout << "Please enter status's text:";
			getchar();
			getline(cin, content);
			a.addStatusToUser(content, a.getUserInIndex(uIndex), statusType, mediaFileName);
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
			isValidData = false;
		}
		cout << "\n";
	}

}

void Facebook:: readStatusToPage()
{
	string content, mediaFileName;
	int pIndex, statusType;
	bool isValidData = false;
	pIndex = getPageIndexForActions();

	while (isValidData == false)
	{
		isValidData = true;
		try
		{
			statusType = statusTypeChoice(mediaFileName);
			cout << "Please enter status:";
			getchar();
			getline(cin, content);
			a.addStatusToPage(content, a.getPageInIndex(pIndex), statusType, mediaFileName);
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
			isValidData = false;
		}
		cout << "\n";
	}
}

void Facebook::showAllStatusOfUser()const
{
	int uIndex;

	uIndex = getUserIndexForActions();

	a.showUserStatus(a.getUserInIndex(uIndex));
	cout << "\n";

}

void Facebook::showAllStatusOfPage()const
{
	int pIndex;
	pIndex = getPageIndexForActions();
	a.showPageStatus(a.getPageInIndex(pIndex));
	cout << "\n";
}

int Facebook:: getUserIndexForActions()const
{
	bool isValid = false;
	int uIndex;
	while (isValid == false)
	{
		isValid = true;

		cout << "\nChoose user from the list:\n";
		a.showAllUsers();
		cout << "Please enter the number of the chosen user:";
		cin >> uIndex;
		try
		{
			a.validUserChoice(uIndex);
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
			isValid = false;
		}
	}

	return(uIndex-1);
}

int Facebook:: getPageIndexForActions()const
{
	int pIndex;
	bool isValid = false;
	while (isValid==false)
	{
		isValid = true;
		cout << "\nChoose page from the list:\n";
		a.showAllPages();
		cout << "Please enter the number of the chosen page:";
		cin >> pIndex;
		try
		{
			a.validPageChoice(pIndex);
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
			isValid = false;
		}
	}
	return (pIndex - 1);
}

void Facebook::show10RecentStatusOfAllUserFriends()
{

	int uIndex;
	uIndex = getUserIndexForActions();
	
	a.show10RecentStatusOfAllUserFriends(a.getUserInIndex(uIndex));
}

void Facebook::createFriendShip()
{
	int u1Index, u2Index;
	bool isValid = false;
	while (!isValid)
	{
		isValid = true;

		u1Index = getUserIndexForActions();
		u2Index = getUserIndexForActions();

		try
		{
			a.createFriendship(a.getUserInIndex(u1Index), a.getUserInIndex(u2Index));
		}
		catch (std::exception& e)
		{
			cout << e.what();
			isValid = false;
		}
	}
}

void Facebook::cancelFriendship()
{
	int u1Index, u2Index;
	bool isValid = false;
	User *u1, *u2;
	while (!isValid)
	{
		isValid = true;

		u1Index = getUserIndexForActions();
		u2Index = getUserIndexForActions();
		u1 = &a.getUserInIndex(u1Index);
		u2 = &a.getUserInIndex(u2Index);
		try
		{
			a.cancelFriendship(*u1, *u2);
		}
		catch (std::exception& e)
		{
			cout << e.what();
			isValid = false;
		}
	}


}

void Facebook::addFanToPage()
{
	bool isValid = false;
	int uIndex, pIndex;
	User* user;
	FanPage* page;
	while (!isValid)
	{
		isValid = true;

		uIndex = getUserIndexForActions();
		pIndex = getPageIndexForActions();
		user = &a.getUserInIndex(uIndex);
		page = &a.getPageInIndex(pIndex);

		try
		{
			a.addFanToPage(*user, *page);
		}
		catch (std::exception& e)
		{
			cout << e.what();
			isValid = false;
		}
	}
}

void Facebook:: removeFanFromPage()
{
	bool isValid = false;
	int uIndex, pIndex;
	User* user;
	FanPage* page;
	while (!isValid)
	{
		isValid = true;

		uIndex = getUserIndexForActions();
		pIndex = getPageIndexForActions();
		user = &a.getUserInIndex(uIndex);
		page = &a.getPageInIndex(pIndex);
		try
		{
			a.deleteFanFromPage(*user, *page);
		}
		catch (std::exception& e)
		{
			cout << e.what();
			isValid = false;
		}
	}
}

void Facebook:: showAllObjectsInFacebook()const
{
	a.showAllUsers();
	a.showAllPages();
}

void Facebook::ShowAllFriendsOfUser()const
{
	int uIndex;
	uIndex = getUserIndexForActions();
	a.showUserFriends(a.getUserInIndex(uIndex));
}

void Facebook::ShowAllFansOfPage()const
{
	int pIndex;
	pIndex = getPageIndexForActions();
	a.showPageFans(a.getPageInIndex(pIndex));
}

int Facebook::statusTypeChoice(string& mediaFileName) noexcept(false)
{
	int statusType;
	cout << "Please choose status's type:\n"
		<< "1- text status\n"
		<< "2- text and image status\n"
		<< "3- text and video status\n";
	cin >> statusType;
	if (statusType < 1 || statusType>3)
		throw invalidInput();
	if (statusType == 2)
	{
		cout << "please enter image file name (add .jpg at the suffix):" << endl;
		cin >> mediaFileName ;
		if (mediaFileName == "" || !checkImageName(mediaFileName))
			throw wrongMediaName();
	}
	else if (statusType == 3)
	{
		cout << "please enter video file name (add .mp4 at the suffix):" << endl;
		cin >> mediaFileName;
		if (mediaFileName == "" || !checkVideoName(mediaFileName))
			throw wrongMediaName();
	}
	return statusType;
}

bool Facebook::isFileEmpty(ifstream& inFile) const
{
	if (inFile.peek() == EOF)
		return true;
	return false;
}

void Facebook::createBuiltInObjects()
{
	a.createBuiltInObjects();
}

void Facebook::save(ofstream& outFile) const
{
	a.save(outFile);
}

bool Facebook::checkImageName(const string& name)const
{
	int nameLen;
	nameLen = name.size();
	if (name[nameLen - 1] == 'g' && name[nameLen - 2] == 'p' && name[nameLen - 3] == 'j' && name[nameLen - 4] == '.')
		return true;
	else
		return false;
}

bool Facebook::checkVideoName(const string& name) const
{
	int nameLen;
	nameLen = name.size();
	if (name[nameLen - 1] == '4' && name[nameLen - 2] == 'p' && name[nameLen - 3] == 'm' && name[nameLen - 4] == '.')
		return true;
	else
		return false;
}


