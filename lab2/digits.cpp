#include <iostream>
using namespace std;

int main()
{
    int userInput = 0;
    int ones = 0;
    int tens = 0;
    int hundreds = 0;
    
    cout << "Enter an integer between 0 and 999: ";
    cin >> userInput;
    
    
    ones = (userInput % 100) % 10;
    
    tens = ((userInput % 100) - ones)/10;
    
    hundreds = userInput/100;
    
    cout << "1s digit is: " << ones << endl;
    cout << "10s digit is: " << tens << endl;
    cout << "100s digit is: " << hundreds << endl;
    
    return 0;
}
