#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsUsers.h"
#include "clsString.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include "clsScreen.h"

class clsRegristerLogin:protected clsScreen
{
private:

    static void _PrintRecordLoginRegister(clsUsers::stRegisterLogin RegisterLogin)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << RegisterLogin.DateTime;
        cout << "| " << setw(20) << left << RegisterLogin.UserName;
        cout << "| " << setw(20) << left << RegisterLogin.Password;
        cout << "| " << setw(10) << left << RegisterLogin.Permission;
    }


public:

    static void ShowRegisterLoginList()
    {
        if (!CheckAccessRight(clsUsers::enperimission::PLodinRegister))
        {
            return;
        }
        vector <clsUsers::stRegisterLogin> vUsers = clsUsers::GetLogInRegisterList();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUsers::stRegisterLogin User : vUsers)
            {

                _PrintRecordLoginRegister(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }



};

