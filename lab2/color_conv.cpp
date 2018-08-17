#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    // Enter your code here
    int red = 0;
    int green = 0;
    int blue = 0;
    double white = 0.0;
    double cyan = 0.0;
    double magenta = 0.0;
    double yellow = 0.0;
    double black = 0.0;
    
    
    cout << "Enter your red value: ";
    cin >> red;
    cout << "Enter your green value: ";
    cin >> green;
    cout << "Enter your blue value: ";
    cin >> blue;
    
    if ((max(red/255.0, green/255.0) >= max(red/255.0, blue/255.0)) && (max(red/255.0, green/255.0) >= max(green/255.0, blue/255.0)))
    {
        white = max(red/255.0, green/255.0);
        cyan = (white-red/255.0)/white;
        magenta = (white-green/255.0)/white;
        yellow = (white-blue/255.0)/white;
        black = 1.0-white;
        
        cout << "cyan: " << cyan << std::endl;
        cout << "magenta: " << magenta << std::endl;
        cout << "yellow: " << yellow << std::endl;
        cout << "black: " << black << std::endl;
    }
    else if ((max(green/255.0, blue/255.0) >= max(red/255.0, blue/255.0)) && (max(green/255.0, blue/255.0) >= max(red/255.0, green/255.0)))
    {
        white = max(green/255.0, blue/255.0);
        cyan = (white-red/255.0)/white;
        magenta = (white-green/255.0)/white;
        yellow = (white-blue/255.0)/white;
        black = 1.0-white;
        
        cout << "cyan: " << cyan << std::endl;
        cout << "magenta: " << magenta << std::endl;
        cout << "yellow: " << yellow << std::endl;
        cout << "black: " << black << std::endl;
    }
    else if ((max(blue/255.0, red/255.0) >= max(red/255.0, green/255.0)) && (max(blue/255.0, red/255.0) >= max(blue/255.0, green/255.0)))
    {
        white = max(blue/255.0, red/255.0);
        cyan = (white-red/255.0)/white;
        magenta = (white-green/255.0)/white;
        yellow = (white-blue/255.0)/white;
        black = 1.0-white;
        
        cout << "cyan: " << cyan << std::endl;
        cout << "magenta: " << magenta << std::endl;
        cout << "yellow: " << yellow << std::endl;
        cout << "black: " << black << std::endl;
    }
    
    return 0;
}
