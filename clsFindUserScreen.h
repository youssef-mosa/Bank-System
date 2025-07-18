#pragma once
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

class clsFindUserScreen:protected clsScreen
{
private:
    static void _Print(clsUsers User)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName     : " << User.FirstName;
        cout << "\nLastName      : " << User.LastName;
        cout << "\nFull Name     : " << User.FullName();
        cout << "\nEmail         : " << User.Email;
        cout << "\nPhone         : " << User.Phone;
        cout << "\nUserName      : " << User.UserName;
        cout << "\nPassword      : " << User.Password;
        cout << "\nPermissions   : " << User.Permissions;
        cout << "\n___________________\n";
    }

public:
    static void FindUser()
    {
        _DrawScreenHeader("\tFind User Info Screen");
        string UserName = "";
        cout << "Please Enter UserName :";
        UserName = clsInputValidate<string>::ReadString();

        while (!clsUsers::IsUserExist(UserName))
        {
            cout << "\nUserName Not Found , Enter another one : ";
            UserName = clsInputValidate<string>::ReadString();
        }

        clsUsers User = clsUsers::Find(UserName);


        if (!User.IsEmpty())
            cout << "\nUser Found :-)\n";
        else
            cout << "\nUser Not Found:-(\n";

        _Print(User);

    }
};

