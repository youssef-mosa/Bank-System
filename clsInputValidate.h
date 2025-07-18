#pragma once
#pragma warning(disable: 4996)
#include<iostream>
#include <ctype.h>
#include "clsDate.h";

template<class T>
class clsInputValidate
{
public:
	static T IsNumberBetween(int choosseNumber, int Number1, int Number2)
	{
		return choosseNumber >= Number1 && choosseNumber <= Number2 ? true : false;
	}

	static T IsNumberBetween(short choosseNumber, short Number1, short Number2)
	{
		return choosseNumber >= Number1 && choosseNumber <= Number2 ? true : false;
	}

	static T IsNumberBetween(float choosseNumber, float Number1, float Number2)
	{
		return choosseNumber >= Number1 && choosseNumber <= Number2 ? true : false;
	}

	static T IsNumberBetween(double choosseNumber, double Number1, double Number2)
	{
		return choosseNumber >= Number1 && choosseNumber <= Number2 ? true : false;
	}

	static T IsDateBetween(clsDate D, clsDate From, clsDate To)
	{
		return ( (D.IsDateAfterDate2(From) || D.IsDateEquleDate2(From))
			&& (D.IsDateBeforDate2(To) || D.IsDateEquleDate2(To)) 
			|| (D.IsDateAfterDate2(To) || D.IsDateEquleDate2(To))
			&& (D.IsDateBeforDate2(From) || D.IsDateEquleDate2(From)));
	}

	static T IsNumber(string S1)
	{
		for (char C : S1)
		{
			if (!isdigit(C))
				return false;
		}
		return true;
	}

	static T IsDoubleNumber(string S1)
	{
		for (int i = 1; i <= S1.length(); i++)
		{
			if (S1[i] == '.')
			{
				return true;
			}
		}
		return false;
	}

	static T ReadIntNumber(string ErrorMassege = "Invaild Number, Enter again : \n")
	{
		int Number ;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMassege;
		}
		return Number;
	}

	static T ReadIntNumberBetween(int N1, int N2, string ErrorMassege = "Invaild Number, Enter again : \n")
	{
		int N = ReadIntNumber();
		while (!IsNumberBetween(N, N1, N2))
		{
			cout << ErrorMassege;
			N = ReadIntNumber();
		}
		return N;
	}
	
	static T ReadFloatNumber(string ErrorMassege = "Invaild Number, Enter again : \n")
	{
		float Number ;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMassege;
		}
		return Number;
	}

	static T ReadFloatNumberBetween(float N1, float N2, string ErrorMassege = "Invaild Number, Enter again : \n")
	{
		float N = ReadIntNumber();
		while (!IsNumberBetween(N, N1, N2))
		{
			cout << ErrorMassege;
			N = ReadIntNumber();
		}
		return N;
	}

	static T ReadDblNumber(string ErrorMassege = "Invaild Number, Enter again : \n")
	{
		double Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMassege;
		}
		return Number;
	}

	static T ReadDblNumberBetween(double N1, double N2, string ErrorMassege = "Invaild Number, Enter again : \n")
	{
		double N = ReadDblNumber();
		while (!IsNumberBetween(N, N1, N2))
		{
			cout << ErrorMassege;
			N = ReadDblNumber();
		}
		return N;
	}

	static T IsVaildDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static T ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}

};

