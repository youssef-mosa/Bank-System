#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>


using namespace std;

class clsBankClient:public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance = 0;
	bool _MarkForDelete = false;

	struct stTransferLog;
	static clsBankClient _ConvertLineToClientObject(string line, string delim = "#//#")
	{
		vector<string> vClientDate;
		vClientDate = clsString::Split(line, delim);

		if (vClientDate.size() < 7)
		{
			return _GetEmptyClientOpject();
		}
		
		return clsBankClient(enMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2], vClientDate[3]
			, vClientDate[4], vClientDate[5], stod(vClientDate[6]));
	}

	static stTransferLog _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLog TransferLogRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		TransferLogRecord.DateTime = LoginRegisterDataLine[0];
		TransferLogRecord.SourceAcct = LoginRegisterDataLine[1];
		TransferLogRecord.DectinationAcct = LoginRegisterDataLine[2];
		TransferLogRecord.Amount = stod(LoginRegisterDataLine[3]);
		TransferLogRecord.sourceBalance = stod(LoginRegisterDataLine[4]);
		TransferLogRecord.DectinationBalance = stod(LoginRegisterDataLine[5]);
		TransferLogRecord.Users = LoginRegisterDataLine[6];

		return TransferLogRecord;

	}

	static clsBankClient _GetEmptyClientOpject()
	{	
		return clsBankClient(enMode::EmptyMode, "", "", "","", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string delim = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + delim;
		stClientRecord += Client.LastName + delim;
		stClientRecord += Client.Email + delim;
		stClientRecord += Client.Phone + delim;
		stClientRecord += Client.AccountNumber() + delim;
		stClientRecord += Client.PinCode + delim;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}

	static vector<clsBankClient> _LoadClientDateFromFile()
	{
		vector<clsBankClient> vclint;
		fstream Myfile;
		Myfile.open("Clients.txt", ios::in);
		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				vclint.push_back(Client);
			}
			Myfile.close();
		}
		return vclint;
	}

	static void _SaveClientDateToFile(vector<clsBankClient> vclint)
	{
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out);
		string DateLine;
		if (Myfile.is_open())
		{
			for (clsBankClient& c : vclint)
			{
				if (c._MarkForDelete == false)
				{
					DateLine = _ConvertClientObjectToLine(c);
					Myfile << DateLine << endl;
				}
			}
			Myfile.close();
		}
	}

	void _UpDate()
	{
		vector<clsBankClient> _vClientDate = _LoadClientDateFromFile();

		for (clsBankClient& C : _vClientDate)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDateToFile(_vClientDate);
	}

	void _AddNew()
	{
		_AddDateLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDateLineToFile(string DateLine)
	{
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out | ios::app);
		if (Myfile.is_open())
		{
			Myfile << DateLine << endl;
			Myfile.close();
		}
	}

	string _PrepareLogInRecordTranfer(clsBankClient DestinationClient,double Amount ,string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += _AccountNumber + Seperator;
		LoginRecord += DestinationClient.AccountNumber() + Seperator;
		LoginRecord += to_string(Amount) + Seperator;
		LoginRecord += to_string(_AccountBalance) + Seperator;
		LoginRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		LoginRecord +=CurrentUser.UserName;
		return LoginRecord;
	}

	void  _TransferLog(clsBankClient DestinationClient, double Amount)
	{
		string DateLine = _PrepareLogInRecordTranfer(DestinationClient, Amount);

		fstream Myfile;
		Myfile.open("TransferLog.txt", ios::out | ios::app);
		if (Myfile.is_open())
		{
			Myfile << DateLine << endl;
			Myfile.close();
		}
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string AccountNumber, string PinCode, float AccountBalance) :
		     clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLog
	{
		string DateTime;
		string SourceAcct;
		string DectinationAcct;
		double Amount;
		float sourceBalance;
		float DectinationBalance;
		string Users;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDelet()
	{
		return _MarkForDelete;
	}

	//Get
	string AccountNumber()
	{
		return _AccountNumber;
	}

	//set
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	//Get
	string GetPinCode()
	{
		return _PinCode ;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;

	//set
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	//Get
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	//No UI in class Main Code
	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName     : " << FirstName;
		cout << "\nLastName      : " << LastName;
		cout << "\nFull Name     : " << FullName();
		cout << "\nEmail         : " << Email;
		cout << "\nPhone         : " << Phone;
		cout << "\nAccountNumber : " << _AccountNumber;
		cout << "\nPinCode       : " << _PinCode;
		cout << "\nAccountBalance: " << _AccountBalance;
		cout << "\n___________________\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vclint;
		fstream Myfile;
		Myfile.open("Clients.txt", ios::in);

		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.AccountNumber() == AccountNumber)
				{
					Myfile.close();
					return Client;
				}
				vclint.push_back(Client);
			}
			Myfile.close();
		}
		return _GetEmptyClientOpject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vclint;
		fstream Myfile;
		Myfile.open("Clients.txt", ios::in);

		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					Myfile.close();
					return Client;
				}
				vclint.push_back(Client);
			}
			Myfile.close();
		}
		return _GetEmptyClientOpject();
	}

	enum enSaveResult { svFaildEmpty = 0, svSuccessfully = 1 ,svFaildAccountNumberExist = 2 };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResult::svFaildEmpty;

		case enMode::UpdateMode:

			_UpDate();
			return enSaveResult::svSuccessfully;

		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFaildAccountNumberExist;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccessfully;
			}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	
	bool Delete()
	{
		vector<clsBankClient> vClient = _LoadClientDateFromFile();

		for (clsBankClient &C : vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientDateToFile(vClient);

		*this = _GetEmptyClientOpject();
		
		return true;
	}

	static vector<clsBankClient> GetClientList()
	{
		return _LoadClientDateFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient>vClient = GetClientList();
		double GetTotalBalances = 0;
		for (clsBankClient C : vClient)
		{
			GetTotalBalances += C.AccountBalance;
		}
		return GetTotalBalances;
	}

	void Deposit(double Amount)
	{
		 _AccountBalance += Amount;
		 Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}

	bool Tranfer(double Amount, clsBankClient &DestinationClient)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		else
		{
			Withdraw(Amount);
			DestinationClient.Deposit(Amount);
			_TransferLog(DestinationClient, Amount);
			return true;
		}
	}

	static vector<stTransferLog> GetTransferLogList()
	{
		vector<stTransferLog> vclint;
		fstream Myfile;
		Myfile.open("TransferLog.txt", ios::in);
		if (Myfile.is_open())
		{
			string line;
			stTransferLog clint;
			while (getline(Myfile, line))
			{
				clint = _ConvertTransferLogLineToRecord(line);
				vclint.push_back(clint);
			}
			Myfile.close();
		}
		return vclint;
	}

	
};