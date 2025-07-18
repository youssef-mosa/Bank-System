#pragma once
#include <iostream>
#include<iomanip>
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <vector>

class clsWithdrwaScreen:protected clsScreen
{
private:
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName     : " << Client.FirstName;
        cout << "\nLastName      : " << Client.LastName;
        cout << "\nFull Name     : " << Client.FullName();
        cout << "\nEmail         : " << Client.Email;
        cout << "\nPhone         : " << Client.Phone;
        cout << "\nAccountNumber : " << Client.AccountNumber();
        cout << "\nPinCode       : " << Client.PinCode;
        cout << "\nAccountBalance: " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:
    static void WithdrawScreen()
    {
        _DrawScreenHeader("\t\tWithdraw Screen");
        string AccountNumber = "";
        AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient With[" << AccountNumber << "] doesn't Exist. \n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);

        double Amount = 0;
        char Answer = 'n';
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate<double>::ReadDblNumber();
        cout << "\nAre you sure you want Withdraw this ammount? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client.Withdraw(Amount);
            cout << "\nAmount Withdraw Successfully.\n";
            cout << "\nThe New AccountBalance = " << Client.AccountBalance;
        }
        else
        {
            cout << "\nCan not Withdraw ,insuffecient Balance !.\n";
            cout << "\nAmount to Withdraw = " << Amount;
            cout << "\nYour Balance = " << Client.AccountBalance;
        }
    }
};

