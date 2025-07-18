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

class clsAddClientScreen:protected clsScreen
{
private:
   static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nFirstName :";
        Client.FirstName = clsInputValidate<string>::ReadString();
        cout << "LastName :";
        Client.LastName = clsInputValidate<string>::ReadString();
        cout << "Email :";
        Client.Email = clsInputValidate<string>::ReadString();
        cout << "Phone :";
        Client.Phone = clsInputValidate<string>::ReadString();
        cout << "PinCode :";
        Client.PinCode = clsInputValidate<string>::ReadString();
        cout << "AccountBalance :";
        Client.AccountBalance = clsInputValidate<float>::ReadFloatNumber();
    }

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
    static void AddNewClient()
    {
        if (!CheckAccessRight(clsUsers::enperimission::PAddnewclintscrren))
        {
            return;
        }
        _DrawScreenHeader("\tAdd New Client Screen");

        string AccountNumber = "";
        cout << "Please Enter AccountNumber :";
        AccountNumber = clsInputValidate<string>::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccountNumber Is Already used , Enter another one : ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResult SaveResult;
        SaveResult = NewClient.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSuccessfully:
            cout << "\n\nAdd New Client successfully :-)\n";
            clsAddClientScreen::_Print(NewClient);
            break;
        case clsBankClient::enSaveResult::svFaildEmpty:
            cout << "\nErroe Update Client Faild beacuse is Empty!!\n";
            break;

        case clsBankClient::enSaveResult::svFaildAccountNumberExist:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
    }



};

