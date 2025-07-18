#pragma once
#include<iostream>
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen:protected clsScreen
{

private:
	static void _Login()
	{
		bool Loginfaild = false;
		short CountFaild = 3;
		string UserName, Password;
		do
		{	
			if (Loginfaild)
			{
				CountFaild--;
				cout << "\nInvalid UserName/Passward\n";
				cout << "You have " << CountFaild << " Trials to login.\n";
			}

            if (CountFaild == 0)
			{
				cout << "\nYou are Locked after 3 Trial(s).\n";
				exit(0);
			}

			cout << "\nEnter Username ? ";
			getline(cin >> ws, UserName);
			cout << "\nEnter Passward ? ";
			getline(cin, Password);
			CurrentUser = clsUsers::Find(UserName, Password);
			Loginfaild = CurrentUser.IsEmpty();
		} while (Loginfaild);

		CurrentUser.RegristerLogin();
		clsMainScreen::ShowMainMenue();
	}

public:

	static void ShowLogInScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogIn Screen");
		_Login();
	}

};

