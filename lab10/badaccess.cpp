#include "bigint.h"
#include <iostream>

using namespace std;

class BadExample : BigInt
{
   public:
      int exampleInteger;
      BadExample(string badString, BigInt a);
};

BadExample::BadExample(string badString, BigInt a) : BigInt(badString)
{
   exampleInteger = a.bigIntVector[0];
};


int main()
{
    BigInt a("123");
    BadExample bad("123", a);
    cout << bad.exampleInteger << endl;
    
    return 0;
}
