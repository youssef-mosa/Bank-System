#pragma once
#include <iostream>
#include<iomanip>
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <vector>

class clsTotalBalanceScreen:protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(8) << left << "  " << "|" << left <<  setw(15) << Client.AccountNumber();
        cout <<"|" << left <<  setw(40) << Client.FullName();
        cout << "  " << "|" << left <<  setw(12) << Client.AccountBalance;
    }

public:
    static void ShowClientBalanceList()
    {


        vector <clsBankClient> vClient = clsBankClient::GetClientList();

        string Titel = "\tClient List Screen";
        string SubTitel = "\t(" + to_string(vClient.size()) + ")Client(s)";
        _DrawScreenHeader(Titel, SubTitel);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        double TotalBalances = clsBankClient::GetTotalBalances();
        if (vClient.size() == 0)
            cout << "\t\t\t\tNo Clients Avalible In The System!";
        else

            for (clsBankClient Sclint : vClient)
            {
                _PrintClientRecordBalanceLine(Sclint);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n---------------------------------------------------------";
        cout << "-------------------------------------------------------\n";
        cout << "\t\t\t\t\tTotalBalance = " << TotalBalances << endl;
        cout << "\t\t\t\t\t ( " << clsUtil::NumberToText(TotalBalances)<<")" << endl;

    }
};

