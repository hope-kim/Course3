#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int angleDegrees = 0;
    double angleRadians = 0;
    cout << "Enter the angle theta in degrees: ";
    cin >> angleDegrees;
    angleRadians = (M_PI*angleDegrees)/180;
    
    for (int y = 0; y < 31; y++)
    {
        int xCoord = floor(y*(tan(angleRadians)));
        
        if (xCoord < 20 && xCoord > 0)
        {
            for (int i = 0; i < xCoord; i++)
            {
                cout << "*";
            }
        }
        if (xCoord >= 20 && xCoord <= 30)
        {
            for (int i = 0; i < 20; i++)
            {
                cout << "*";
            }
        }
        if (xCoord > 30)
        {
            for (int i = 0; i < xCoord; i++)
            {
                cout << "*";
            }
        }
        cout << endl;
    }
    
    
    return 0;
}
