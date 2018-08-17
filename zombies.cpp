/********************************************************
 * CS 103 Zombie-pocalypse PA
 * Name: Hope Kim
 * USC email: hopekim@usc.edu
 * Comments (you want us to know):
 * Runs similuations that determine the average, minimum, 
 *    and maximum # of nights that it will take for a  
 *    zombie-pocalypse to take over a certain population
 ********************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
    // Array with enough entries for the maximum population size possible
    bool pop[MAXPOP];
    
    // User input variables
    int N = 0;
    int k = 0;
    int M = 0;
    int s = 0;
    
    // Output for user input
    cout << "Enter the following: N k M seed" << endl;
    cout << "-> ";
    cin >> N >> k >> M >> s;
    
    // Seeding the random number generator with the seed provided by user
    srand(s);
    
    // Quits program if k > N
    if (k > N)
    {
        cout << "Quitting!" << endl;
    }
    
    // Valid program execution
    else
    { 
        // Holds the variables for number of nights (sum for average, min, max)
        double sumNights = 0;
        int min_nights = 1000000000;
        int max_nights = -1;
        
        // Goes through the simulation M times
        for (int simulation = 0; simulation < M; simulation++)
        {
            // Sets indices from 0 to N-1 in the array to humans
            for (int human = 0; human < N; human++)
            {
                pop[human] = false;
            }
            // Sets indices from 0 to k-1 in the array to zombies
            for (int zombie = 0; zombie < k; zombie++)
            {
                pop[zombie] = true;
            }
            
            // Variables to hold counts of nights, humans, zombies
            int numberNights = 0;
            int numberHumans = N-k;
            int numberZombies = k;
            int numberZombiesStart = k;
            
            // While loop for each night that there are still humans
            while (numberHumans > 0)
            {
                // Each zombie gets a bite
                for (int bite = 0; bite < numberZombiesStart; bite++)
                {
                    // Creates a random zombie
                    int zombieIndex = rand() % N;
                    
                    // Makes the zombie and adjusts counts if human before
                    if (pop[zombieIndex] == false)
                    {
                        numberHumans--;
                        numberZombies++;
                        pop[zombieIndex] = true;
                    }
                }
                
                // Changes the number of zombies that start out the next day
                numberZombiesStart = numberZombies;
                
                // Increases the number of nights
                numberNights++;  
            }
            
            // Compares the number of nights after a simulation to the one before
            if (numberNights < min_nights)
            {
               min_nights = numberNights;
            }
            if (numberNights > max_nights)
            {
               max_nights = numberNights;
            }
            
            // Adds to the sum of the nights
            sumNights += numberNights;
        }

        // Prints out average, max, and min number of nights
        double avg_nights = 0;
        avg_nights = sumNights/M;
        
        cout << "Average nights: " << avg_nights << endl;
        cout << "Max nights: " << max_nights << endl;
        cout << "Min nights: " << min_nights << endl;
    }
    
    return 0;
}





