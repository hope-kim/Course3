/* 
web.cpp

Author: Hope Kim

Email: hopekim@usc.edu

Short description of this file:
   Includes the Web class's default constructor, destructor,
   read_graph, write_graph, and calculate_rank functions.
*/

#include "web.h"

// default constructor for Web class; not used
Web::Web()
{

}

// destructor for Web class; no dynamic memory allocation
Web::~Web()
{
   walkers.clear();
   pages.clear();
}

// takes an input file and sets the correct variables
bool Web::read_graph(const char *filename)
{
   // uses ifstream with the filename
   ifstream inputFile(filename);
   
   // validates that the file can be opened
   if (inputFile.fail())
   {
      return false;
   }


   // determines the number of pages
   int numberPages;

   inputFile >> numberPages;

   // validates number of pages
   if (inputFile.fail())
   {
      return false;
   }
   
   // loops through the number of pages
   for (int i = 0; i < numberPages; i++)
   { 
      // sets the id and url
      int id;
      string url;
      
      inputFile >> id >> url;

      // validates id
      if (inputFile.fail())
      {
         return false;
      }

      // validates url
      if (inputFile.fail())
      {
         return false;
      }
      
      // creates a newPage with constructor
      Page newPage(id, url);
      
      // sets the rank
      double rank;

      inputFile >> rank;

      // validates rank
      if (inputFile.fail())
      {
         return false;
      }
      
      // sets the rank for newPage
      newPage.setRank(rank);

      // sets the links for each page
      string linkString;
      
      // ensures that linkString will be correct
      inputFile.ignore();
      
      // reads in line from inputFile into linkString
      getline(inputFile, linkString);
      
      // stringstream to extract numbers from linkString
      stringstream linkToNumber(linkString);
      
      // goes through the whole linkString
      while(!linkToNumber.eof())
      {
         // creates rank
         int number; 
         linkToNumber >> number;

         // validates rank
         if (linkToNumber.fail())
         {
            break;
         }
         
         // adds the link to the vector of links
         newPage.addLink(number);
      }
      
      // adds it to the vector of pages
      pages.push_back(newPage);
   }
   return true; 
}

// writes to an output file using the correct variables
bool Web::write_graph(const char *filename)
{
   // uses ofstream with an output filename
   ofstream outputFile;
   
   // opens the file
   outputFile.open(filename);

   // validates that the file can be opened
   if (outputFile.fail())
   {
      return false;
   }
   
   // writes the number of pages
   outputFile << pages.size() << endl;
   
   // loops through the number of pages
   for (int i = 0; i < pages.size(); i++)
   {
      // writes the page id
      outputFile << pages[i].getID() << endl;
      
      // writes the page url
      outputFile << '\t' << pages[i].getURL() << endl;
      
      // writes the page rank
      outputFile << '\t' << pages[i].getRank() << endl;
      
      // loops through and writes the links for each page
      for (int j = 0; j < pages[i].getLinks().size(); j++)
      {
         // for only one link
         if (j == (pages[i].getLinks().size() - 1) && j == 0)
         {
            outputFile << '\t' << pages[i].getLinks()[j] << " " << endl; 
         }

         // for the first link
         else if(j == 0)
         {
            outputFile << '\t' << pages[i].getLinks()[j] << " ";
         }

         //for the last link
         else if(j == (pages[i].getLinks().size() - 1))
         {
            outputFile << pages[i].getLinks()[j] << " " << endl;
         }

         // for any other links
         else
         {
            outputFile << pages[i].getLinks()[j] << " ";
         }
      }
   }
   
   // closes the output file
   outputFile.close();
   return true;
}
 
// calculates the page rank using the number of simulations and walkers   
void Web::calculate_rank(int S,int N)
{
   // number of pages
   int numberPages = pages.size();

   // number of walkers per page to equally distribute
   int numWalkersPerPage = N/numberPages;

   // number of leftover walkers to equally distribute
   int leftOver = N % numberPages;

   // uniformly distributes the walkers
   for (int i = 0; i < numberPages; i++)
   {
      // uniformly distributes numWalkersPerPage
      walkers.push_back(numWalkersPerPage);

      // if there are leftover walkers to equally distribute
      if (leftOver != 0)
      {
         // add to the page
         walkers[i] += 1;

         // decrements the leftovers
         leftOver--;
      }
   }
   
   // makes a vector tempWalkers that is the same as walkers to avoid
   // double counting
   vector <int> tempWalkers = walkers;

   // loops through the number of simulations
   for (int i = 0; i < S; i++)
   {
      // loops through the number of pages
      for (int j = 0; j < numberPages; j++)
      {
         // loops through the number of walkers    
         for (int k = 0; k < walkers[j]; k++)
         {
            // gets a random link index from the page that the walker is on
            int randomLinkIndex = rand() % pages[j].getLinks().size();

            // walker moves to new random page 
            tempWalkers[pages[j].getLinks()[randomLinkIndex]]++;

            // walker leaves original page
            tempWalkers[j]--;
         }
      }

      // sets walkers equal to tempWalkers
      walkers = tempWalkers;
   }
   
   // loops through the number of pages
   for (int i = 0; i < pages.size(); i++)
   {
      // holds the proportion of walkers on that page
      double proportion = walkers[i]/(double)N;
         
      // sets the rank for this page to the proportion
      pages[i].setRank(proportion);
   }
}