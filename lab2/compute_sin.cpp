#include <iostream>
#include <cmath>

/* Author: Hope Kim
 * Program: compute_sin
 * Description: Reads a number x from input, an angle in radians.
 *    Computes an approximation to sin(x) using an 4th-order Taylor series.
 */

using namespace std;

int fact(int); // declares a function the skeleton defines for you.

int main(int argc, char *argv[])
{
    // Declare any variables you need here
    double userInput = 0.0;
    double result = 0.0;
    
    // Prompt the user
    cout << "Enter x in radians:  ";
    
    // get input
    cin >> userInput;
    
    
    // Do some operations
    result = userInput - (pow(userInput, 3))/fact(3) + (pow(userInput, 5))/fact(5) - (pow(userInput, 7))/fact(7);
    
    // Print the result to the user
    cout << "The approximation is: " << result << std::endl;
    
    
    // You're done
    return 0;
    
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}


