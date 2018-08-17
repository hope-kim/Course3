#include <iostream>
#include <fstream>

using namespace std;

int** read_mpg(const char* filename, int* n)
{

   ifstream inputFile(filename);
   
   if (inputFile.fail())
   {
      cout << "File open error" << endl;
      return 0;
   }
   
   if (inputFile.fail())
   {
      cout << "First line isn't an integer" << endl;
      return 0;
   }
   
   inputFile >> *n;
   
   int** fuelConsumption = new int*[*n];
   
   int mileage;
   
   for (int i = 0; i < *n; i++)
   {
      fuelConsumption[i] = new int[4];
      
      for (int j = 0; j < 4; j++)
      {
         inputFile >> mileage;
         fuelConsumption[i][j] = mileage;
      }
   }
   
   inputFile.close();
   
   return fuelConsumption;
}

double convert_speed_time_to_gallons(int speed, int minutes, int* mpg_array)
{
   double gallons;
   int index;
   
   if (speed < 20)
   {
      index = 0;
   }
   else if (speed >= 20 && speed < 40)
   {
      index = 1;
   }
   else if (speed >= 40 && speed < 60)
   {
      index = 2;
   }
   else
   {
      index = 3;
   }
   
   double distance = (speed*minutes)/60;
   int mileage = mpg_array[index];
   gallons = distance/mileage;
   
   return gallons;
   
}
