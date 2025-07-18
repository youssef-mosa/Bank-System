#pragma once
#pragma warning(disable: 4996)
#include<iostream>
#include<vector>
#include<cmath>
#include <string>
#include"clsString.h";

using namespace std;

class clsDate
{
private: 
	short _Day;
    short _Month;
	short _Year;
public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
   
	clsDate(string Date)
	{
		clsString Cstring;
		vector<string>Vdtae = Cstring.Split(Date, "/");

		_Day = stoi(Vdtae[0]);
		_Month = stoi(Vdtae[1]);
		_Year = stoi(Vdtae[2]);
	}

	clsDate(short Day, short Month,short Year)
	{
		_Year = Year;
		_Month = Month;
		_Day = Day;
	}

	clsDate(short NumberOrderDays, short Year)
	{
		clsDate date = GetDateFromBegginingYear(NumberOrderDays, Year);

		_Year = date.Year;
		_Month = date.Month;
		_Day = date.Day;
	}

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear() 
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear))short Year;

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth() 
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth))short Month;

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay() 
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay))short Day;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate()
	{
		//StDate Date;
		time_t t = time(0);
		tm* now = localtime(&t);
		short Year, Month, Day;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		return clsDate(Day,Month,Year);
	}

	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	static bool Is_Leep_Year(int Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool Is_Leep_Year() const
	{
		return Is_Leep_Year(_Year);
	}

	 static bool IsValidDate(clsDate Date)
     {
          return (Date.Month >= 1 && Date.Month <= 12) &&
             (Date.Day >= 1 && Date.Day <= NumberofdaysinMonth(Date.Year, Date.Month));
     }

	 bool IsValidDate()
	 {
		 return IsValidDate(*this);
	 }

	static short NumberofdaysinMonth(short Year, short Month)
	{
		if (Month < 1 || Month>12)
			return 0;
		int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (Is_Leep_Year(Year) ? 29 : 28) : arr[Month - 1];
	}

	short NumberofdaysinMonth()
	{
		return NumberofdaysinMonth(_Year, _Month);
	}

	static short Number_of_days_from_begining_the_Year(short Year, short Month, short Day)
	{
		short Sum = 0;
		for (int i = 1; i <= Month - 1; i++)
		{
			Sum += NumberofdaysinMonth(Year, i);

		}
		Sum += Day;
		return Sum;
	}

	short Number_of_days_from_begining_the_Year()
	{
		return Number_of_days_from_begining_the_Year(_Year, _Month, _Day);
	}
	
	static string Monthname(short Month)
	{
		string arr[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug" ,"Sep" ,"Oct", "Nov", "Dec" };
		return arr[Month - 1];
	}

	string Monthname()
	{
		return Monthname(_Month);
	}

	static string Dayname(short Dayofweekorder)
	{
		string arr[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arr[Dayofweekorder];
	}

	string Dayname()
	{
		return Dayname(_Day);
	}

	static short DayOfWeekorder(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
	}

	short DayOfWeekorder()
	{
		return DayOfWeekorder(_Day, _Month, _Year);
	}

	static void PrintMonthCalander(int Year, int Month)
	{
		short current = DayOfWeekorder(Year, Month, 1);

		short days = NumberofdaysinMonth(Year, Month);

		printf("\n ___________________%s ___________________\n\n"
			, Monthname(Month).c_str());

		printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;
		for (i = 0; i < current; i++)
		{
			printf("     ");
		}
		for (int j = 1; j <= days; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n __________________________________________");
	}

	void PrintMonthCalander()
	{
		PrintMonthCalander(_Year, _Month);
	}

	static void PrintAllCalanderYear(short Year)
	{
		printf("  _________________________________________\n\n");
		printf(" \t\tCalender - %d\n", Year);
		printf("  _________________________________________\n\n");
		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalander(Year, i);
		}
		return;
	}

	void PrintAllCalanderYear()
	{
		PrintAllCalanderYear(_Year);
	}

	static short DaysInYear(short Year)
	{
		return Is_Leep_Year(Year) ? 366 : 365;
	}

	short DaysInYear()
	{
		return DaysInYear(_Year);
	}

	static short HoursOfYear(short Year)
	{
		return  DaysInYear(Year) * 24;
	}

	short HoursOfYear()
	{
		return HoursOfYear(_Year);
	}

	static short MinutesOfYear(short Year)
	{
		return HoursOfYear(Year) * 60;
	}

	short MinutesOfYear()
	{
		return MinutesOfYear(_Year);
	}

	static short Secoundofyear(short Year)
	{
		return MinutesOfYear(Year) * 60;
	}

	short Secoundofyear()
	{
		return Secoundofyear(_Year);
	}

	static short HoursOfMonth(short Year, short Month)
	{
		return  NumberofdaysinMonth(Year, Month) * 24;
	}

	short HoursOfMonth()
	{
		return  HoursOfMonth(_Year, _Month);
	}

	static short MinutesOfMonth(short Year, short Month)
	{
		return HoursOfMonth(Year, Month) * 60;
	}

	short MinutesOfMonth()
	{
		return MinutesOfMonth(_Year, _Month);
	}

	static short SecoundOfMonth(short Year, short Month)
	{
		return MinutesOfMonth(Year, Month) * 60;
	}

	short SecoundOfMonth()
	{
		return SecoundOfMonth(_Year, _Month);
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	void AddDateDay(short Day)
	{
		short remaningdays = Day + Number_of_days_from_begining_the_Year(_Year, _Month, _Day);
		short OrderMonth = 0;
		_Month = 1;

		while (true)
		{
			OrderMonth = NumberofdaysinMonth(_Year,_Month);

			if (remaningdays > OrderMonth)
			{
				remaningdays -= OrderMonth;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = remaningdays;
				break;
			}
		}
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true :
			((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true
				: (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}

    bool IsDateBeforDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EquleDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ?
			((Date1._Day == Date2._Day) ? true : false) : false) : false;
	}

    bool IsDateEquleDate2(clsDate Date2)
	{
		return IsDate1EquleDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !(IsDate1BeforeDate2(Date1, Date2)|| IsDate1EquleDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumberofdaysinMonth(Date._Year, Date._Month));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate  AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Month))
			{
				Date._Day = 1;
				Date._Month = 1;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}

		}
		else
		{
			Date._Day++;
		}
		return Date;
	}

	void  AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static clsDate IncreaseDateByXDay(clsDate Date, short Xday)
	{
		for (int i = 1; i <= Xday; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDay( short Xday)
	{
		*this = IncreaseDateByXDay(*this, Xday);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeek(clsDate Date, short Xweek)
	{
		for (int i = 1; i <= Xweek; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeek(short Xweek)
	{
		*this = IncreaseDateByXWeek(*this, Xweek);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberDaysIncurrentMonth = NumberofdaysinMonth(Date.Year, Date.Month);
		if (Date.Day > NumberDaysIncurrentMonth)
		{
			Date.Day = NumberDaysIncurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(clsDate Date, short XMonth)
	{
		for (int i = 1; i <= XMonth; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonth(short XMonth)
	{
		*this = IncreaseDateByXMonth(*this, XMonth);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYear(clsDate Date, short XYear)
	{
		Date.Year += XYear;
		return Date;
	}

	void IncreaseDateByXYear(short XYear)
	{
		*this = IncreaseDateByXYear(*this, XYear);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		Date.Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecade(clsDate Date, short XDecade)
	{
		Date.Year += XDecade * 10;
		return Date;
	}

	void IncreaseDateByXDecade(short XDecade)
	{
		*this = IncreaseDateByXDecade(*this, XDecade);
	}

	static clsDate  IncreaseDateByOneCentury(clsDate Date)
	{
		Date.Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate  Date)
	{
		Date.Year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseOneDay(clsDate Date)
	{
		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{
				Date._Day = 31;
				Date._Month = 12;
				Date._Year--;
			}
			else
			{
				Date._Month--;
				Date._Day = NumberofdaysinMonth(Date._Year, Date._Month);
			}
		}
		else
		{
			Date._Day--;
		}
		return Date;
	}

	void DecreaseOneDay()
	{
		*this = DecreaseOneDay(*this);
	}

	static clsDate DecreaseDateByXDay(clsDate Date, short Xday)
	{
		for (int i = 1; i <= Xday; i++)
		{
			Date = DecreaseOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDay(short Xday)
	{
		*this = DecreaseDateByXDay(*this, Xday);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(clsDate Date, short Xweek)
	{
		for (int i = 1; i <= Xweek; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeek(short Xweek)
	{
		*this = DecreaseDateByXWeek(*this, Xweek);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		short NumberDaysIncurrentMonth = NumberofdaysinMonth(Date.Year, Date.Month);
		if (Date.Day > NumberDaysIncurrentMonth)
		{
			Date.Day = NumberDaysIncurrentMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonth(clsDate Date, short XMonth)
	{
		for (int i = 1; i <= XMonth; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonth(short XMonth)
	{
		*this = DecreaseDateByXMonth(*this,XMonth);
	}

	static clsDate DecreaseDateByoneYear(clsDate Date)
	{
		Date.Year--;
		return Date;
	}

	void DecreaseDateByoneYear()
	{
		*this = DecreaseDateByoneYear(*this);
	}

	static clsDate DecreaseDateByXYear(clsDate Date, short XYear)
	{
		Date.Year -= XYear;
		return Date;
	}

    void DecreaseDateByXYear(short XYear)
	{
		*this = DecreaseDateByXYear(*this, XYear);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		Date.Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecade(clsDate Date, short XDecade)
	{
		Date.Year -= XDecade * 10;
		return Date;
	}

	void DecreaseDateByXDecade(short XDecade)
	{
		*this = DecreaseDateByXDecade(*this, XDecade);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		Date.Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}

	static short IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeekorder(Date.Day,Date.Month,Date.Year) == 6) ;
	}

	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short Day = DayOfWeekorder(Date.Day, Date.Month, Date.Year);
		return (Day == 5 || Day == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekorder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate NumberofDays;
		NumberofDays.Day = NumberofdaysinMonth(Date.Year, Date.Month);
		NumberofDays.Month = Date.Month;
		NumberofDays.Year = Date.Year;
		return GetDifferenceInDays(Date, NumberofDays, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		clsDate NumberofDays;
		NumberofDays.Day = 31;
		NumberofDays.Month = 12;
		NumberofDays.Year = Date.Year;
		return GetDifferenceInDays(Date, NumberofDays, true);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short GetActualVactionDays(clsDate DateFrom, clsDate DateTo)
	{
		short Dayscount = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Dayscount++;

			DateFrom = AddOneDay(DateFrom);
		}
		return Dayscount;
	}

	short GetActualVactionDays(clsDate DateTo)
	{
		return GetActualVactionDays(*this, DateTo);
	}

	static clsDate CalculateReturnDateVaction(short Days, clsDate DateFrom)
	{
		short vaction = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}


		for (int i = 1; i <= Days + vaction; i++)
		{
			if (IsWeekEnd(DateFrom))
				vaction++;

			DateFrom = AddOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;
			DateFrom = AddOneDay(DateFrom);
		}
		return Days;
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}

	static clsDate GetDateFromBegginingYear(short NumberOrderDays, short Year)
	{
		clsDate Date;// day/month/year
		short remaningdays = NumberOrderDays;
		short OrderMonth = 0;
		Date.Month = 1;
		Date.Year = Year;

		while (true)
		{
			OrderMonth = NumberofdaysinMonth(Year, Date.Month);

			if (remaningdays > OrderMonth)
			{
				remaningdays -= OrderMonth;
				Date.Month++;
			}
			else
			{
				Date.Day = remaningdays;
				break;
			}
		}
		return Date;
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2,bool IncludeEndDay = false)
	{
		//this will take care of negative diff
		int Days = 0;
		short SawpFlagValue = 1;

		
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SawpFlagValue : Days *SawpFlagValue;
	}

	short GetDifferenceInDays(clsDate Date2, bool Includingendday = false)
	{
		return GetDifferenceInDays(*this,Date2,Includingendday);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		cout << "Age:";
		return GetDifferenceInDays(DateOfBirth,clsDate::GetSystemDate(), true);
	}

	enum enDateReturn { Before = -1, Equal = 0, After = 1 };

	static enDateReturn ComparDate(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateReturn::Before;

		if (IsDate1EquleDate2(Date1, Date2))
			return enDateReturn::Equal;


		return enDateReturn::After;
	}

	enDateReturn ComparDate(clsDate Date2)
	{
		return ComparDate(*this, Date2);
	}


};

