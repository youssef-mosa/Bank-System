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

class clsAddUserScreen:protected clsScreen
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
        cout << "\nShow Login Register List ? y/n? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            permission += clsUsers::enperimission::PLodinRegister;
        }

        return permission;
    }

public:
    static void AddNewUser()
    {
        _DrawScreenHeader("\tAdd New User Screen");

        string UserName = "";
        cout << "Please Enter UserName :";
        UserName = clsInputValidate<string>::ReadString();

        while (clsUsers::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already used , Enter another one : ";
            UserName = clsInputValidate<string>::ReadString();
        }

        clsUsers NewUser = clsUsers::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUsers::enSaveResult SaveResult;
        SaveResult = NewUser.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSuccessfully:
            cout << "\n\nAdd New User successfully :-)\n";
            _Print(NewUser);
            break;
        case clsBankClient::enSaveResult::svFaildEmpty:
            cout << "\nErroe Add User Faild beacuse is Empty!!\n";
            break;

        case clsBankClient::enSaveResult::svFaildAccountNumberExist:
            cout << "\nError account was not saved because User Name is used!\n";
            break;
        }
    }

};

