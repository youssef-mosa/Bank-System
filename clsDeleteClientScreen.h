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

class clsDeleteClientScreen:protected clsScreen
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
    static void DeletClient()
    {
        if (!CheckAccessRight(clsUsers::enperimission::PDeletclintscreen))
        {
            return;
        }
        _DrawScreenHeader("\tDelete Client Screen");
        string AccountNumber = "";
        cout << "Please Enter AccountNumber :";
        AccountNumber = clsInputValidate<string>::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccountNumber Not Found , Enter another one : ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);

        char Answer = 'n';
        cout << "\nAre you sure you want delet this Account?y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nDelete Client Seccessfully :-)\n";
                _Print(Client);
            }
            else
            {
                cout << "\nError Client Was Not Delete\n";
            }
        }

    
    }

};

