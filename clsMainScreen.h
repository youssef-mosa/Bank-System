#pragma once
#include <iostream>
#include "clsPerson.h"
#include "Global.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsMangerUserScreen.h"
#include "clsRegristerLoginList.h"
#include "clsCurrencyScreen.h"
#include "clsUtil.h"
#include <vector>
using namespace std;

class clsMainScreen:protected clsScreen
{
private:
	enum _enMainMenueOption
	{
		eShowclintlist = 1,eAddnewclintscrren = 2,eDeletclintscreen = 3,eUpdateclintscreen = 4
		,eFindclintscreen = 5,eTransaction = 6,eMangeUser = 7,enRegisterLogin = 8 ,enCurrencyExchange = 9,
		eLogout = 10
	};

	static void _GobacktoMainmenu()
	{
		cout << setw(37) << left << "\n\n Press any key to go back to main menu . . .\n\n";
		system("pause>0");
		ShowMainMenue();
	}

	static short _ReadMainMenueOption()
	{
		cout << clsUtil::Tabs(3) << " Choose what do you want to do :[1 to 10] ? ";
		short Choose = clsInputValidate<int>::ReadIntNumberBetween(1, 10, "Enter Number Between [1 to 10] ?");
		return Choose;
	}

	static void _ShowAllClientScreen()
	{
		clsClientListScreen::ShowClientList();
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddClientScreen::AddNewClient();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::DeletClient();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::UpdateClient();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::FindClient();
	}

	static void _ShowTransactionScreen()
	{
		clsTransactionScreen::ShowMenueofTransaction();
	}

	static void _ShowMangeUserScreen()
	{
		clsMangerUserScreen::ShowManagerUserMenue();
	}

	static void RegisterLogin()
	{
		clsRegristerLogin::ShowRegisterLoginList();
	}

	static void ShowCurrencyExchange()
	{
		clsCurrencyScreen::ShowCurrencyExchangeMenue();
	}

	static void _Logout()
	{
		CurrentUser = clsUsers::Find("", "");
	}

	static void _PerfromMangerUserOption(_enMainMenueOption MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case _enMainMenueOption::eShowclintlist:
		{
			system("cls");
			_ShowAllClientScreen();
			_GobacktoMainmenu();
			break;
		}
		case _enMainMenueOption::eAddnewclintscrren:
			system("cls");
			_ShowAddNewClientScreen();
			_GobacktoMainmenu();
			break;

		case _enMainMenueOption::eDeletclintscreen:
			system("cls");
			_ShowDeleteClientScreen();
			_GobacktoMainmenu();
			break;

		case _enMainMenueOption::eUpdateclintscreen:
			system("cls");
			_ShowUpdateClientScreen();
			_GobacktoMainmenu();
			break;

		case _enMainMenueOption::eFindclintscreen:
			system("cls");
			_ShowFindClientScreen();
			_GobacktoMainmenu();
			break;

		case _enMainMenueOption::eTransaction:
			system("cls");
			_ShowTransactionScreen();
			_GobacktoMainmenu();
			break;

		case _enMainMenueOption::eMangeUser:
			system("cls");
			_ShowMangeUserScreen();
			_GobacktoMainmenu();
			break;
		case _enMainMenueOption::enRegisterLogin:
			system("cls");
			RegisterLogin();
			_GobacktoMainmenu();
			break;
		case _enMainMenueOption::enCurrencyExchange:
			system("cls");
			ShowCurrencyExchange();
			_GobacktoMainmenu();
			break;

		case _enMainMenueOption::eLogout:
			system("cls");
			_Logout();
			//Login();

			break;
		}

	}


public:
	static void ShowMainMenue()
	{

		system("cls");
		_DrawScreenHeader("\t\t  Main Screen");

		 cout << clsUtil::Tabs(3)<<""<< "===========================================\n";
            cout << clsUtil::Tabs(3) << "" << "\t\tMain Menue\n";
            cout << clsUtil::Tabs(3) << "" << "===========================================\n";
            cout << clsUtil::Tabs(3) << "" << "\t[1] Show Client List.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[2] Add New Client.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[3] Delete Client.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[4] Update Client Info.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[5] Find Client.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[6] Transactions.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[7] Manage Users.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[8] Login Register List.\n";
            cout << clsUtil::Tabs(3) << "" << "\t[9] Currency Exhcange .\n";
            cout << clsUtil::Tabs(3) << "" << "\t[10] Logout.\n";
            cout << clsUtil::Tabs(3) << "" << "===========================================\n";

		_PerfromMangerUserOption((_enMainMenueOption)_ReadMainMenueOption());
	}

};

