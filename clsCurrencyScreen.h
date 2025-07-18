#pragma once
#include <iostream>
#include<iomanip>
#include "clsShowCurrencyList.h"
#include "clsFindCurrency.h"
#include "clsUpdateRateCurrency.h"
#include "clsCurrencyCalculator.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <vector>

class clsCurrencyScreen:protected clsScreen
{
	enum enCurrencyExchange
	{
		enListCurrencies = 1,
		enFindCurrencies = 2,
		enUpdateRate = 3,
		enCurrencyCalculate = 4,
		enMainMenue=5
	};

	static short _ReadCurrencyExchangeMenueOption()
	{
		cout << clsUtil::Tabs(3) << "Choose what do you want to do : [1 to 5] ? ";
		short Choose = clsInputValidate<int>::ReadIntNumberBetween(1, 5, "Enter Number Between [1 to 5] ?");
		return Choose;
	}

	static void _GobacktoCurrencyExchangeMenu()
	{
		cout << "\n\n Press any key to go back to main menu . . .\n\n";
		system("pause>0");
		ShowCurrencyExchangeMenue();
	}

	static void _Currencylist()
	{
		clsShowCurrencyList::ShowCurrencyList();
	}

    static void _FindCurrency()
	{
		clsFindCurrency::FindCurrency();
	}

	static void _UpdateCurrency()
	{
		clsUpdateRateCurrency::UpdateRateCurrency();
	}

	static void CurrencyCalculator()
	{
		clsCurrencyCalculator::CurrencyCalculator();
	}

	static void _PerfromCurrencyExchangeOption(enCurrencyExchange MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enCurrencyExchange::enListCurrencies:
		{
			system("cls");
			_Currencylist();
			_GobacktoCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchange::enFindCurrencies:
			system("cls");
			_FindCurrency();
			_GobacktoCurrencyExchangeMenu();
			break;

		case enCurrencyExchange::enUpdateRate:
			system("cls");
			_UpdateCurrency();
			_GobacktoCurrencyExchangeMenu();
			break;

		case enCurrencyExchange::enCurrencyCalculate:
			system("cls");
			CurrencyCalculator();
			_GobacktoCurrencyExchangeMenu();
			break;

		case enCurrencyExchange::enMainMenue:
			break;
		}

	}
public:
	static void ShowCurrencyExchangeMenue()
	{

		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Screen");

		cout << clsUtil::Tabs(3) << "" << "===========================================\n";
		cout << clsUtil::Tabs(3) << "" << "\tCurrency Exchange Main Screen\n";
		cout << clsUtil::Tabs(3) << "" << "===========================================\n";
		cout << clsUtil::Tabs(3) << "" << "\t[1] List Currencies.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[2] Find Currency.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[3] Update Rate.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[4] Currency Calculator.\n";
		cout << clsUtil::Tabs(3) << "" << "\t[5] Main Menue.\n";
		cout << clsUtil::Tabs(3) << "" << "===========================================\n";

		_PerfromCurrencyExchangeOption((enCurrencyExchange)_ReadCurrencyExchangeMenueOption());
	}
};

