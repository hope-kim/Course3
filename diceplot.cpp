#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int roll()
{
    int randomRoll = rand() % 6 + 1;
    
    return randomRoll;
}
void printHistogram(int counts[])
{
        for (int i = 0; i < 21; i++)
        {
            cout << i+4 << ": ";
            for (int j = 0; j < counts[i]; j++)
            {
                cout << "X";
            }
            cout << endl;
        }
}
int main()
{
    srand(time(0));
    int n = 0;
    cout << "How many rolls do you want: ";
    cin >> n;
    
    int array[n];
    int counts[21];
    for (int i = 0; i < 21; i++)
    {
        counts[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int sumRolls = 0;
        for (int i = 0; i < 4; i++)
        {
            sumRolls += roll();
        }
        array[i] = sumRolls;
        
        if (sumRolls == 4)
        {
            counts[0]++;
        }
        else if (sumRolls == 5)
        {
            counts[1]++;
        }
        else if (sumRolls == 6)
        {
            counts[2]++;
        }
        else if (sumRolls == 7)
        {
            counts[3]++;
        }
        else if (sumRolls == 8)
        {
            counts[4]++;
        }
        else if (sumRolls == 9)
        {
            counts[5]++;
        }
        else if (sumRolls == 10)
        {
            counts[6]++;
        }
        else if (sumRolls == 11)
        {
            counts[7]++;
        }
        else if (sumRolls == 12)
        {
            counts[8]++;
        }
        else if (sumRolls == 13)
        {
            counts[9]++;
        }
        else if (sumRolls == 14)
        {
            counts[10]++;
        }
        else if (sumRolls == 15)
        {
            counts[11]++;
        }
        else if (sumRolls == 16)
        {
            counts[12]++;
        }
        else if (sumRolls == 17)
        {
            counts[13]++;
        }
        else if (sumRolls == 18)
        {
            counts[14]++;
        }
        else if (sumRolls == 19)
        {
            counts[15]++;
        }
        else if (sumRolls == 20)
        {
            counts[16]++;
        }
        else if (sumRolls == 21)
        {
            counts[17]++;
        }
        else if (sumRolls == 22)
        {
            counts[18]++;
        }
        else if (sumRolls == 23)
        {
            counts[19]++;
        }
        else if (sumRolls == 24)
        {
            counts[20]++;
        }
    }
    
    printHistogram(counts);
    
    return 0;
}
