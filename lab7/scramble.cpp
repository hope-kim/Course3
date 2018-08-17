// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

int main(int argc, char* argv[]) {
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;
  
  // Checks if user entered enough command line arguments
  if (argc <= 1)
  {
      cout << "Did not enter enough command line arguments." << endl;
      return 1;
  }
  
     // If user entered enough command line arguments
     else
     {
     // Opens the file using command line arguments
     ifstream inputFile(argv[1]);
     
     // Checks if file can be successfully opened and exits program with error message
     if (inputFile.fail())
     {
         cout << "File cannot be opened. Exiting program!" << endl;
         return 1;
     }
     
     // Attempts to read an integer from file
     int numWords = 0;
     inputFile >> numWords;
     
     // If read is unsuccessful, close and exit with error message
     if (inputFile.fail())
     {
         cout << "Did not read integer. Exiting program!" << endl;
         return 1;
     }  

     // Dynamically allocate an array of char*s
     char** wordBank = new char*[numWords];
     
     // Declare a character array "buffer" 41 characters to hold read-in strings
     // Loop to read in each word from the file into the character array
     for (int i = 0; i < numWords; i++)
     {
         char buffer[41] = {0};
         inputFile >> buffer;
         
         // Size to hold new character array
         int size = strlen(buffer);
         
         // Dynamically allocate new character array to hold word
         wordBank[i] = new char[size+1];
         
         // Copy word from buffer to array
         strcpy(wordBank[i], buffer);
     }  
     
     // Close input file
     inputFile.close();
     
     // Pick a random word from the wordBank
     int target = rand() % numWords;
     int targetLen = strlen(wordBank[target]);

     // Make a dynamically-allocated copy of the word and scramble it
     char* word = new char[targetLen+1];
     strcpy(word, wordBank[target]);
     permute(word, targetLen);
     
     // An individual game continues until a word
     // is guessed correctly or 10 turns have elapsed
     while (!wordGuessed && numTurns > 0)
     {
       cout << "Scrambled word: " << word << endl;
       cout << "What do you guess the original word is? ";
       cin >> guess;
       wordGuessed = (strcmp(guess, wordBank[target]) == 0);
       numTurns--;
     }
     if (wordGuessed)
     {
       cout << "You win!" << endl;
     }
     else
     {
       cout << "Too many turns...You lose!" << endl;
     }
     
     // Deallocate all memory created with new
     delete [] word;
     word = 0;
     
     for (int i = 0; i < numWords; i++)
     {
         delete [] wordBank[i];
     }
     
     delete [] wordBank;
     wordBank = 0;
     }
  
  return 0;
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}
