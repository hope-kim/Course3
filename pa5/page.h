/* 
page.h

Author: Hope Kim

Email: hopekim@usc.edu

Short description of this file:
   Includes the Page class along with its public member functions
   and private member variables.
*/

#ifndef PAGE_H
#define PAGE_H
#include <string>
using std::string;
#include <vector>
using std::vector;
class Page { 
public:
  // public member functions
  Page(int i,const string &u);
  int getID() const { return id; }
  string getURL() const { return url;}
  double getRank() const { return rank; }
  void addLink(int id);
  void setRank(double r) { rank = r;}
  vector<int> &getLinks() { return links; };
  
private:
  // private member variables
  int id;
  string url;
  double rank;
  vector<int> links;
};  
#endif