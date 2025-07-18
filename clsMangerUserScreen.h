#pragma once
#include <iostream>
#include<iomanip>
#include "clsPerson.h"
#include "clsUserListScreen.h"
#include "clsAddUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsMainScreen.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <vector>

class clsMangerUserScreen: protected clsScreen
{
private:
	enum enMangeUser
	{
		enMangeUser_ShowUserlist = 1,
		enMangeUser_AddnewUserscrren = 2,
		enMangeUser_DeletUserscreen = 3,
		enMangeUser_UpdateUserscreen = 4,
		enMangeUser_FindUserscreen = 5,
		enMangeUser_enMainmenue = 6
	};

	static short _ReadMangerUserMenueOption()
	{
		cout << clsUtil::Tabs(3) << "Choose what do you want to do : [1 to 6] ? ";
		short Choose = clsInputValidate<int>::ReadIntNumberBetween(1, 6, "Enter Number Between [1 to 6] ?");
		return Choose;
	}

	static void _GobacktoMangerUserMenu()
	{
		cout << "\n\n Press any key to go back to main menu . . .\n\n";
		system("pause>0");
		ShowManagerUserMenue();
	}

	static void _ShowUserlist()
	{
		clsUserListScreen::ShowUserList();
	}

	static void _AddNewUser()
	{
		clsAddUserScreen::AddNewUser();
	}

	static void _DeletUser()
	{
		clsDeleteUserScreen::DeletUser();
	}

	static void _UpdateUser()
	{
		clsUpdateUserScreen::UpdateUser();
	}

	static void _FindUser()
	{
		clsFindUserScreen::FindUser();
	}

	static void _PerfromMangerUserOption(enMangeUser MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMangeUser::enMangeUser_ShowUserlist:
		{
			system("cls");
			_ShowUserlist();
			_GobacktoMangerUserMenu();
			break;
		}
		case enMangeUser::enMangeUser_AddnewUserscrren:
			system("cls");
			_AddNewUser();
			_GobacktoMangerUserMenu();
			break;

		case enMangeUser::enMangeUser_DeletUserscreen:
			system("cls");
			_DeletUser();
			_GobacktoMangerUserMenu();
			break;

		case enMangeUser::enMangeUser_UpdateUserscreen:
			system("cls");
			_UpdateUser();
			_GobacktoMangerUserMenu();
			break;

		case enMangeUser::enMangeUser_FindUserscreen:
			system("cls");
			_FindUser();
			_GobacktoMangerUserMenu();
			break;

		case enMangeUser::enMangeUser_enMainmenue:
			break;
		}

	}
public:
	static void ShowManagerUserMenue()
	{

		if (!CheckAccessRight(clsUsers::enperimission::PMangeUser))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("\t\tManger User Screen");

		cout << clsUtil::Tabs(3) << "" << "===========================================\n";
		cout << clsUtil::Tabs(3) << "" << "\t\tManger User\n";
		cout << clsUtil::Tabs(3) << "" << "===========================================\n";
		cout << clsUtil::Tabs(3) << "" << "\t[1] List Users.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[2] Add New User.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[3] Delete User.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[4] Update User.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[5] Find User.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[6] Main Menue.\n";
		cout << clsUtil::Tabs(3) << "" << "===========================================\n";

		_PerfromMangerUserOption((enMangeUser)_ReadMangerUserMenueOption());
	}
};

