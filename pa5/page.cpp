/* 
page.cpp

Author: Hope Kim

Email: hopekim@usc.edu

Short description of this file:
   Includes both the default constructor for the Page class
   and the addLink function, which were both not defined in
   the header file.
*/

#include "page.h"

// constructor for Page class
Page::Page(int i,const string &u)
{
   // initializes the page id to i
   id = i;
   
   // initializes the page url to u
   url = u;
}

// adds link to the vector of links for a page
void Page::addLink(int id)
{
   // pushes back the id of the link for a page
   links.push_back(id);
}