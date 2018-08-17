#include "bigint.h"
#include <iostream>

using namespace std;

BigInt::BigInt(string s)
{
    int stringLength = s.length();
    for (int i = stringLength-1; i > -1; i--)
    {
        bigIntVector.push_back(s[i]-48);
    }
}
string BigInt::to_string()
{
    char charString[bigIntVector.size()+1];
    for (int i = 0; i < bigIntVector.size(); i++)
    {
        charString[i] = (bigIntVector[bigIntVector.size()-1-i] + 48);
    }
    charString[bigIntVector.size()] = 0;
    string final = charString;
    return final;
}
void BigInt::add(BigInt b)
{
       while (b.bigIntVector.size() > bigIntVector.size())
       {
           bigIntVector.push_back(0);
       }
       
       int vectorSize = bigIntVector.size();
       for (int i = 0; i < vectorSize; i++)
       {
           int sum = bigIntVector[i] + b.bigIntVector[i];
           if (i == (bigIntVector.size()-1) && sum == 10)
           {
               bigIntVector[i] = 0;
               bigIntVector.push_back(1);
           }
           else if (i == (bigIntVector.size()-1) && sum > 10)
           {

               bigIntVector[i] = sum % 10;
               bigIntVector.push_back(1);
           }
           else if (sum < 10)
           {
               bigIntVector[i] += b.bigIntVector[i];
           }
           else if (sum == 10)
           {
               bigIntVector[i] = 0;
               bigIntVector[i+1] += 1;
           }
           else if (sum > 10)
           {
               bigIntVector[i] = sum % 10;
               bigIntVector[i+1] += 1;
           }
           
       }
}
