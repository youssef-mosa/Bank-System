#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsDate.h"
#include "Global.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>


using namespace std;

class clsUsers :public clsPerson
{
	
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	 string _UserName;
	 string _Password;
	 int _Permissions;
	 bool _MarkForDelete = false;

	struct stRegisterLogin;

	static clsUsers _ConvertLineToUserObject(string line, string delim = "#//#")
	{
		vector<string> vClientDate;
		vClientDate = clsString::Split(line, delim);

		if (vClientDate.size() < 7)
		{
			return _GetEmptyCurrencyOpject();
		}

		return clsUsers(enMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2], vClientDate[3]
			, vClientDate[4], clsUtil::DecryptText(vClientDate[5]), stoi(vClientDate[6]));
	}

	static stRegisterLogin _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stRegisterLogin LoginRegisterRecord;
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permission = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;

	}
	
	static clsUsers _GetEmptyCurrencyOpject()
	{
		return clsUsers(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserObjectToLine(clsUsers User, string delim = "#//#")
	{
		string stUserRecord = "";
		stUserRecord += User.FirstName + delim;
		stUserRecord += User.LastName + delim;
		stUserRecord += User.Email + delim;
		stUserRecord += User.Phone + delim;
		stUserRecord += User.UserName + delim;
		stUserRecord += clsUtil::EncryptText(User.Password) + delim;
		stUserRecord += to_string(User.Permissions);
		return stUserRecord;
	}

	static vector<clsUsers> _LoadUserDateFromFile()
	{
		vector<clsUsers> vclint;
		fstream Myfile;
		Myfile.open("Users.txt", ios::in);
		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsUsers Client = _ConvertLineToUserObject(line);
				vclint.push_back(Client);
			}
			Myfile.close();
		}
		return vclint;
	}

	static void _SaveUserDateToFile(vector<clsUsers> vclint)
	{
		fstream Myfile;
		Myfile.open("Users.txt", ios::out);
		string DateLine;
		if (Myfile.is_open())
		{
			for (clsUsers& c : vclint)
			{
				if (c._MarkForDelete == false)
				{
					DateLine = _ConvertUserObjectToLine(c);
					Myfile << DateLine << endl;
				}
			}
			Myfile.close();
		}
	}

	void _UpDate()
	{
		vector<clsUsers> _vClientDate = _LoadUserDateFromFile();

		for (clsUsers& U : _vClientDate)
		{
			if (U.UserName == GetUserName())
			{
				U = *this;
				break;
			}
		}
		_SaveUserDateToFile(_vClientDate);
	}

	void _AddNew()
	{
		_AddDateLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDateLineToFile(string DateLine)
	{
		fstream Myfile;
		Myfile.open("Users.txt", ios::out | ios::app);
		if (Myfile.is_open())
		{
			Myfile << DateLine << endl;
			Myfile.close();
		}
	}

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}


public:
	
	enum enperimission
	{
		Pfullaccess = -1,PShowclintlist = 1,PAddnewclintscrren = 2,PDeletclintscreen = 4,
		PUpdateclintscreen = 8, PFindclintscreen = 16,PTransaction = 32,PMangeUser = 64 , 
		PLodinRegister = 128
	};

	struct stRegisterLogin
	{
		string DateTime ;
		string UserName ;
		string Password ;
		int Permission ;
	};

	clsUsers(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string UserName, string Password,int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}


	bool IsEmpty() 
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDelet() 
	{
		return _MarkForDelete;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	//Get
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName))string UserName;
	//set
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	//Get
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	//set
	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	//Get
	int GetPermissions() const
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;

	static clsUsers Find(string UserName)
	{
		vector<clsUsers> vclint;
		fstream Myfile;
		Myfile.open("Users.txt", ios::in);

		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsUsers User = _ConvertLineToUserObject(line);
				if (User.UserName == UserName)
				{
					Myfile.close();
					return User;
				}
				vclint.push_back(User);
			}
			Myfile.close();
		}
		return _GetEmptyCurrencyOpject();
	}

	static clsUsers Find(string UserName, string Password)
	{
		vector<clsUsers> vclint;
		fstream Myfile;
		Myfile.open("Users.txt", ios::in);

		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsUsers Client = _ConvertLineToUserObject(line);
				if (Client.UserName == UserName && Client.Password == Password)
				{
					Myfile.close();
					return Client;
				}
				vclint.push_back(Client);
			}
			Myfile.close();
		}
		return _GetEmptyCurrencyOpject();
	}

	enum enSaveResult { svFaildEmpty = 0, svSuccessfully = 1, svFaildAccountNumberExist = 2 };

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
			if (clsUsers::IsUserExist(_UserName))
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

	static bool IsUserExist(string AccountNumber)
	{
		clsUsers User = Find(AccountNumber);
		return (!User.IsEmpty());
	}

	static clsUsers GetAddNewUserObject(string UserName)
	{
		return clsUsers(enMode::AddNewMode, "", "", "", "", UserName,"", 0);
	}

	bool Delete()
	{
		vector<clsUsers> vClient = _LoadUserDateFromFile();

		for (clsUsers& C : vClient)
		{
			if (C.UserName == _UserName)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveUserDateToFile(vClient);

		*this = _GetEmptyCurrencyOpject();

		return true;
	}

	static vector<clsUsers> GetUserList()
	{
		return _LoadUserDateFromFile();
	}

	bool CheckAccessPermission(enperimission Permission) const
	{
		if (this->Permissions == enperimission::Pfullaccess)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegristerLogin()
	{
		string DateLine = _PrepareLogInRecord();

		fstream Myfile;
		Myfile.open("Regrist.txt", ios::out | ios::app);
		if (Myfile.is_open())
		{
			Myfile << DateLine << endl;
			Myfile.close();
		}
	}

	static vector<stRegisterLogin> GetLogInRegisterList()
	{
		vector<stRegisterLogin> vclint;
		fstream Myfile;
		Myfile.open("Regrist.txt", ios::in);
		if (Myfile.is_open())
		{
			string line;
			stRegisterLogin clint;
			while (getline(Myfile, line))
			{
				clint = _ConvertLoginRegisterLineToRecord(line);
				vclint.push_back(clint);
			}
			Myfile.close();
		}
		return vclint;
	}




};

