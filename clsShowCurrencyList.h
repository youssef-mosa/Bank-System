#pragma once
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
class clsShowCurrencyList:protected clsScreen
{
private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(15) << left << Currency.Rate();
    }


public:
    static void ShowCurrencyList()
    {

        vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();

        string Titel = "\tCurrencies List Screen";
        string SubTitel = "\t(" + to_string(vCurrency.size()) + ")Currency";
        _DrawScreenHeader(Titel, SubTitel);
        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(15) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrency.size() == 0)
            cout << "\t\t\t\tNo Currencies Avalible In The System!";
        else

            for (clsCurrency Sclint : vCurrency)
            {
                PrintCurrencyRecordLine(Sclint);
                cout << endl;
            }
        cout << "\n---------------------------------------------------------";
        cout << "-------------------------------------------------------\n";

    }

};

