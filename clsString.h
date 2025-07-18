#pragma once
#include<iostream>
#include<vector>


using namespace std;

class clsString
{
private:
	string _Value;
	

public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}
	//set
	void SetValue(string Value)
	{
		_Value = Value;
		
	}
	//Get
	string GetValue()
	{
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue))string Value;
	
	static short Length(string S1)
	{
		return S1.length();
	};

	short Length()
	{
		return _Value.length();
	};

	static short CountSpicficLetter(string len, char charcters, bool MatchCase = true)
	{
		short count = 0;
		for (short i = 0; i < len.length(); i++)
		{
			if (MatchCase)
			{
				if (len[i] == charcters)
					count++;
			}
			else
			{
				if (tolower(len[i]) == tolower(charcters))
					count++;
			}
		}
		return count;
	}

	short CountSpicficLetter(char Charcters, bool MatchCase = true)
	{
		return CountSpicficLetter(Charcters, MatchCase);
	}

	static bool IsVowel(char charcters)
	{
		charcters = tolower(charcters);
		return ((charcters == 'a') || (charcters == 'e') || (charcters == 'i') || (charcters == 'o') || (charcters == 'u'));
	} 

	static short CountVowels(string len)
	{
		short count = 0;
		for (short i = 0; i < len.length(); i++)
		{
			if (IsVowel(len[i]))
				count++;
		}
		return count;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void VowelsInAllWord(string len)
	{

		for (short i = 0; i < len.length(); i++)
		{
			if (IsVowel(len[i]))
				cout << len[i] << " ";
		}
	}

	void VowelsInAllWord()
	{
		VowelsInAllWord(_Value);
	}

	static void FirstWordInAllLine(string len)
	{
		string delim = " ";
		string lenword;
		short pos = 0;
		while ((pos = len.find(delim)) != std::string::npos)//npos if  the thing you want not found
		{
			lenword = len.substr(0, pos);
			if (lenword != "")
			{
				cout << lenword << endl;
			}

			len.erase(0, pos + delim.length());//erase clear the word from the variable
		}
		if (len != "")
		{
			cout << len << endl;
		}
	}

	void FirstWordInAllLine()
	{
		FirstWordInAllLine(_Value);
	}

	static short CountWord(string len)
	{
		string delim = " ";
		string lenword;
		short pos = 0;
		short count = 0;
		while ((pos = len.find(delim)) != std::string::npos)
		{
			lenword = len.substr(0, pos);
			if (lenword != "")
			{
				count++;
			}

			len.erase(0, pos + delim.length());
		}
		if (len != "")
		{
			count++;
		}
		return count;
	}

	short CountWord()
	{
		return CountWord(_Value);
	}

	static vector<string> Split(string S1, string Delim)
	{

		vector<string> vString;

		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word   
			// if (sWord != "")
			// {
			vString.push_back(sWord);
			//}

			S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
		}

		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}

		return vString;

	}

	vector<string> Split(string Delim)
	{
		return Split(_Value, Delim);
	}

	static string trimleft(string len)
	{
		for (short i = 0; i < len.length(); i++)
		{
			if (len[i] != ' ')
			{
				return len.substr(i, len.length() - i);
			}
		}
		return "";
	}

	string trimleft()
	{
		return  trimleft(_Value);
	}

	static string trimright(string len)
	{
		for (short i = len.length() - 1; i >= 0; i--)
		{
			if (len[i] != ' ')
			{
				return len.substr(0, i + i);
			}
		}
		return "";
	}

	string trimright()
	{
		return trimright(_Value);
	}

	static string Trim(string len)
	{
		return (trimleft(trimright(len)));
	}

	string Trim()
	{
		return Trim(_Value);
	}

	static string Join(vector<string>vlen, string delim)
	{
		string lenn = "";
		for (string word : vlen)
		{
			lenn = lenn + word + delim;
		}

		return lenn.substr(0, lenn.length() - delim.length());
	}

	static string Join(string arr[], short lengtharray, string delim)
	{
		string lenn = "";
		for (int i = 0; i < lengtharray; i++)
		{
			lenn = lenn + arr[i] + delim;
		}
		return lenn.substr(0, lenn.length() - delim.length());

	}

	static string ReverseWordsInString(string S1)
	{

		vector<string> vString;
		string S2 = "";

		vString = Split(S1, " ");

		// declare iterator
		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{

			--iter;

			S2 += *iter + " ";

		}

		S2 = S2.substr(0, S2.length() - 1); //remove last space.

		return S2;
	}

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}
	
	static void RemoveVowels(string Word)
	{
		string vowel = "aeoui";
		for (int i = 0; i < vowel.length(); i++)
		{
			for (int j = 0; j < Word.length(); j++)
			{
				if (Word[j] == vowel[i])
					Word.erase(remove(Word.begin(), Word.end(), vowel[i]), Word.end());
			}
		}
		cout << Word;
	}

	void RemoveVowels()
	{
		RemoveVowels(_Value);
	}

	static void FirstLetterInEachWord(string len)
	{
		bool Isfirstleter = true;

		for (short i = 0; i < len.length(); i++)
		{
			if (len[i] != ' ' && Isfirstleter)
			{
				cout << len[i] << "   ";
			}
			Isfirstleter = (len[i] == ' ' ? true : false);
		}
	}

	void FirstLetterInEachWord()
	{
		FirstLetterInEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string len)
	{
		bool isfirstleter = true;

		for (short i = 0; i < len.length(); i++)
		{
			if (len[i] != ' ' && isfirstleter)
			{
				len[i] = toupper(len[i]);
				// cout << len[i] << endl;
			}
			isfirstleter = (len[i] == ' ' ? true : false);
		}

		return len;

	}

	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string len)
	{
		bool isfirstleter = true;

		for (short i = 0; i < len.length(); i++)
		{
			if (len[i] != ' ' && isfirstleter)
			{
				len[i] = tolower(len[i]);
				// cout << len[i] << endl;
			}
			isfirstleter = (len[i] == ' ' ? true : false);
		}
		return len;
	}

	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string  UpperAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}

	void  UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string  LowerAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void  LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char  InvertLetterCase(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	static string InvertAllLetters(string len)//small to Capital and Capital to small
	{
		for (short i = 0; i < len.length(); i++)
		{
			len[i] = InvertLetterCase(len[i]);
		}
		return len;
	}

	void InvertAllLetters()
	{
		_Value = InvertAllLetters(_Value);
	}

	static int CountCapitalLetters(string len)
	{
		int count1 = 0;
		for (short i = 0; i < len.length(); i++)
		{
			if (isupper(len[i]))
			{
				count1++;
			}
		}
		return count1;
	}

	int CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static int CountSmallLetters(string len)
	{
		int count2 = 0;
		for (short i = 0; i < len.length(); i++)
		{
			if (islower(len[i]))
			{
				count2++;
			}
		}
		return count2;
	}

	int CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	enum enwhattocount { small = 0, capital = 1, all = 3 };

	static short CountLetter(string len, enwhattocount Whatcount = enwhattocount::all)
	{

		if (Whatcount == enwhattocount::all)
		{
			return len.length();
		}
		short count = 0;

		for (short i = 0; i < len.length(); i++)
		{
			if (Whatcount == enwhattocount::capital && isupper(len[i]))
				count++;
			if (Whatcount == enwhattocount::small && islower(len[i]))
				count++;
		}

		return count;
	}

	static string ReplaceWord(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
	{

		vector<string> vString = Split(S1, " ");

		for (string& s : vString)
		{

			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}

			}
			else
			{
				if (LowerAllString(s) == LowerAllString(StringToReplace))
				{
					s = sRepalceTo;
				}

			}

		}

		return Join(vString, " ");
	}

	string ReplaceWord(string StringToReplace, string sRepalceTo)
	{
		return ReplaceWord(_Value, StringToReplace, sRepalceTo);
	}

	static string RemovePunctuations(string S1)
	{

		string S2 = "";

		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}

		return S2;

	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}

};

