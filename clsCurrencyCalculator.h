#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculator:protected clsScreen
{
private:
    static void _Print(clsCurrency Currency,string Titel="Currency Card:")
    {
        cout << Titel;
        cout << "\n___________________";
        cout << "\nCountry  : " << Currency.Country();
        cout << "\nCode     : " << Currency.CurrencyCode();
        cout << "\nName     : " << Currency.CurrencyName();
        cout << "\nRate(1$) : " << Currency.Rate();
        cout << "\n___________________\n\n";
    }

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate<float>::ReadFloatNumber();
        return Amount;
    }

    static clsCurrency _GetCurrency(string Text)
    {
        string CurrencyCode;
        cout << Text;

        CurrencyCode = clsInputValidate<string>::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate<string>::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }

    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _Print(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }
        cout << "\nConverting from USD to:\n";

        _Print(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.ConvertFromCurrencyToCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();
    }
    

public:
    static void CurrencyCalculator()
    {
        char Answer = 'n';
        do
        {
            system("cls");
            _DrawScreenHeader("\tCalculator Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
               
            cout << "\n\nDo you want to perform another Calculation ? y/n ? ";
            cin >> Answer;

        } while (Answer == 'Y' || Answer == 'y');

    }

};

