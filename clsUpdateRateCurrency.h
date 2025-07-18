#pragma once
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "clsCurrency.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

class clsUpdateRateCurrency:protected clsScreen
{
private:
    static void _Print(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry  : " << Currency.Country();
        cout << "\nCode     : " << Currency.CurrencyCode();
        cout << "\nName     : " << Currency.CurrencyName();
        cout << "\nRate(1$) : " << Currency.Rate();
        cout << "\n___________________\n";
    }

    static float _ReadNewRate()
    {
        cout << "\n\nEnter New Rate: ";
        float NewRate = clsInputValidate<float>::ReadFloatNumber();
        return NewRate;
    }

public:
    static void UpdateRateCurrency()
    {
        _DrawScreenHeader("\tUpdate Currency Screen");

        cout << "Please enter Currency Code: ";
        string Code = clsInputValidate<string>::ReadString();

        while (!clsCurrency::IsCurrencyExist(Code))
        {
            cout << "\nCode Not Found , Enter another one : ";
            Code = clsInputValidate<string>::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(Code);
        _Print(Currency);

        char Answer = 'n';
        cout << "\nAre you sure you want update the rate of this Currency ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            cout << "\n\n Update Currency Rate :";
            cout << "\n_____________________________";

            Currency.UpdateRate(_ReadNewRate());
            cout << "\n\nCurrency Rate Update successfully :-)\n";
            _Print(Currency);
        }


    }

};

