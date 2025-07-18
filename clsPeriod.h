#pragma once
#include<iostream>
#include"clsDate.h";

class clsPeriod
{
public:
	clsDate StartDate;
	clsDate EndDate;

	clsPeriod(clsDate StartDate, clsDate DateTo)
	{
		this->StartDate=StartDate;
		this->EndDate = DateTo;
	}

	static bool IsOverLapPeriod(clsPeriod Period1, clsPeriod Period2)
	{
		if (clsDate::ComparDate(Period2.EndDate, Period1.StartDate) == clsDate::enDateReturn::Before
			|| (clsDate::ComparDate(Period2.StartDate, Period1.EndDate) == clsDate::enDateReturn::After))
			return false;

		else
			return true;
	}

	bool IsOverLapPeriod( clsPeriod Period2)
	{
		return IsOverLapPeriod(*this, Period2);
	}

	void Print()
	{
		cout << "Start Date :";
		StartDate.Print();

		cout << "End Date :";
		EndDate.Print();
	}


};

