#pragma once
#pragma warning(disable: 4996)
#include<iostream>
#include<vector>
#include<cmath>
#include <string>
#include"clsString.h"

class clsTime
{
private:
	short _Hour;
	short _Minute;
	short _Secound;

public:

	clsTime()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Hour = now->tm_hour;
		_Minute = now->tm_min;
		_Secound = now->tm_sec;
	}

	clsTime(string Date)
	{
		clsString Cstring;
		vector<string>Vdtae = Cstring.Split(Date, ":");

		_Hour = stoi(Vdtae[0]);
		_Minute = stoi(Vdtae[1]);
		_Secound = stoi(Vdtae[2]);
	}

	clsTime(short Hour, short Minute, short Secound)
	{
		_Hour = Hour;
		_Minute = Minute;
		_Secound = Secound;
	}

	void SetHour(short Hour)
	{
		_Hour = Hour;
	}
	short GetHour() const
	{
		return _Hour;
	}
	__declspec(property(get = GetHour, put = SetHour))short Hour;

	void SetMinute(short minute)
	{
		_Minute = minute;
	}
	short GetMinute() const
	{
		return _Minute;
	}
	__declspec(property(get = GetMinute, put = SetMinute))short Minute;

	void SetSecound(short Secound)
	{
		_Secound = Secound;
	}
	short GetSecound() const
	{
		return _Secound;
	}
	__declspec(property(get = GetSecound, put = SetSecound))short Secound;

	static clsTime GetSystemTime()
	{
		//StDate Date;
		time_t t = time(0);
		tm* now = localtime(&t);
		short Hour, minutes, Secound;
		Hour = now->tm_hour;
		minutes = now->tm_min;
		Secound = now->tm_sec;
		return clsTime(Hour, minutes, Secound);
	}

	static string TimeToString(clsTime Time)
	{
		return to_string(Time.Hour) + ":" + to_string(Time.Minute) + ":" + to_string(Time.Secound);
	}

	string TimeToString()
	{
		return TimeToString(*this);
	}
};

