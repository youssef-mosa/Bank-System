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

class clsDeleteUserScreen:protected clsScreen
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
    static void DeletUser()
    {
        _DrawScreenHeader("\tDelete User Screen");
        string UserName = "";
        cout << "Please Enter UserName :";
        UserName = clsInputValidate<string>::ReadString();

        while (!clsUsers::IsUserExist(UserName))
        {
            cout << "\nUserName Not Found , Enter another one : ";
            UserName = clsInputValidate<string>::ReadString();
        }

        clsUsers User = clsUsers::Find(UserName);
        _Print(User);

        char Answer = 'n';
        cout << "\nAre you sure you want delet this User?y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (User.Delete())
            {
                cout << "\nDelete User Seccessfully :-)\n";
                _Print(User);
            }
            else
            {
                cout << "\nError User Was Not Delete\n";
            }
        }
    }

};

