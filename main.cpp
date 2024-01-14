#define _CRT_SECURE_NO_WARNINGS
#include "Facebook.h"
#include <iostream>
const int FINISH = 15;
using namespace std;


int main()
{
	Facebook f;
	int choice=0;

	ifstream inFile("facebook.txt");
	if (f.isFileEmpty(inFile))
		f.createBuiltInObjects();
	else
		f.restoration(inFile);

	inFile.close();

	cout << "Wellcome to Facebook!\n\n";
	while (choice != FINISH)
	{
		try
		{
			choice = f.showMenuAndGetChoice();
			f.makeAction(choice);
		}
		catch (...)
		{
			cout << "Unknown error!";
		}
	}

	ofstream outFile("facebook.txt", ios::trunc);
	f.save(outFile);
	outFile.close();

}