#pragma once
#include <iostream>
#include<iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrwaScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsPerson.h"
#include "clsMainScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferListScreen.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <vector>

class clsTransactionScreen:protected clsScreen
{
private:
	enum enTransactions
	{
		enTransaction_enDeposit = 1,enTransaction_enWithdraw = 2,enTransaction_enTotalBalance = 3,
		enTransaction_Tranfer = 4, enTransaction_enTransferLogList = 5, enTransaction_enMainmenue = 6
		
	};

	static void GobacktotransactionMenu()
	{
		cout << "\n\n Press any key to go back to main menu . . .\n\n";
		system("pause>0");
		ShowMenueofTransaction();
	}

	static short _ReadTransactionMenueOption()
	{
		cout << clsUtil::Tabs(3) << "Choose what do you want to do : [1 to 6] ? ";
		short Choose = clsInputValidate<int>::ReadIntNumberBetween(1, 6, "Enter Number Between [1 to 6] ?");
		return Choose;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::DepositScreen();
	}

	static void _ShowWithDrawScreen()
	{
		clsWithdrwaScreen::WithdrawScreen();
	}

	static void _ShowTotalBalanceScreen()
	{
		clsTotalBalanceScreen::ShowClientBalanceList();
	}

	static void _ShowTransferScreen()
	{
		clsTransfarScreen::TransferScreen();
	}

	static void _ShowTransferListScreen()
	{
		clsTransferListScreen::ShowRegisterLoginList();
	}

	static void _PerfromTransactionMenueOption(enTransactions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enTransactions::enTransaction_enDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			GobacktotransactionMenu();
			break;
		}
		case enTransactions::enTransaction_enWithdraw:
			system("cls");
			_ShowWithDrawScreen();
			GobacktotransactionMenu();
			break;

		case enTransactions::enTransaction_enTotalBalance:
			system("cls");
			_ShowTotalBalanceScreen();
			GobacktotransactionMenu();
			break;
		case enTransactions::enTransaction_Tranfer:
			system("cls");
			_ShowTransferScreen();
			GobacktotransactionMenu();
			break;
		case enTransactions::enTransaction_enTransferLogList:
			system("cls");
			_ShowTransferListScreen();
			GobacktotransactionMenu();
			break;

		case enTransactions::enTransaction_enMainmenue:
			break;
		}

	}




public:
	static void ShowMenueofTransaction()
	{

		if (!CheckAccessRight(clsUsers::enperimission::PTransaction))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t\tTrasactions Screen");
		cout << clsUtil::Tabs(3) << "==========================================\n";
		cout << clsUtil::Tabs(3) << "\t   Transaction Menue Screen            \n";
		cout << clsUtil::Tabs(3) << "==========================================\n";
		cout << clsUtil::Tabs(3) << "[1] Deposit.\n";
		cout << clsUtil::Tabs(3) << "[2] Withdraw.\n";
		cout << clsUtil::Tabs(3) << "[3] Total Balance.\n";
		cout << clsUtil::Tabs(3) << "[4] Transfer.\n";
		cout << clsUtil::Tabs(3) << "[5] Transfer Log List.\n";
		cout << clsUtil::Tabs(3) << "[6] Main Menue.\n";
		cout << clsUtil::Tabs(3) << "==========================================\n";
		_PerfromTransactionMenueOption(enTransactions(_ReadTransactionMenueOption()));

	}


};

