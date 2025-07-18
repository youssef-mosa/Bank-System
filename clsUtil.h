#pragma once
#pragma warning(disable: 4996)
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdio>
#include <string>
#include "clsDate.h";

using namespace std;
class clsUtil
{
public:

   enum enCharType { SamallLetter = 1, CapitalLetter = 2, Digit = 3, SpecialCharacter = 4  , MixChars=5};

   static void Srand()
	{
		 srand((unsigned)time(NULL));
	}

   static int RandomNumber(int From, int To)
    {
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

   static char RandomCharacter(enCharType CharType)
    {
       if (CharType == MixChars)
       {
           CharType = (enCharType)RandomNumber(1, 3);
       }

        switch (CharType)
        {
        case enCharType::SamallLetter:
        {
            return char(RandomNumber(97, 122));
            break; // break is not necessary after return.
        }
        case enCharType::CapitalLetter:
        { 
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {           
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        }
        // If no valid type is provided, return a null character.
        return '\0';//we work on char not int
    }

   static  string GenerateWord(enCharType CharType, short Length)
    {
        string Word;

        for (int i = 1; i <= Length; i++)
        {
            // Append a random character of the specified type to the word.
            Word = Word + RandomCharacter(CharType);
        }
        return Word;
    }

   static string GenerateKey(enCharType CharType)
    {
        string Key = "";  

        // Concatenate four groups of 4 random uppercase letters, separated by hyphens.
        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

   static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        // Loop from 1 to NumberOfKeys.
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            // Print the current key number and the generated key.
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

   static void FillArrayWithRandomNumbers(int Arr[],int ArrNumber, int From, int To)
   {
       for (int i = 0; i < ArrNumber; i++)
           Arr[i] = RandomNumber(From, To);
   }

   static void FillArrayWithRandomWords(string Arr[],int ArrNumber, enCharType CharType, short Length)
   {
       for (int i = 0; i < ArrNumber; i++)
           Arr[i] = GenerateWord(CharType, Length);
   }

   static void FillArrayWithRandomKeys(string Arr[],int ArrNumber, enCharType CharType)
   {
       for (int i = 0; i < ArrNumber; i++)
           Arr[i] = GenerateKey(CharType);
   }

   static void PrintArray(int arr[], int arrLength)
   {
       for (int i = 0; i < arrLength; i++)
           cout << arr[i] << endl; 
   }

   static void PrintArray(string arr[], int arrLength)
   {
       for (int i = 0; i < arrLength; i++)
           cout << arr[i] <<endl; 
   }

   static int MaxNumberInArray(int arr[], int arrLength)
   {
       int Max = 0;  

       for (int i = 0; i < arrLength; i++)
       { 
           if (arr[i] > Max)
           {
               Max = arr[i];
           }
       }
       return Max; 
   }

   static int MinNumberInArray(int arr[], int arrLength)
   {
       int Min = arr[0];

       for (int i = 0; i < arrLength; i++)
       {
           if (arr[i] < Min)
           {
               Min = arr[i];
           }
       }
       return Min;  
   }

   static int SumArray(int arr[], int arrLength)
   {
       int Sum = 0;  
       
       for (int i = 0; i < arrLength; i++)
       {
           Sum += arr[i];
       }
       return Sum;  
   }

   static void SumOf2Arrays(int arr1[], int arr2[], int arrSum[], int arrLength)
   {
       for (int i = 0; i < arrLength; i++)
       {
           arrSum[i] = arr1[i] + arr2[i];  
       }
   }

   static float ArrayAverage(int arr[], int arrLength)
   {
       // Compute the average by casting the sum to float to ensure floating-point division.
       return (float)SumArray(arr, arrLength) / arrLength;
   }

   static void CopyArray(int arrSource[], int arrDestination[], int arrLength)
   {
       // Loop through each element up to arrLength and copy from source to destination.
       for (int i = 0; i < arrLength; i++)
           arrDestination[i] = arrSource[i];
   }

   enum enPrimNotPrime { Prime = 1, NotPrime = 2 };

   static enPrimNotPrime CheckPrime(int Number)
   {
       int M = round(Number / 2);

       // Loop from 2 to M to test for divisibility.
       for (int Counter = 2; Counter <= M; Counter++)
       {
           // If Number is divisible by any Counter, then it is not a prime.
           if (Number % Counter == 0)
               return enPrimNotPrime::NotPrime;  // Return NotPrime immediately.
       }

       // If no divisors were found, return Prime.
       return enPrimNotPrime::Prime;
   }

   static void CopyOnlyPrimaryNumbers(int arrSource[], int arrDestination[], int arrLength, int& arr2Lenght)
   {
       int Counter = 0;  
      
       for (int i = 0; i < arrLength; i++)
       {
           if (CheckPrime(arrSource[i]) == enPrimNotPrime::Prime)
           {
               arrDestination[Counter] = arrSource[i];
               Counter++; 
           }
       }

       // The code decrements Counter by 1 before assigning it to arr2Lenght.
       // Note: This is unusual as it reduces the count by one. It may be intended to adjust for 0-based indexing,
       // but typically the counter already reflects the number of primes found.
       arr2Lenght = --Counter;
   }

   static void Swap(int& A, int& B)
   {
       int Temp;

       Temp = A;
       A = B;
       B = Temp;
   }

   static  void Swap(double& A, double& B)
   {
       double Temp;

       Temp = A;
       A = B;
       B = Temp;
   }

   static  void Swap(bool& A, bool& B)
   {
       bool Temp;

       Temp = A;
       A = B;
       B = Temp;
   }

   static  void Swap(char& A, char& B)
   {
       char Temp;

       Temp = A;
       A = B;
       B = Temp;
   }

   static  void Swap(string& A, string& B)
   {
       string Temp;

       Temp = A;
       A = B;
       B = Temp;
   }

   static  void Swap(clsDate& A, clsDate& B)
   {
       clsDate::SwapDates(A, B);

   }

   static  void ShuffleArray(int arr[100], int arrLength)
   {

       for (int i = 0; i < arrLength; i++)
       {
           Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
       }

   }

   static  void ShuffleArray(string arr[100], int arrLength)
   {

       for (int i = 0; i < arrLength; i++)
       {
           Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
       }

   }

   static string  Tabs(short NumberOfTabs)
   {
       string t = "";

       for (int i = 1; i < NumberOfTabs; i++)
       {
           t = t + "\t";
           cout << t;
       }
       return t;

   }

   static string  EncryptText(string Text, short EncryptionKey=10)
   {

       for (int i = 0; i <= Text.length(); i++)
       {

           Text[i] = char((int)Text[i] + EncryptionKey);

       }

       return Text;

   }

   static string  DecryptText(string Text, short EncryptionKey=10)
   {

       for (int i = 0; i <= Text.length(); i++)
       {

           Text[i] = char((int)Text[i] - EncryptionKey);

       }
       return Text;

   }

   static string NumberToText(int number)
   {
       string ones[] = { "","one","two","three","four","five","six","seven","eight",
           "nine", "ten","eleven","twelve" ,"thirteen", "fourteen", "fifteen","sixteen" ,
           "seventeen", "eighteen" ,"nineteen" };
       string tens[] = { "","","twenty" ,"thirty" ,"forty" ,"fifty","sixty","seventy","eighty","ninety","ninety nine" };
       if (number == 0)
       {
           return "";
       }
       if (number >= 1 && number <= 19)
       {
           return ones[number] + " ";
       }
       if (number >= 20 && number <= 99)
       {
           return tens[number / 10] + " " + NumberToText(number % 10) + " ";
       }
       if (number >= 100 && number <= 199)
       {
           return "One hundred " + NumberToText(number % 100) + " ";
       }
       if (number >= 200 && number <= 999)
       {
           return  NumberToText(number / 100) + "hundred " + NumberToText(number % 100) + " ";
       }
       if (number >= 1000 && number <= 1999)
       {
           return "One thousand " + NumberToText(number % 1000) + " ";
       }
       if (number >= 2000 && number <= 999999)
       {
           return  NumberToText(number / 1000) + "thousand  " + NumberToText(number % 1000) + " ";
       }
       if (number >= 1000000 && number <= 1999999)
       {
           return "one Million " + NumberToText(number % 1000000) + " ";
       }
       if (number >= 2000000 && number <= 999999999)
       {
           return  NumberToText(number / 1000000) + "Million  " + NumberToText(number % 1000000) + " ";
       }
       if (number >= 1000000000 && number <= 1999999999)
       {
           return "One Billion " + NumberToText(number % 1000000000) + " ";
       }
       if (number >= 2000000000 && number <= 999999999999)
       {
           return  NumberToText(number / 1000000000) + "Billions  " + NumberToText(number % 1000000000) + " ";
       }
       else
       {
           return "";
       }
   }


};

