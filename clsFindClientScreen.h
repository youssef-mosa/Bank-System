#pragma once
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

class clsFindClientScreen:clsScreen
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
public:

    static void FindClient()
    {
        if (!CheckAccessRight(clsUsers::enperimission::PFindclintscreen))
        {
            return;
        }
        _DrawScreenHeader("\tFind Client Info Screen");
        string AccountNumber = "";
        cout << "Please Enter AccountNumber :";
        AccountNumber = clsInputValidate<string>::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccountNumber Not Found , Enter another one : ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);


        if (!Client.IsEmpty())
            cout << "\nClient Found :-)\n";
        else
            cout << "\nCilent Not Found:-(\n";

        _Print(Client);

    }
};

