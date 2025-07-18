#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsString.h"
#include <vector>
#include <iomanip>
#include <fstream>

class clsTransferListScreen:protected clsScreen
{
private:

    static void _PrintRecordTransferLog(clsBankClient::stTransferLog TransferLog)
    {
        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLog.DateTime;
        cout << "| " << setw(8) << left << TransferLog.SourceAcct;
        cout << "| " << setw(8) << left << TransferLog.DectinationAcct;
        cout << "| " << setw(10) << left << TransferLog.Amount;
        cout << "| " << setw(10) << left << TransferLog.sourceBalance;
        cout << "| " << setw(10) << left << TransferLog.DectinationBalance;
        cout << "| " << setw(8) << left << TransferLog.Users;
    }


public:

    static void ShowRegisterLoginList()
    {
        vector <clsBankClient::stTransferLog> vClient = clsBankClient::GetTransferLogList();

        string Title = "\t Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vClient.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vClient.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankClient::stTransferLog Client : vClient)
            {

                _PrintRecordTransferLog(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }


};

