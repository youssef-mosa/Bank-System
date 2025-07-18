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

class clsClientListScreen:protected clsScreen
{
private:
   static void PrintClientRecordLine(clsBankClient Client)
    {
       cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
       cout << "| " << setw(20) << left << Client.FullName();
       cout << "| " << setw(12) << left << Client.Phone;
       cout << "| " << setw(20) << left << Client.Email;
       cout << "| " << setw(10) << left << Client.PinCode;
       cout << "| " << setw(12) << left << Client.AccountBalance;

    }


public:
   static void ShowClientList()
    {
       if (!CheckAccessRight(clsUsers::enperimission::PShowclintlist))
       {
           return;
       }

        vector <clsBankClient> vClient = clsBankClient::GetClientList();

        string Titel = "\tClient List Screen";
        string SubTitel = "\t(" + to_string(vClient.size()) + ")Client(s)";
        _DrawScreenHeader(Titel, SubTitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClient.size() == 0)
            cout << "\t\t\t\tNo Clients Avalible In The System!";
        else

            for (clsBankClient Sclint : vClient)
            {
                PrintClientRecordLine(Sclint);
                cout << endl;
            }
        cout << "\n---------------------------------------------------------";
        cout << "-------------------------------------------------------\n";

    }


};

