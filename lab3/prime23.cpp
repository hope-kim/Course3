#include <iostream>
using namespace std;

int main()
{
    int userInput = 0;
    cout << "Enter a positive integer: ";
    cin >> userInput;
    
    int countTwos = 0;
    int countThrees = 0;
    bool otherFactor = false;
    
    while ((userInput % 2 == 0) && (userInput > 1))
    {
        countTwos++;
        userInput /= 2;
    }
    while ((userInput % 3 == 0) && (userInput > 1))
    {
        countThrees++;
        userInput /= 3;
    }
    
    if (userInput > 1)
    {
        otherFactor = true;
    }
    if (userInput == 1)
    {
        otherFactor = false;
    }
    
    if (otherFactor)
    {
        cout << "No" << endl;
    }
    
    else if (otherFactor == false)
    {
        cout << "Yes" << endl;
        cout << "Twos: " << countTwos;
        cout << " Threes: " << countThrees << endl;
    }
        
    
    
    
    
    
    
    return 0;
}
