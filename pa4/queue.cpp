/* 
queue.cpp

Author: Hope Kim

Email: hopekim@usc.edu

Short description of this file:
   This file utilizes the queue class in order to carry out all
   of the functions that a queue can implement.
*/

#include "queue.h"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
   delete [] contents;
}

// insert a new Location at the end/back of our list   
void Queue::push(Location loc) {
   // FILL THIS IN
   
   // a new location is at the tail of the list
   contents[tail] = loc;
   
   // tail incremented
   tail++;
}

// return and "remove" the oldest Location not already extracted
Location Queue::pop() {
   // FILL THIS IN
   
   // head is incremented and "removed"
   head++;
   
   // this returns the oldest location not already extracted
   return contents[head-1];
}

// is this Queue empty? (did we extract everything added?)
bool Queue::is_empty() {
   // FILL THIS IN
   
   // if the Queue is empty, head will equal tail
   if (head == tail)
   {
      return true;
   }
   
   // if the Queue is not empty
   else
   {
      return false;
   }
}

