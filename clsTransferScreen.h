#pragma once
#include <iostream>
#include <string>
#include "clsUsers.h"
#include "clsString.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <vector>
#include <iomanip>
#include <fstream>

class clsTransfarScreen:protected clsScreen
{
private:

    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name     : " << Client.FullName();
        cout << "\nAccountNumber : " << Client.AccountNumber();
        cout << "\nAccountBalance: " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(string Text)
    {
        string AccountNumber;
        cout << Text;
        AccountNumber = clsInputValidate<string>::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }
        return AccountNumber;
    }

    static double _ReadAmount(clsBankClient SourceClient)
    {
        double Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate<double>::ReadDblNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate<double>::ReadDblNumber();
        }
        return Amount;
    }

    static bool IsAcountNumberTheSameAccount(string AccountNumber1, string AccountNumber2)
    {
        if (AccountNumber1 == AccountNumber2)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

public:

    static void TransferScreen()
    {
        _DrawScreenHeader("\t\tTranfer Screen");
        string SourceAccountNumber = "";
        string DestinationAccountNumber = "";

        SourceAccountNumber = _ReadAccountNumber("\nPlease Enter Account Number to Transfer From: ");

        clsBankClient SourceClient = clsBankClient::Find(SourceAccountNumber);
        _Print(SourceClient);

        DestinationAccountNumber = _ReadAccountNumber("\nPlease Enter Account Number to Transfer To: ");

        while (!IsAcountNumberTheSameAccount(SourceAccountNumber, DestinationAccountNumber))
        {
            cout << "\nYou can't Transfer money to the same Account Number!\n";
            DestinationAccountNumber = _ReadAccountNumber("\nPlease Enter Account Number to Transfer To: ");
        }

        clsBankClient DestinationClient = clsBankClient::Find(DestinationAccountNumber);
        _Print(DestinationClient);

        double Amount = _ReadAmount(SourceClient);
        char Answer = 'n';

        cout << "\nAre you sure you want to perform this operation? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Tranfer(Amount, DestinationClient))
            {
                cout << "\nTransfer done Successfully.\n";
            }
            else
            {
                cout << "\nTransfer Faild.\n";
            }
        }
        _Print(SourceClient);
        _Print(DestinationClient);
    }


};

