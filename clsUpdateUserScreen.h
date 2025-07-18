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

class clsUpdateUserScreen:protected clsScreen
{
private:
    static void _ReadUserInfo(clsUsers& User)
    {
        cout << "\nFirstName :";
        User.FirstName = clsInputValidate<string>::ReadString();
        cout << "\nLastName :";
        User.LastName = clsInputValidate<string>::ReadString();
        cout << "\nEmail :";
        User.Email = clsInputValidate<string>::ReadString();
        cout << "\nPhone :";
        User.Phone = clsInputValidate<string>::ReadString();
        cout << "\nPassword :";
        User.Password = clsInputValidate<string>::ReadString();
        cout << "\nPermission :";
        User.Permissions = _PermissionAccess();
    }

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

    static int _PermissionAccess()
    {
        int permission = 0;
        char Answer = 'n';
        cout << "\nDo you want to give Full Access? y/n? ";
        cin >> Answer;
        if ((Answer == 'Y' || Answer == 'y'))
        {
            return -1;
        }
        cout << "\nDo you want give access to :\n";
        cout << "\nShow Clint List ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PShowclintlist;
        }
        cout << "\nAdd New Clint ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PAddnewclintscrren;
        }
        cout << "\nDelete Clint ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PDeletclintscreen;
        }
        cout << "\nUpdate Clint ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PUpdateclintscreen;
        }
        cout << "\nFind Clint ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PFindclintscreen;
        }
        cout << "\nTransaction ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PTransaction;
        }
        cout << "\nManger Users ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PMangeUser;
        }

        return permission;
    }

public:
    static void UpdateUser()
    {
        _DrawScreenHeader("\tUpdate User Info Screen");
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

        cout << "\n\n Update User info :";
        cout << "\n_____________________________";

        _ReadUserInfo(User);

        clsUsers::enSaveResult SaveResult;
        SaveResult = User.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSuccessfully:
            cout << "\n\nUpdate User successfully :-)\n";
            _Print(User);
            break;
        case clsBankClient::enSaveResult::svFaildEmpty:
            cout << "\nErroe Update User Faild beacuse is Empty!!\n";
            break;
        }
    }
};

