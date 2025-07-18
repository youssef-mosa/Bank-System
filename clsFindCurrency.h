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

class clsFindCurrency:protected clsScreen
{
private:

    enum enFindBy{Code = 1,Country = 2};

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

    static short _ReadChosseFindBy()
    {
        short Choice = 0;
        cout << "Find By: [1] Code or [2] Country  ? ";
        short Choose = clsInputValidate<int>::ReadIntNumberBetween(1, 2, "Find By: [1] Code or [2] Country  ? ");
        return Choose;
    }

    static void _ShowResult(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _Print(Currency);
        }

        else
        {
            cout << "\nCurrency Not Found:-(\n";
        }
    }

public:

    static void FindCurrency()
    {
        _DrawScreenHeader("\tFind Currency Screen");

        string Code = "";
        string Country = "";
        enFindBy WhatYouWant;

        WhatYouWant = enFindBy(_ReadChosseFindBy());

        clsCurrency Currency;

        switch (WhatYouWant)
        {
        case enFindBy::Code:
            cout << "\nPlease enter CurrencyCode :";
            Code = clsInputValidate<string>::ReadString();
            Currency = clsCurrency::FindByCode(Code);
            _ShowResult(Currency);
            break;
        case enFindBy::Country:
            cout << "\nPlease enter Country Name :";
            Country = clsInputValidate<string>::ReadString();
            Currency = clsCurrency::FindByCountry(Country);
            _ShowResult(Currency);
            break;
        }
        
    }


};

