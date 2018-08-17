/* 
web.h

Author: Hope Kim

Email: hopekim@usc.edu

Short description of this file:
   Includes the Web class with public member functions such as the
   default constructor, destructor, read_graph, write_graph, and
   calculate_rank. It also includes the private member variables
   such as the vector<int> walkers and vector<Page> pages.
*/

#ifndef WEB_H
#define WEB_H
#include "page.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>
using namespace std;

class Web { 

public:
    // public member functions
    Web();
    ~Web();
    bool read_graph(const char *filename);
    bool write_graph(const char *filename);
    void calculate_rank(int S,int N);
    void print_pages()  {
	 for(int i=0;i<pages.size() ;i ++) { 
	   cout << pages[i].getID() << " -> " ;
                for(int j=0;j<pages[i].getLinks().size();j++) { 
			cout << pages[i].getLinks()[j] << " ";
	 }
		cout << endl;

        }
    }
    
private:  
   // private member variables   
   vector <int> walkers;
   vector<Page> pages;
};  
#endif