#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsMainScreen.h"
#include "clsUsers.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsTime.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\n\t\t\t\t\t  ______________________________________";
        cout << "\n\n\t\t\t\t\t" << Title;
        if (SubTitle != "")
        {
            cout << clsUtil::Tabs(4) << "\n\t\t\t\t\t" << SubTitle;
        }
        cout << "\n\t\t\t\t\t  ______________________________________\n\n";

        cout << "\t\t\t\t\t   User :" <<CurrentUser.UserName ;
        cout << "\t\tTime :" << clsTime::TimeToString(clsTime());
        cout << "\n\t\t\t\t\t\t\t\tDate :" << clsDate::DateToString(clsDate()) <<"\n";
        cout << "\t\t\t\t\t  ______________________________________\n\n";
    }


    static bool CheckAccessRight(clsUsers::enperimission Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t------------------------------------\n";
            cout << "\n\t\t\t\t\tAccess Denied!,Contact Your Admin.";
            cout << "\n\n\t\t\t\t\t------------------------------------\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};

