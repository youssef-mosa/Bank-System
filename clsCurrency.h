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
class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, };
	enMode _Mode;

	  string _Country;
	  string _CurrencyCode;
	  string _CurrencyName;
	  float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string line, string delim = "#//#")
	{
		vector<string> vCurrencyDate;
		vCurrencyDate = clsString::Split(line, delim);

		if (vCurrencyDate.size() < 4)
		{
			return _GetEmptyCurrencyOpject();
		}

		return clsCurrency(enMode::UpdateMode, vCurrencyDate[0], vCurrencyDate[1], vCurrencyDate[2]
			,stod(vCurrencyDate[3]));
	}

	static clsCurrency _GetEmptyCurrencyOpject()
	{
		return clsCurrency(enMode::EmptyMode, "", "","", 0);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string delim = "#//#")
	{
		string stUserRecord = "";
		stUserRecord += Currency._Country + delim;
		stUserRecord += Currency._CurrencyCode+ delim;
		stUserRecord += Currency._CurrencyName + delim;
		stUserRecord += to_string(Currency._Rate) ;
		return stUserRecord;
	}

	static vector<clsCurrency> _LoadCurrenciesDateFromFile()
	{
		vector<clsCurrency> vCurrency;
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::in);
		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				vCurrency.push_back(Currency);
			}
			Myfile.close();
		}
		return vCurrency;
	}

	static void _SaveCurrencyDateToFile(vector<clsCurrency> vCurrency)
	{
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::out);
		string DateLine;
		if (Myfile.is_open())
		{
			for (clsCurrency& c : vCurrency)
			{
				DateLine = _ConvertCurrencyObjectToLine(c);
				Myfile << DateLine << endl;
				
			}
			Myfile.close();
		}
	}

	void _UpDate()
	{
		vector<clsCurrency> _vCurrencyDate = _LoadCurrenciesDateFromFile();

		for (clsCurrency& C : _vCurrencyDate)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDateToFile(_vCurrencyDate);
	}

public:
	clsCurrency(enMode Mode,string Country,string CurrencyCode, string CurrencyName,float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
		
	}

	clsCurrency()
	{
		_Mode = enMode::EmptyMode;
		_Country = "";
		_CurrencyCode = "";
		_CurrencyName = "";
		_Rate = 0;
	}
	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrenciesDateFromFile();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_UpDate();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsString::UpperAllString(Code);

		vector<clsCurrency> vCurrency;
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::in);

		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				if (Currency.CurrencyCode() == Code)
				{
					Myfile.close();
					return Currency;
				}
				vCurrency.push_back(Currency);
			}
			Myfile.close();
		}
		return _GetEmptyCurrencyOpject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperFirstLetterOfEachWord(Country);
		vector<clsCurrency> vCurrency;
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::in);

		if (Myfile.is_open())
		{
			string line;
			while (getline(Myfile, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				if (Currency.Country() == Country)
				{
					Myfile.close();
					return Currency;
				}
				vCurrency.push_back(Currency);
			}
			Myfile.close();
		}
		return _GetEmptyCurrencyOpject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDateFromFile();
	}

    float ConvertToUSD(float Amount)
	{
		return (float) (Amount / Rate());
	}

    float ConvertFromCurrencyToCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());

	}
	


};

