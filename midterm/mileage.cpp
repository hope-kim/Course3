#include <iostream>
#include <fstream>
#include <climits>

#include "mlib.h"
using namespace std;

int main(int argc, char* argv[])
{
   if (argv[1] == NULL)
   {
      cout << "No filename error" << endl;
      return 1;
   }
   
   int numTypes;
   int** fuelConsumption = read_mpg(argv[1], &numTypes);
   
   if (fuelConsumption == 0)
   {
      return 1;
   }
   
   int speed;
   int min;
   
   cin >> speed >> min;
   
   double* gallons = new double[numTypes];
   
   while(speed > -1 && min > -1)
   {
      for (int i = 0; i < numTypes; i++)
      {
         gallons[i] += convert_speed_time_to_gallons(speed, min, fuelConsumption[i]);
      }
      cin >> speed >> min;
   }
   
   double low = INT_MAX;
   int index = 0;
   
   for (int i = 0; i < numTypes; i++)
   {
      cout << i << " " << gallons[i] << endl;
      
      if (low > gallons[i])
      {
         low = gallons[i];
         index = i;
      }
   }
   
   cout << "Least: " << index << endl;
   
   for (int i = 0; i < numTypes; i++)
   {
      delete[] fuelConsumption[i];
   }
   
   delete [] fuelConsumption;
   delete [] gallons;
   return 0;
}
